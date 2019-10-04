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
			//do we need to do anything here?
		}


		/*******************************************************************************
		* Function Name:   render()
		* Purpose:         Overrides the EditorWindow render()
		*				   Here we need to make sure our _data vector gets
		*                  properly copied to our _buffer vector. Then
		*                  we need to call our super classes render
		*******************************************************************************/
		virtual void render() {

			//then call our super classes render function.
			EditorWindow::render();
		}



		//These will not be available to extended classes, or anyone else.
	private:
		

	};
} // end TextEditorNamespace

#endif