/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	October 10th, 2019
 *
 *	EditorWindow.hpp: An extended version of EditorComponent
 *					  This class gives the ability to display both text and
                      other components.
*********************************************************************************/

#ifndef EDITOR_WINDOW
#define EDITOR_WINDOW

#include "EditorComponent.hpp"
#include "../customcolors.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

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
				//_buffer[loc] = "Testtesttesetkja;lksdjfalksdfja;lkjddddddddd";

				if(_buffer[loc].length() < size.width)
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
			 * Function Name:   setBuffer()
			 * Purpose:         Sets a new buffer for the text buffer
			 *******************************************************************************/
			void setBuffer(vector<string> newBuffer) {
				//delete the current buffer
				_buffer.clear();

				//replace it
				_buffer = newBuffer;
			}

			/*******************************************************************************
			 * Function Name:   putChar()
			 * Purpose:         Adds a character to the buffer, at the specified location
			 * Without border
			 * ((EditorWindow*)components[0])->putChar('0', ((EditorWindow*)components[0])->getSize().height - 1, ((EditorWindow*)components[0])->getSize().width - 1);
			 *
			 * with border
			 * ((EditorWindow*)components[1])->putChar('1', ((EditorWindow*)components[1])->getSize().height - 3, ((EditorWindow*)components[1])->getSize().width - 5);
			 *******************************************************************************/
			bool putChar(char c, int y, int x) {
				bool returnVal = false;

				if (hasBorder()) {
					//y++;
					x++;  //we can't use the first column, there is a border there now
					if (y >= 0 & y < _buffer.size()-2 && x >= 1 && x < _buffer[y].size()-2) {	 //check to make sure we aren't trying to enter in invalid area

						//Add the character to the buffer
						_buffer[y][x] = (int)c;

						//and print the character to the string
						wmove(_c_window, y, x);						//The curses wmove function
						waddch(_c_window, (int)_buffer[y].at(x));		//add char to window, at x, y, casted to an int for curses
						returnVal = true;
					}
				}else {
					if (y >= 0 & y < _buffer.size() && x >= 0 && x < _buffer[y].size()) {	 //check to make sure we aren't trying to enter in invalid area
						
						//Add the character to the buffer
						_buffer[y][x] = (int)c;

						//and print the character to the string
						wmove(_c_window, y, x);						//The curses wmove function
						waddch(_c_window, (int)_buffer[y].at(x));		//add char to window, at x, y, casted to an int for curses
						returnVal = true;
					}
					
				}
				return returnVal;
			}

			/*******************************************************************************
			 * Function Name:   render()
			 * Purpose:         Renders this EditorWindow
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
								colorbox(_c_window, COLOR_MENU_PAIR, true);

								//we do have a border
								//loop through each line
								for (int y = 1; y < getSize().height - 1; y++) { //we won't print on the first or last line, because the border is there

									//loop through each character in the line
									for (int x = 1; x < _buffer[y].size()+1 && x < getSize().width - 2; x++) {
										wmove(_c_window, y, x);
										waddch(_c_window, (int)_buffer[y - 1].at(x - 1));
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