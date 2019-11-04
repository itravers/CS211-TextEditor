#/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	October 4th, 2019
 *
 *	EditorWindowInteractive.hpp: An editor window that can process input
 *								the window has to track location and
 *                              allow the user to type input.
*********************************************************************************/

#ifndef EDITOR_WINDOW_INTERACTIVE
#define EDITOR_WINDOW_INTERACTIVE

#include "EditorWindowEditable.hpp"
#include "KeyboardHandler.hpp"


//we are defining a class in the namespace TextEditorNamespace
namespace TextEditorNamespace {

	//we are defining a EditorWindowScrollable, which is an extention of EditorWindowMoveable
	class EditorWindowInteractive : public EditorWindowEditable, public KeyboardHandler {

		//We'll be extending this class later, these will be private for extended classes
	protected:
		Location _cursorLocation = Location{ 0, 0 };			//Keep track of where our cursor is.

		/*******************************************************************************
		* Function Name:   getCursorLocation()
		* Purpose:         Returns our current cursor location
		*******************************************************************************/
		Location getCursorLocation() {
			return _cursorLocation;
		}

		/*******************************************************************************
		* Function Name:   setCursorLocation()
		* Purpose:         Sets the current cursor location.
		*******************************************************************************/
		void setCursorLocation(Location l) {

			//neither x nor y can be allowed to be less than 0
			if (l.x < 0) l.x = 0;
			if (l.y < 0) l.y = 0;

			//set the cursor location
			_cursorLocation = l;
		}

		/*******************************************************************************
		* Function Name:   incrementCursorLocation()
		* Purpose:         Adds 1 to the current cursor location.
		*******************************************************************************/
		void incrementCursorLocation(char xOry = 'y') {

			switch (xOry) {
			case 'x':
				setCursorLocation(Location{ getCursorLocation().y, getCursorLocation().x + 1 });
				break;
			case 'y':
				setCursorLocation(Location{ getCursorLocation().y + 1, getCursorLocation().x });
				break;
			}
		}

		/*******************************************************************************
		* Function Name:   decrementCursorLocation()
		* Purpose:         Subtracts 1 to the current cursor location.
		*******************************************************************************/
		void decrementCursorLocation(char xOry = 'y') {

			switch (xOry) {
			case 'x':
				setCursorLocation(Location{ getCursorLocation().y, getCursorLocation().x - 1 });
				break;
			case 'y':
				setCursorLocation(Location{ getCursorLocation().y - 1, getCursorLocation().x });
				break;
			}
		}

		/*******************************************************************************
		* Function Name:   putChar() - overRides EditorWindowEditable.putChar
		* Purpose:         Puts a character into the _data, where the cursor is
		*******************************************************************************/
		virtual void putChar(char c) {
			Location translatedLocation = Location{ _cursorLocation.y + _scrolledLocation.y, _cursorLocation.x + _scrolledLocation.x };
			EditorWindowEditable::putChar(c, translatedLocation);
			moveCursorRight();
		}

		//These will be public for all extended classes
	public:

		//constructor
		EditorWindowInteractive(WINDOW* parent = 0, Location location = { 0, 0 }, Size size = { 0, 0 }, bool isVisible = false, bool hasBorder = false)
			:EditorWindowEditable(parent, location, size, isVisible, hasBorder) {

		}


		/*******************************************************************************
		* Function Name:   render()
		* Purpose:         Overrides the EditorWindow render()
		*				   We'll need to render our cursor, etc       
		*******************************************************************************/
		virtual void render() {

			//then call our super classes render function.
			EditorWindowEditable::render();

			Location pulledLocation = Location{_cursorLocation.y, _cursorLocation.x};
			Location renderLocation = Location{ _cursorLocation.y, _cursorLocation.x };

			//translate x and y based on scrolling
			pulledLocation.y = _cursorLocation.y + _scrolledLocation.y;
			pulledLocation.x = _cursorLocation.x + _scrolledLocation.x;

			//then we render our cursor
			int cursorChar = (int)getChar(pulledLocation);
			if (cursorChar <= 0) cursorChar = ' ';

			//translate x and y based on if a border is on
			if (hasBorder()) {
				renderLocation.x++;
				renderLocation.y++;
			}
			
			wattron(_c_window, COLOR_PAIR(COLOR_CURSOR_PAIR));
			mvwaddch(_c_window, renderLocation.y, renderLocation.x, cursorChar);
			wattroff(_c_window, COLOR_PAIR(COLOR_CURSOR_PAIR));
			//wrefresh(contentWindow);
		}

		/*******************************************************************************
		* Function Name:   handleKeyboardInput(int input)
		* Purpose:         handle input sent to this window
		*******************************************************************************/
		virtual void handleKeyboardInput(int input) {
			switch (input) {
			case KEY_UP:
				moveCursorUp();
				break;
			case KEY_DOWN:
				moveCursorDown();
				break;
			case KEY_LEFT:
				moveCursorLeft();
				break;
			case KEY_RIGHT:
				moveCursorRight();
				break;
			
			case KEY_ENTER:
				
				break;
			case 8: //this is a backspace
				moveCursorLeft();
				putChar(' ');
				moveCursorLeft();
				break;
			case 'a': case 'b': case 'c': case ' ': default:
				putChar((char)input);
				break;
			case -1:
				//do nothing if nothing is hit
				break;

			}
		}

		string searchBufferForCurrentWord() {
			string currentWord = "";
			Location translatedLocation = Location{ _cursorLocation.y + _scrolledLocation.y, _cursorLocation.x + _scrolledLocation.x };
			char currentChar = EditorWindowEditable::getChar(translatedLocation);

			if (currentChar == ' ' || currentChar == '\0') {

				//test if the character right before this one exists
				
				//if our current char is a blank, see if there is a word right before this one, if there is, use that
				translatedLocation.x--;
				if (translatedLocation.x  >= 0) {
					char prevChar = EditorWindowEditable::getChar(translatedLocation);
					if (prevChar == ' ' || prevChar == '\0')return currentWord; //if we are on a space, we don't need to show anything
				}else {
					//translatedLocation.x++;
					return currentWord; //if we are on a space, we don't need to show anything
				}
			}
			
			
			
				//we are on a character, we need to backtrack until we are either on a space, or at the first line
				//then we need to return all the chars between are most backtracked position, and our first position.
				int lastX = translatedLocation.x;

				while (translatedLocation.x != 0 && currentChar != ' ') {
					translatedLocation.x--;
					currentChar = EditorWindowEditable::getChar(translatedLocation);
				}

				//go forward one if our current char is ' '
				if (currentChar == ' ')translatedLocation.x++;
				int firstX = translatedLocation.x;

				//build our word
				for (int i = firstX; i <= lastX; i++) {
					translatedLocation.x = i;
					currentWord += EditorWindowEditable::getChar(translatedLocation);
				}
			
			return currentWord;
		}

		void insertString(string s) {
			//Location cursorLoc = ;
			
			//loop through string inserting where our cursor is
			for (int i = 0; i < s.size(); i++) {
				putChar(s[i]);
			}
		}


		//These will not be available to extended classes, or anyone else.
	private:

		void moveCursorUp() {
			if (_scrolledLocation.y == 0) {
				decrementCursorLocation();
			}else {
				decrementScroll();
			}
			setNeedsRefresh(true);
		}

		void moveCursorDown() {
			int offset = 1;
			if (hasBorder()) offset = 3;
			if (_cursorLocation.y < _buffer.size() - offset) {
				incrementCursorLocation();
			}else {
				incrementScroll();
			}
			setNeedsRefresh(true);
		}

		void moveCursorLeft() {
			if (_scrolledLocation.x == 0) {
				decrementCursorLocation('x');
			}
			else {
				decrementScroll('x');
			}
			setNeedsRefresh(true);
		}

		void moveCursorRight() {
			int offset = 1;
			
			if (hasBorder()) offset = 4;	//we offset different if there is a border
			if (_cursorLocation.x < getSize().width - offset) {
				incrementCursorLocation('x');
			}
			else {
				incrementScroll('x');
			}
			setNeedsRefresh(true);
		}

	};
} // end TextEditorNamespace

#endif