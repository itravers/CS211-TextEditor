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
#include "EditorMenuPanel.hpp"
#include <map>

using std::map;

//we are defining a class in the namespace TextEditorNamespace
namespace TextEditorNamespace {

	//we are defining a MenuBehaviour
	class MenuBar {

	//We may be extending this class later, these will be private for extended classes
	protected:


	//These will be public for all extended classes
	public:

		//constructor
		MenuBar(WINDOW* window, Location loc, Size size){
			
			//create the mainMenu
			mainMenu = new EditorMenuPanel(window, loc, size);
		}

		/*******************************************************************************
		* Function Name:   addItem(string mainMenu, string subMenu, void (*callBackFunction)(string, void*))
		* Purpose:         adds an Item to the menu, with the given function
		*                  Each menu can only have 1 ITEM with the same name
		*******************************************************************************/
		void addItem(string subMenuName, string itemName, void (*callBackFunction)(string, void*), void* ptr_to_caller) {

			//check to see if itemName already exists
			auto it = subMenus.find(itemName);
			if (it == subMenus.end()) {

				//we have not found an item with that name, we need to add it

				//do we have a subMenu by subMenuName?
				if (mainMenu.contains(subMenuName)) {

					//the main menu already has a submenu by that name,we can add this item to that submenu
					EditorMenuPanel* subMenu = subMenus[subMenuName];
					subMenu->addItem(itemName, callBackFunction, ptr_to_caller);
				}else {

					//the main menu does not have a sub menu by that name, we have to create the sub menu and then add this item to it
					// find the x location of that value
					//int xLoc = mainMenu.getXLoc(subMenuName);
					EditorMenuPanel* subMenu = new EditorMenuPanel();
				}
			}
			//we already have a function by that name do nothing
			int x = 0; //debug
		}


		/*******************************************************************************
		* Function Name:   render()
		* Purpose:         Renders the menu in a vertical format
		*******************************************************************************/
		virtual void render(vector<string> items) {

			//only render main menu if it needs a refresh
			if (mainMenu->needsRefresh()) {
				mainMenu->render();
				mainMenu->refresh();
			}

			//only render sub-menu's if they need a refresh
			for (auto it = subMenus.begin(); it != subMenus.end(); it++) {
				EditorMenuPanel* menuPanel = it->second;
				if (menuPanel->needsRefresh()) {
					menuPanel->render();
					menuPanel->refresh();
				}
			}
		}

		/*******************************************************************************
		* Function Name:   needsRefresh()
		* Purpose:         Returns true if ANY of our components needs to be refreshed
		*******************************************************************************/
		bool needsRefresh() {
			bool returnVal = false;

			//check main menu
			if (mainMenu->needsRefresh()) {
				returnVal = true;
			}

			//check submenus
			for (auto it = subMenus.begin(); it != subMenus.end(); it++) {
				if (returnVal) break; //we have found that we need to be refreshed

				EditorMenuPanel* menuPanel = it->second;
				if (menuPanel->needsRefresh()) {
					returnVal = true;
					break;
				}
			}

			return returnVal;
		}

		/*******************************************************************************
		* Function Name:   processMouseEvent(MEVENT* mEvent)
		* Purpose:         Returns vector of all items in the menu.
		*******************************************************************************/
		void processMouseEvent(MEVENT* mEvent) {

			// Have the mainMenu process all mouse events
			if (mainMenu != nullptr) mainMenu->processMouseEvent(mEvent);

			//loop through all submenu's, if a submenu is visible, have it process the event
			for (auto it = subMenus.begin(); it != subMenus.end(); it++) {
				EditorMenuPanel* menuPanel = it->second;
				if (menuPanel->isVisible()) menuPanel->processMouseEvent(mEvent);
			}
		}

	//These will not be available to extended classes, or anyone else.
	private:
		EditorMenuPanel* mainMenu = nullptr;		//this is the menu bar at the top of the screen
		map<string, EditorMenuPanel*> subMenus; //our submenu's
		WINDOW* window;

	}; // end class MenuBar
} // end TextEditorNamespace

#endif