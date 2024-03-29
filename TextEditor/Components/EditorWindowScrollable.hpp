#/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	October 4th, 2019
 *
 *	EditorWindowScrollable.hpp: An extended version of EditorWindowMoveable
 *					  This class further extends the ability of an Editor
 *					  window to be able to be scrolled. This means that
 *					  we need data that can be displayed on the _buffer
 *				      it means that we need to keep track of the location
 *                    we are scrolled to, and we need to be able to render
 *                    to the buffer, from the location we are scrolled to
 *                    either horizontally or vertically
*********************************************************************************/

#ifndef EDITOR_WINDOW_SCROLLABLE
#define EDITOR_WINDOW_SCROLLABLE

#include "EditorWindowMoveable.hpp"
#include "Scrollable.hpp"


//we are defining a class in the namespace TextEditorNamespace
namespace TextEditorNamespace {

	//we are defining a EditorWindowScrollable, which is an extention of EditorWindowMoveable
	class EditorWindowScrollable : public EditorWindowMoveable, public Scrollable {

		//We'll be extending this class later, these will be private for extended classes
	protected:
		Location _scrolledLocation = Location{ 0, 0 };			//Keep track of our scrolling

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

			//we don't want to imprint our data if it is empty.
			if (!_data.empty()) {

				//imprint any data we might have onto the buffer
				imprintOnBuffer(_data, getScrollLocation().y, getScrollLocation().x);
			}

			//then call our super classes render function.
			EditorWindow::render();
		}

		/*******************************************************************************
		* Function Name:   setData()
		* Purpose:         Sets the data that we are to display
		*******************************************************************************/
		void setData(vector<string>d) {
			_data = d;
			setNeedsRefresh(true);
		}

		/*******************************************************************************
		* Function Name:   getScrollLocation()
		* Purpose:         Returns our current scrolling location
		*******************************************************************************/
		virtual Location getScrollLocation(void) {
			return _scrolledLocation;
		}

		/*******************************************************************************
		* Function Name:   setScrolledLocation()
		* Purpose:         Sets the current scroll location.
		*******************************************************************************/
		virtual void setScrollLocation(Location l) {

			//neither x nor y can be allowed to be less than 0
			if (l.x < 0) l.x = 0;
			if (l.y < 0) l.y = 0;

			//set the location
			_scrolledLocation = l;
		}

		/*******************************************************************************
		* Function Name:   incrementScroll()
		* Purpose:         Adds 1 to the current scrolled location.
		*******************************************************************************/
		virtual void incrementScroll(char xOry = 'y') {

			switch (xOry) {
				case 'x':
					setScrollLocation(Location{ getScrollLocation().y, getScrollLocation().x + 1 });
				break;
				case 'y':
					setScrollLocation(Location{ getScrollLocation().y + 1, getScrollLocation().x });
				break;
			}
			setNeedsRefresh(true);
		}

		/*******************************************************************************
		* Function Name:   decrementScroll()
		* Purpose:         Subtracts 1 to the current scrolled location.
		*******************************************************************************/
		virtual void decrementScroll(char xOry = 'y') {

			switch (xOry) {
			case 'x':
				setScrollLocation(Location{ getScrollLocation().y, getScrollLocation().x - 1 });
				break;
			case 'y':
				setScrollLocation(Location{ getScrollLocation().y - 1, getScrollLocation().x });
				break;
			}
			setNeedsRefresh(true);
		}

	//These will not be available to extended classes, or anyone else.
	private:
		

	};
} // end TextEditorNamespace

#endif