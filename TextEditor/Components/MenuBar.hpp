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

#define SUBMENU_WIDTH 15
#define SUBMENU_HEIGHT 10

#include "MenuBehaviour.hpp"
#include "EditorMenuPanel.hpp"
#include <unordered_map>

using std::unordered_map;


//void menuBarCallback(string menuData, void* this_ptr_callback);

//we are defining a class in the namespace TextEditorNamespace
namespace TextEditorNamespace {

	

	//we are defining a MenuBehaviour
	class MenuBar {

	//We may be extending this class later, these will be private for extended classes
	protected:


	//These will be public for all extended classes
	public:

		//default constructor
		MenuBar() {
			//can't be used until the real constructor is called
		}

		//constructor
		MenuBar(WINDOW* window, Location loc, Size size){
			
			//create the mainMenu
			_mainMenu = new EditorMenuPanel(window, loc, size, true, true, true);
			_window = window;
		}

		/*******************************************************************************
		* Function Name:   menuBarCallbackHelper(menuData)
		* Purpose:         Called when an item on the main menu is clicked
		*				   menuData will be the name of the item that was clicked
		*                  we need to hide ALL submenus, and then show only
		*				   the one identified by the name menuData
		*******************************************************************************/
		void menuBarCallbackHelper(string menuData) {
			//close ALL submenus
			auto it = _subMenus.begin();

			// Iterate over the _submenus using iterator
			while (it != _subMenus.end()){
				it->second->setIsVisible(false);
				//it->second->setNeedsRefresh(true);
				it++;
			}

			//now if we have an item of menuData in _submenus map, then make that item visible
			_subMenus[menuData]->setIsVisible(true);
			_subMenus[menuData]->setNeedsRefresh(true);
			_currentSubMenu = _subMenus[menuData];
		}

		/*******************************************************************************
		* Function Name:   menuCallback(string menuData, void* this_ptr_callback)
		* Purpose:         When a main menu item is clicked, this function is called
		*                  it makes sure that that corresponding submenu item pops up
		*                  and all other submenu's close.
		*******************************************************************************/
		static void menuBarCallback(string menuData, void* this_ptr_callback) {
			MenuBar* self = static_cast<MenuBar*>(this_ptr_callback); //helps decouple
			self->menuBarCallbackHelper(menuData);
		}
		

		/*******************************************************************************
		* Function Name:   addItem(string mainMenu, string subMenu, void (*callBackFunction)(string, void*))
		* Purpose:         adds an Item to the menu, with the given function
		*                  Each menu can only have 1 ITEM with the same name
		*******************************************************************************/
		void addItem(string subMenuName, string itemName, void (*callBackFunction)(string, void*), void* ptr_to_caller) {

			//check to see if itemName already exists
			auto it = _subMenus.find(itemName);
			if (it == _subMenus.end()) {

				//we have not found an item with that name, we need to add it

				//do we have a subMenu by subMenuName?
				if (_mainMenu->contains(subMenuName)) {

					//the main menu already has a submenu by that name,we can add this item to that submenu
					EditorMenuPanel* subMenu = _subMenus[subMenuName];
					subMenu->addItem(itemName, callBackFunction, ptr_to_caller);
					
				}else {

					//the main menu does not have a sub menu by that name, we have to create the sub menu and then add this item to it
					// find the x location of that value
					//int xLoc = _mainMenu->getXLoc(subMenuName);
					
					int numItems = _mainMenu->getMenuItems().size();
					Location loc = _mainMenu->getLocationOfItem(numItems, _mainMenu->getMenuItems().size()+1);
					//if (numItems == 1)
					//	loc = Location{ 5,25 };
					loc.y += 2;

					//Location loc = Location{ 3,0 };
					Size size = Size{ SUBMENU_HEIGHT, SUBMENU_WIDTH };

					//create the new subMenu
					EditorMenuPanel* submenu = new EditorMenuPanel(_window, loc, size, false, true, false);

					//add our item to it
					submenu->addItem(itemName, callBackFunction, ptr_to_caller);

					//add the submenu to our main menu, and then to our list of sub menus
					_subMenus[subMenuName] = submenu;
					_mainMenu->addItem(subMenuName, menuBarCallback, this);
					//_mainMenu->setNeedsRefresh(true);
					_subMenus[subMenuName]->setNeedsRefresh(false);
					//having trouble getting a pointer to a member variable to work
					//this is requireing a TextEditorNamespace::MenuBar::* instead of a void* as we planned, is there
					//a way to Generizie the classname itself in the addItem function

				}
			}
			//we already have a function by that name do nothing
			int x = 0; //debug
			
		}


		/*******************************************************************************
		* Function Name:   render()
		* Purpose:         Renders the menu in a vertical format
		*******************************************************************************/
		virtual void render() {

			//only render main menu if it needs a refresh
			if (_mainMenu->needsRefresh()) {
				_mainMenu->render();
				_mainMenu->refresh();
			}

			//only render sub-menu's if they need a refresh
			/*for (auto it = _subMenus.begin(); it != _subMenus.end(); it++) {
				EditorMenuPanel* menuPanel = it->second;
				//if (menuPanel->needsRefresh() && menuPanel->isVisible()) {
				if (menuPanel->needsRefresh()) {
					menuPanel->render();
					menuPanel->refresh();
				}
			}*/

			//try only rendering current submenut
			if (_currentSubMenu != nullptr) {
				if (_currentSubMenu->needsRefresh()) {
					_currentSubMenu->render();
					_currentSubMenu->refresh();
				}
				
			}
		}

		/*******************************************************************************
		* Function Name:   render()
		* Purpose:         Renders the menu in a vertical format
		*******************************************************************************/
		/*
		virtual void refresh() {

			//only render main menu if it needs a refresh
			//if (_mainMenu->needsRefresh()) {
			//_mainMenu->render();
			_mainMenu->refresh();
			//}

			//only render sub-menu's if they need a refresh
			for (auto it = _subMenus.begin(); it != _subMenus.end(); it++) {
				EditorMenuPanel* menuPanel = it->second;
				if (menuPanel->needsRefresh() && menuPanel->isVisible()) {
					//menuPanel->render();
					menuPanel->refresh();
				}
			}
		}*/

		/*******************************************************************************
		* Function Name:   needsRefresh()
		* Purpose:         Returns true if ANY of our components needs to be refreshed
		*******************************************************************************/
		bool needsRefresh() {
			bool returnVal = false;

			//check main menu
			if (_mainMenu->needsRefresh()) {
				returnVal = true;
			}

			//check submenus
			for (auto it = _subMenus.begin(); it != _subMenus.end(); it++) {
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
		int processMouseEvent(MEVENT* mEvent) {
			int returnVal = -1;
			// Have the mainMenu process all mouse events
			if (_mainMenu != nullptr) {
				int itemClicked = _mainMenu->processMouseEvent(mEvent);
				returnVal = itemClicked;

				//no item in the menu was clicked,
				//all menu items should be closed
				if (itemClicked == -2) {
					for (auto it = _subMenus.begin(); it != _subMenus.end(); it++) {
						EditorMenuPanel* menuPanel = it->second;
						if(menuPanel->isVisible())menuPanel->setIsVisible(false);
						menuPanel->render();
						menuPanel->refresh();
						//menuPanel->setNeedsRefresh(false);
						//return;
					}

					//set currentSubMenu to nullptr
					_currentSubMenu = nullptr;
				}
			}

			//loop through all submenu's, if a submenu is visible, have it process the event
			for (auto it = _subMenus.begin(); it != _subMenus.end(); it++) {
				EditorMenuPanel* menuPanel = it->second;
				if (menuPanel->isVisible()) menuPanel->processMouseEvent(mEvent);
			}
			return returnVal;
		}


	//These will not be available to extended classes, or anyone else.
	private:
		EditorMenuPanel* _mainMenu = nullptr;		//this is the menu bar at the top of the screen
		unordered_map<string, EditorMenuPanel*> _subMenus; //our submenu's
		WINDOW* _window;

		//we'll try to track the current submenu, so we can properly figure out which to render
		EditorMenuPanel* _currentSubMenu = nullptr;

		

	}; // end class MenuBar

} // end TextEditorNamespace


#endif