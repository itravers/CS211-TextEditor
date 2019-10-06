/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	October 5th, 2019
 *
 *	EditorWindowEditable.hpp: An extended version of EditorWindowScrollable
 *							  This class further extends the ability of an
 *							  EditorWindow to be edited (finally!)
*********************************************************************************/

#ifndef EDITOR_WINDOW_EDITABLE
#define EDITOR_WINDOW_EDITABLE

#include "EditorWindowScrollable.hpp"
#include "Editable.hpp"


//we are defining a class in the namespace TextEditorNamespace
namespace TextEditorNamespace {

	//we are defining a EditorWindowEditable, which is an extention of EditorWindowScrollable
	class EditorWindowEditable : public EditorWindowScrollable, public Editable {

		//We'll be extending this class later, these will be private for extended classes
	protected:

		//These will be public for all extended classes
	public:

		//constructor
		EditorWindowEditable(WINDOW* parent = 0, Location location = { 0, 0 }, Size size = { 0, 0 }, bool isVisible = false, bool hasBorder = false)
			:EditorWindowScrollable(parent, location, size, isVisible, hasBorder) {

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
		virtual void putChar(char c, Location l) {
			//bool returnVal = false;
			/*int x = l.x;
			int y = l.y;

			if (hasBorder()) {
				//y++;
				x++;  //we can't use the first column, there is a border there now
				if (y >= 0 && y < _buffer.size() - 2 && x >= 1 && x < _buffer[y].size() - 2) {	 //check to make sure we aren't trying to enter in invalid area

					//Add the character to the buffer
					_buffer[y][x] = (int)c;

					//and print the character to the string
					wmove(_c_window, y, x);						//The curses wmove function
					waddch(_c_window, (int)_buffer[y].at(x));		//add char to window, at x, y, casted to an int for curses
					returnVal = true;
				}
			}
			else {
				if (y >= 0 && y < _buffer.size() && x >= 0 && x < _buffer[y].size()) {	 //check to make sure we aren't trying to enter in invalid area

					//Add the character to the buffer
					_buffer[y][x] = (int)c;

					//and print the character to the string
					wmove(_c_window, y, x);						//The curses wmove function
					waddch(_c_window, (int)_buffer[y].at(x));		//add char to window, at x, y, casted to an int for curses
					returnVal = true;
				}

			}*/


			if (_data.size() > l.y) {

				//we have this line
				string line = _data[l.y];

				//is the string long enough to just replace the char?
				if (line.size() > l.x) {

					//the string is big enough to change it
					line[l.x] = c;
				}else {
					//the string is not long enough, we have to resize before inserting
					int diff = l.x - line.length()+1;			//figure out difference in size
					line.insert(line.length(), diff, ' ');	//resize
					line[l.x] = c;							//insert char
				}
				_data[l.y] = line;
			}else {
				//we need to add lines to data in order to add this string
				string newLine = "";

				while (_data.size() <= l.y) {
					_data.push_back(newLine);
				}

				//now we have enough lines, we need to create a new line with our char
				
				int diff = l.x - newLine.length()+1;			//figure out difference in size
				newLine.insert(newLine.length(), diff, ' ');	//resize
				newLine[l.x] = c;
				_data[l.y] = newLine;
			}
			setNeedsRefresh(true);

			//return returnVal;
		}

		virtual char getChar(Location l) {
			char returnVal = NULL;
			if (l.y < _data.size()) {
				if (l.x < _data[l.y].size()) {
					returnVal = _data[l.y][l.x];
				}
			}
			return returnVal;
		}


		//These will not be available to extended classes, or anyone else.
	private:


	};
} // end TextEditorNamespace

#endif