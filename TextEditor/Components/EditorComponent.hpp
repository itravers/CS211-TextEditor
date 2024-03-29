/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	October 1st, 2019
 *
 *	EditorComponent.h: An Abstract class used to wrap a ncurses window
 *                     and panel
*********************************************************************************/

#ifndef EDITOR_COMPONENT
#define EDITOR_COMPONENT

//Define for multi-os
#if _WIN32
	#include "../../curses.h"
	#include "../../panel.h"
	#include "../structs.h"
#else
	#include <curses.h>
	#include <panel.h>
#endif

//We are going to define a namespace here that our entire editor library will use.
namespace TextEditorNamespace {

	

	//We are defining the class EditorComponent
	class EditorComponent {

		//We'll be extending this class later, these will be private for extended classes
		protected:

			//EditorComponents have access to a curses window and a curses panel.
			WINDOW* _c_window = nullptr;			//This is the ncurses window
			PANEL* _c_panel = nullptr;			//This is the ncurses panel

			//Variables
			Location _location = { 0, 0 };		//Where we will place our component
			Size _size = { 0, 0 };				//The size of our component
			bool _hasFocus = false;				//Does this component have focus?
			bool _needsRefresh = false;			//Does this component need to be refreshed?
			bool _isVisible = false;				//Is this component Visible?

		//These will be public for all extended classes
		public:

			//Constructor, initialze in the parameter, because that's cool now.
			EditorComponent(WINDOW* parent = 0, Location loc = { 0, 0 }, Size size = { 0, 0 }, bool visible = false)
													: _c_window(parent), _location(loc), _size(size), _isVisible(visible){

				//check to see if the parent is null, if not, create our window as a subwindow
				if (parent != nullptr) {

					//create our components window
					_c_window = subwin(parent, size.height, size.width, _location.y, _location.x);

					//create our components panel
					_c_panel = new_panel(_c_window);

					//Do we want our Component to be visible? //Set it up now, beyond the auto constructor
					if (_isVisible) {
						setIsVisible(true);
					}
					else {
						setIsVisible(false);
					}
				}
			}

			/*******************************************************************************
			 * Function Name:   setNeedsRefresh()
			 * Purpose:         Sets if the component needs to be refreshed next loop
			 *******************************************************************************/
			void setNeedsRefresh(bool needsRefresh) {
				_needsRefresh = needsRefresh;
			}

			/*******************************************************************************
			 * Function Name:   getLocation()
			 * Purpose:         Returns the Components Location
			 *******************************************************************************/
			Location getLocation() const {
				return _location;
			}

			/*******************************************************************************
			 * Function Name:   setLocation()
			 * Purpose:         Sets the Components Location
			 *******************************************************************************/
			void setLocation(Location l){
				_location = l;
			}

			/*******************************************************************************
			 * Function Name:   getSize()
			 * Purpose:         Returns the Components size
			 *******************************************************************************/
			Size getSize() const {
				return _size;
			}

			/*******************************************************************************
			 * Function Name:   setSize()
			 * Purpose:         Sets the Components size
			 *******************************************************************************/
			void setSize(Size s) {
				_size = s;
			}

			/*******************************************************************************
			 * Function Name:   needsRefresh()
			 * Purpose:         Returns if the Component needs to be refreshed or not
			 *******************************************************************************/
			bool needsRefresh() const {
				return _needsRefresh;
			}

			/*******************************************************************************
			 * Function Name:   hasFocus()
			 * Purpose:         Returns if the Component has current focus or not
			 *******************************************************************************/
			bool hasFocus() const {
				return _hasFocus;
			}

			/*******************************************************************************
			 * Function Name:   setHasFocus()
			 * Purpose:         Sets if the Compentnt is focused or not
			 *******************************************************************************/
			virtual void setHasFocus(bool hasFocus) {
				_hasFocus = hasFocus;
			}

			/*******************************************************************************
			 * Function Name:   isVisible()
			 * Purpose:         Returns if the Component is visible or not
			 *******************************************************************************/
			bool isVisible() const {
				return _isVisible;
			}

			/*******************************************************************************
			 * Function Name:   setIsVisible()
			 * Purpose:         Sets if the Compentnt is focused or not
			 *******************************************************************************/
			void setIsVisible(bool isVisible) {
				_isVisible = isVisible;
				if (isVisible) {
					show_panel(_c_panel);
					update_panels();
				}else {
					//werase(_c_window);
					hide_panel(_c_panel);
					update_panels();
					//wrefresh(_c_window);
				}
				setNeedsRefresh(true);
			}

			//Render this compenent, must be implemented by implementing class
			virtual void render() = 0;

			virtual void refresh() {
				if (_c_window != nullptr) {
					if (needsRefresh()) {
						werase(_c_window);
						render();
						wrefresh(_c_window);
						setNeedsRefresh(false);  //we'll implement this functionality later
					}
				}
				
			}

			

		
		//These will not be available to extended classes, or anyone else.
		private:

			
			
	}; //end class EditorComponent

}//end namespace TextEditor

#endif