/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	October 1st, 2019
 *
 *	EditorWindow.hpp: An extended version of EditorComponent
 *					  This class gives the ability to display both text and
                      other components.
 * If you are going to use a border, the rendering of a window changes
 * the border takes up the outside edge of the window, so it is two
 * lines shorter, or columns shorter than without the border.
 * When the border is removed, everything is reprinted starting at the top left.
*********************************************************************************/

#ifndef EDITOR_WINDOW
#define EDITOR_WINDOW

#include "EditorComponent.hpp"
#include "../customcolors.h"

#include <vector>
#include <string>
#include <sstream>

using std::vector;
using std::string;
using std::istringstream;

//we are defining a class in the namespace TextEditorNamespace
namespace TextEditorNamespace {

	//we are defining a EditorWindow, which is an extention of EditorComponent
	class EditorWindow : public EditorComponent {

		//We'll be extending this class later, these will be private for extended classes
		protected:

			//Each EditorWindow can have a collection of components inside it, these will need to be rendered
			vector<TextEditorNamespace::EditorComponent*> _components{};

			//we have a buffer area where we will display curses chars
			vector<string> _buffer;

			//do we have a border
			bool _hasBorder;
			
		//These will be public for all extended classes
		public:

			//constructor
			EditorWindow(WINDOW* parent = 0, Location location = { 0, 0 }, Size size = { 0, 0 }, bool isVisible = false, bool hasBorder = false)
				:EditorComponent(parent, location, size, isVisible), _hasBorder(hasBorder) {
				
				//set up the buffer, starting with a blank line, and then repeat that blank line for every line of buffer
				string blankLine(size.width, ' ');

				//create a new blank line for every height of size
				for (int i = 0; i < size.height; i++) {
					_buffer.push_back(blankLine);
				}

				int loc = size.height - 3;
				if (loc < 0) loc = 0;
				//_buffer[loc] = "Testtesttesetkja;lksdjfalksdfja;lkjddddddddd";

				if(_buffer.size() > 0 && _buffer[loc].length() < size.width)
				_buffer[loc].append(size.width - _buffer[loc].length(), ' '); //add the rest of the lines in
				int test = 0;

				//set up our border, if we have one.
				if (_hasBorder) {
					colorbox(_c_window, COLOR_MENU_PAIR, 1);
				}

				//_components.push_back(
				//	new TextEditorNamespace::EditorWindow{ parent, TextEditorNamespace::Location{5, 5}, TextEditorNamespace::Size{10, 10}, true, true }
				//);
				
			}

			/*******************************************************************************
			 * Function Name:   hasBorder()
			 * Purpose:         Returns if this EditorWindow has a border
			 *******************************************************************************/
			bool hasBorder() const {
				return _hasBorder;
			}

			/*******************************************************************************
			 * Function Name:   setHasBorder()
			 * Purpose:         Sets if this EditorWindow has a border
			 *******************************************************************************/
			/*void setHasBorder(bool hasBorder){
				_hasBorder = hasBorder;
			}*/ ////we will implement this when we figure out how to remove a border

			/*******************************************************************************
			 * Function Name:   getBuffer()
			 * Purpose:         Returns the text buffer
			 *******************************************************************************/
			vector<string> getBuffer() const {
				return _buffer;
			}

			/*******************************************************************************
			 * Function Name:   getwords()
			 * Purpose:         Returns every word in the text buffer.
			 *******************************************************************************/
			vector<string> getWords() const {
				vector<string>words;

				for (int i = 0; i < _buffer.size(); i++) {
					// Used to split string around spaces. 
					istringstream ss(_buffer[i]);

					// Traverse through all words 
					do {
						// Read a word 
						string word;
						ss >> word;

						//we only want words and numbers here
						if (word == "" || &word[0] == " ") {
							//int i = 0;
						}
						else {
							words.push_back(word);
						}

						// While there is more to read 
					} while (ss);
				}
				
				return words;
			}

			/*******************************************************************************
			 * Function Name:   setBuffer()
			 * Purpose:         Sets a new buffer for the text buffer
			 *******************************************************************************/
			/*void setBuffer(vector<string> newBuffer) {
				//delete the current buffer
				_buffer.clear();

				//replace it
				_buffer = newBuffer;
			}*/

			/*******************************************************************************
			* Function Name:   imprintOnBuffer(toImprint)
			* Purpose:         Imprints the data in _data to the _buffer.
			*                  Imprint takes a snapshot of a buffer, putting the result
			*                  into the Window Buffer. It starts at a specific
			*				   position in the buffer and the snapshot it takes
			*                  is only as large as the buffer it imprints onto.
			*                  toImprint and _buffer need to be the same type.
			*				   startY and startX denote where in the source
			*                  buffer we start imprinting from
			*******************************************************************************/
			void imprintOnBuffer(vector<string> toImprint, int startY = 0, int startX = 0) {

				//loop through toImprint from where we are scrolled, until where we are scrolled + size of buffer in y
				int start = startY;
				int end = start + _buffer.size()-1;

				//end shouldn't be bigger than toImprintSize
				//if (end > toImprint.size())end = toImprint.size(); //keep the last line from being printed over and over.
				for (int i = start; i < end; i++) {
					if (i >= toImprint.size() /*|| i >= _buffer.size()*/) {

						//we are trying to imprint a line that doesn't exist in toImprint
						//lets stop doing that. NEVER CHANGE THE BUFFER SIZE, UNLESS WE ARE RESIZING
						string newString = "";
						int oldSize = _buffer[0].size();
						int diff = oldSize - newString.size();
						newString.insert(newString.length(), diff, ' ');		//padding happens here
						_buffer[i - start] = newString;
						//break;
					}
					else {

						//imprint our toImprint string onto our given buffer string.
						_buffer[i - start] = imprintString(toImprint[i], _buffer[i-start], startX); //i-start tartgets our ith buffer, this is how we display scrolled info
					}
				}
				setNeedsRefresh(true);
			}

			/*******************************************************************************
			* Function Name:   imprintString(s1, s2)
			* Purpose:         Imprints string s1 onto string s2
			*                  If s1 is larger than s2, we will chop s1 down
			*                  until it is the size of s2, then s2 = s1.
			*                  Otherwise s2 is larger than s1, and we pad
			*                  s1 so it is the size of s2, then we s2 = s1;
			*******************************************************************************/
			string imprintString(string s1, string s2, int startX = 0) {
				if (s1.size() == s2.size()) {

					//everything is good, just replace the string.
					s2 = s1;
				}
				else if (s1.size() < s2.size()) {

					//we need to pad s1, until it is the size of s2, before we replace
					int diff = s2.size() - s1.size();
					s1.insert(s1.length(), diff, ' ');		//padding happens here
					s2 = s1;

				}
				else {

					//we need to chop s1, so it is only the size of s2, before we replace
					int length = s2.size();		//the length we need our string to be chopped to
					s1 = (s1.substr(startX));
					s2 = s1;
				}

				//if startX is not zero, it means we are shifting the string, but we don't want to resize the string at all
				int size = s2.size();					//record size
				if (startX >= s2.length()) {
					s2 = "";
					//s2.insert(s2.length(), size, ' ');
				}else {
					s2 = s2.substr(startX);					//take subtring starting at startX
				}
				
				int diff = size - s2.size();			//calculate difference from new string size to target string size
				s2.insert(s2.length(), diff, ' ');		//pad the string so it is the proper size.

				return s2;
			}

			
			

			/*******************************************************************************
			 * Function Name:   render()
			 * Purpose:         Renders this EditorWindow
			 * Preconditions:   The _buffer that we are rendering with here must be
			 *                  exactly the same size as our _c_window
			 *******************************************************************************/
			virtual void render() {
				
				//only render if we are visibile
				if (isVisible()) {
					
					//render all the included components
					//render components
					for (auto& component : _components){

						//check if we need a refresh, and do a component render
						if (needsRefresh() == true && component->needsRefresh() == true){
							component->render();
							component->refresh();
						}
					}

					//check if we need a refresh, and do a text render
					//if (needsRefresh() == true) {
						
						//loop through the buffer and print it to the screen
						if (_c_window != nullptr) {

							//erase the window first
							werase(_c_window);

							//we render differently if we have a border or not
							if (hasBorder()) {
								//create the border
								colorbox(_c_window, COLOR_GREEN_BLACK, true);

								//we do have a border
								//loop through each line
								for (int y = 1; y < getSize().height - 1; y++) { //we won't print on the first or last line, because the border is there

									//loop through each character in the line
									for (int x = 1; x < _buffer[y].size()+1 && x < getSize().width - 2; x++) {
										wattron(_c_window, COLOR_PAIR(COLOR_WHITE_BLACK));
										wmove(_c_window, y, x);
										waddch(_c_window, (int)_buffer[y - 1].at(x - 1));
										wattroff(_c_window, COLOR_PAIR(COLOR_WHITE_BLACK));
									}
								}
							}else {

								//we do not have a border
								//loop through each line
								for (int y = 0; y < getSize().height; y++) {

									//loop through each char in the line
									for (int x = 0; x < _buffer[y].size() && x < getSize().width; x++) {
										wmove(_c_window, y, x);						//The curses wmove function
										waddch(_c_window, (int)_buffer[y].at(x));		//add char to window, at x, y, casted to an int for curses
									}
								}
							}
						}
					//}
				}
			} //end render function


		//These will not be available to extended classes, or anyone else.
		private:
			/*
				This function was not written by me. I adapted it from the colorbox function in tui.c
				that the teacher supplied.
			*/
			void colorbox(WINDOW* win, chtype color, int hasbox)
			{
				int maxy;
#ifndef PDCURSES
				int maxx;
#endif
				chtype attr = color & A_ATTR;  /* extract Bold, Reverse, Blink bits */

				setcolor(win, color);

#ifdef A_COLOR
				if (has_colors())
					wbkgd(win, COLOR_PAIR(color & A_CHARTEXT) | (attr & ~A_REVERSE));
				else
#endif
					wbkgd(win, attr);

				werase(win);

#ifdef PDCURSES
				maxy = getmaxy(win);
#else
				getmaxyx(win, maxy, maxx);
#endif
				if (hasbox && (maxy > 2))
					box(win, 0, 0);

				touchwin(win);
				wrefresh(win);
			}

			/*
				This function was not written by me. I adapted it from the setcolor
				function in tui.c, supplied by the teacher.
			*/
			void setcolor(WINDOW* win, chtype color)
			{
				chtype attr = color & A_ATTR;  /* extract Bold, Reverse, Blink bits */

#ifdef A_COLOR
				attr &= ~A_REVERSE;  /* ignore reverse, use colors instead! */
				wattrset(win, COLOR_PAIR(color & A_CHARTEXT) | attr);
#else
				attr &= ~A_BOLD;     /* ignore bold, gives messy display on HP-UX */
				wattrset(win, attr);
#endif
			}

	}; //end class EditorWindow

} // end TextEditorNamespace


#endif