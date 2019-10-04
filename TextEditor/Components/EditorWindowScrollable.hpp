#/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	October 4th, 2019
 *
 *	EditorWindowScrollable.hpp: An extended version of EditorWindowMoveable
 *					  This class further extends the ability of an Editor
 *					  window to be able to be scrolled. This means that the
 *                    window now has to keep track of a cursor, a cursor location
 *                    We have to have current lines of text that we are supposed
 *                    to render to screen. We have to keep track of our scroll
 *                    position. We have to have a scroll bar as contained
 *                    component, we have to be able to update that scroll bar.
 *                    We have to allow a user to type and edit text.
*********************************************************************************/

#ifndef EDITOR_WINDOW_SCROLLABLE
#define EDITOR_WINDOW_SCROLLABLE

#include "EditorWindowMoveable.hpp"


//we are defining a class in the namespace TextEditorNamespace
namespace TextEditorNamespace {

	//we are defining a EditorWindowScrollable, which is an extention of EditorWindowMoveable
	class EditorWindowScrollable : public EditorWindowMoveable {

		//We'll be extending this class later, these will be private for extended classes
	protected:
		Location _scrolledLocation = Location{ 0, 0 };			//Keep track of our scrolling
		Location _cursorLocation = Location{ 0, 0 };			//Keep track of where our cursor is.

		//we need text to be displayed, NOTE, this is different than our _buffer
		//text that needs to be displayed will need to be properly imprinted on
		//the _buffer in order to be displayed
		vector<string> _data;

		//These will be public for all extended classes
	public:

		//constructor
		EditorWindowScrollable(WINDOW* parent = 0, Location location = { 0, 0 }, Size size = { 0, 0 }, bool isVisible = false, bool hasBorder = false)
			:EditorWindowMoveable(parent, location, size, isVisible, hasBorder) {
			
			//initialize our _data vector
			_data = vector<string>();
		}


		/*******************************************************************************
		* Function Name:   render()
		* Purpose:         Overrides the EditorWindow render()
		*				   Here we need to make sure our _data vector gets
		*                  properly copied to our _buffer vector. Then
		*                  we need to call our super classes render
		*******************************************************************************/
		virtual void render() {

			//imprint any data we might have onto the buffer
			imprintOnBuffer(_data);

			//then call our super classes render function.
			EditorWindow::render();
		}

		/*******************************************************************************
		* Function Name:   getScrollLocation()
		* Purpose:         Returns our current scrolling location
		*******************************************************************************/
		Location getScrollLocation() {
			return _scrolledLocation;
		}

		/*******************************************************************************
		* Function Name:   setScrolledLocation()
		* Purpose:         Sets the current scroll location.
		*******************************************************************************/
		void setScrollLocation(Location l) {
			_scrolledLocation = l;
		}

		/*******************************************************************************
		* Function Name:   incrementScroll()
		* Purpose:         Adds 1 to the current scrolled location.
		*******************************************************************************/
		void incrementScroll(char xOry = 'y') {

			switch (xOry) {
				case 'x':
					setScrollLocation(Location{ getScrollLocation().y, getScrollLocation().x + 1 });
				break;
				case 'y':
					setScrollLocation(Location{ getScrollLocation().y + 1, getScrollLocation().x });
				break;
			}
		}

		/*******************************************************************************
		* Function Name:   decrementScroll()
		* Purpose:         Subtracts 1 to the current scrolled location.
		*******************************************************************************/
		void decrementScroll(char xOry = 'y') {

			switch (xOry) {
			case 'x':
				setScrollLocation(Location{ getScrollLocation().y, getScrollLocation().x - 1 });
				break;
			case 'y':
				setScrollLocation(Location{ getScrollLocation().y - 1, getScrollLocation().x });
				break;
			}
		}


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
		* Function Name:   imprintOnBuffer(toImprint)
		* Purpose:         Imprints the data in _data to the _buffer.
		*                  Imprinting means that we take the data in _data
		*                  and copy that data to _buffer, dropping any data
		*                  that does not fit into the buffer. 
		*                  Imprinting takes into account our scrolling position
		*                  so that only the correct data from _data gets imprinted
		*                  in the buffer.
		*                  toImprint and _buffer need to be the same type.
		*******************************************************************************/
		void imprintOnBuffer(vector<string> toImprint) {
			
			//loop through toImprint from where we are scrolled, until where we are scrolled + size of buffer in y
			int start = getScrollLocation().y;
			int end = getScrollLocation().y + _buffer.size();
			for (int i = start; i < end; i++) {
				if (i >= toImprint.size()) {

					//we are trying to imprint a line that doesn't exist in toImprint
					//lets stop doing that.
					break;
				}else {

					//imprint our toImprint string onto our given buffer string.
					imprintString(&toImprint[i], &_buffer[i]);
				}
			}
		}

		/*******************************************************************************
		* Function Name:   imprintString(s1, s2)
		* Purpose:         Imprints string s1 onto string s2
		*                  If s1 is larger than s2, we will chop s1 down
		*                  until it is the size of s2, then s2 = s1.
		*                  Otherwise s2 is larger than s1, and we pad
		*                  s1 so it is the size of s2, then we s2 = s1;
		*******************************************************************************/
		void imprintString(string* s1, string* s2) {
			if (s1->size() == s2->size()) {

				//everything is good, just replace the string.
				s2 = s1;
			}else if (s1->size() < s2->size()) {

				//we need to pad s1, until it is the size of s2, before we replace
				int diff = s1->size() - s2->size();
				s1->insert(s1->length(), diff, ' ');		//padding happens here
				s2 = s1;

			}else {

				//we need to chop s1, so it is only the size of s2, before we replace
				int length = s2->size();		//the length we need our string to be chopped to
				s1 = &(s1->substr(0, length));
			}
		}


		//These will not be available to extended classes, or anyone else.
	private:
		

	};
} // end TextEditorNamespace

#endif