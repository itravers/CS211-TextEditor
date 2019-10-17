#/********************************************************************************
 *	Isaac Travers
 *	CS 211 - Data Structures
 *	October 16th, 2019
 *
 *	MenuBar.hpp:  The classic "File Edit View Etc" Menu bar at the top of the program
 *                A menu bar is meant to be at or near the top of the screen.
 *				  The user can click a menu item and a sub-menu will pop up.
 *				  The user can click a sub-menu item and the correlated function
 *				  will be called. If the user clicks off of the sub menu, that
 *				  submenu will be closed.
*********************************************************************************/

#ifndef MENU_BAR_HPP
#define MENU_BAR_HPP

#include "MenuBehaviour.hpp"

//we are defining a class in the namespace TextEditorNamespace
namespace TextEditorNamespace {

	//we are defining a MenuBehaviour
	class MenuBar {

		//We may be extending this class later, these will be private for extended classes
	protected:


		//These will be public for all extended classes
	public:

		//constructor
		MenuBar(){
			//you know nothing jon snow
		}

		/*******************************************************************************
		* Function Name:   render()
		* Purpose:         Renders the menu in a vertical format
		*******************************************************************************/
		virtual void render(vector<string> items) {

		}

		//These will not be available to extended classes, or anyone else.
	private:

	}; // end class MenuBar
} // end TextEditorNamespace

#endif