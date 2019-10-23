#/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	October 11th, 2019
 *
 *	EditorMenu.hpp: A class that keeps track of a menu
 *                  A menu has multiple menu items,
 *                  each menu item is associated with a function.
 *                  when a menu item is selected, the associated function is called
 *                  Menus can have different behaviours that can be swapped out
 *                  each behaviour defines how the menu is layed out and 
 *                  also whether a clicked has happened.
 *					We use the "Strategy Design Pattern" to implement menu behviours.
*********************************************************************************/

#ifndef EDITOR_MENU
#define EDITOR_MENU

#define ITEM_LIMIT 10

#include "EditorWindowMoveable.hpp"
#include "MenuBehaviourHorizontal.hpp"
#include "MenuBehaviourVertical.hpp"
#include <algorithm>


//we are defining a class in the namespace TextEditorNamespace
namespace TextEditorNamespace {

	//we are defining a EditorWindowScrollable, which is an extention of EditorWindowMoveable
	class EditorMenuPanel : public EditorWindowMoveable {

		//We'll be extending this class later, these will be private for extended classes
	protected:
		void (*callback[ITEM_LIMIT])(string, void*);		//An Array of Callback functions of the form void name(string, void*) - The service callback pattern
		void* callback_pnt_to_caller[ITEM_LIMIT];			//An array of pointers to the caller, used to call the callback fucntion
		MenuBehaviour* menuBehaviour;						//The swappable behaviour of the menu - Uses the strategy pattern.
		vector<string> menuItems;							//The Individual Menu Items

		//These will be public for all extended classes
	public:

		//constructor
		EditorMenuPanel(WINDOW* parent = 0, Location location = { 0, 0 }, Size size = { 0, 0 }, bool isVisible = false, bool hasBorder = false, bool isHorizontal = true)
			:EditorWindowMoveable(parent, location, size, isVisible, hasBorder) {

			//initialize the menu Items
			menuItems = vector<string>();

			//check if we are horizontal or not, and initialze the proper behaviour
			if (isHorizontal) {
				menuBehaviour =  new MenuBehaviourHorizontal(_buffer);
			}
			else {
				menuBehaviour = new MenuBehaviourVertical(_buffer);
			}
		}

		/*******************************************************************************
		* Function Name:   render()
		* Purpose:         Overrides the EditorWindow render()
		*				   We'll need to render our cursor, etc
		*******************************************************************************/
		virtual void render() {

			//now render our menu items
			menuBehaviour->render(menuItems);

			//render our super class
			EditorWindowMoveable::render();
		}

		/*******************************************************************************
		* Function Name:   getLocationOfItem()
		* Purpose:         Returns the location of the first char of a menu item
		*******************************************************************************/
		Location getLocationOfItem(int itemNum) {
			return menuBehaviour->getLocationOfItem(itemNum, menuItems);
		}


		/*******************************************************************************
		* Function Name:   contains()
		* Purpose:         Returns true if our menu panel holds an
		*                  item by the name of "item".
		*******************************************************************************/
		bool contains(string item) {
			bool returnVal = false;

			if (std::find(menuItems.begin(), menuItems.end(), item) != menuItems.end()) {
				/* v contains x */
				returnVal = true;
			}

			return returnVal;
		}

		/*******************************************************************************
		* Function Name:   addItem()
		* Purpose:         Adds an item to the menu
		*                  with the specified callback function a "void nameOfFunc(string menuData, void* ptrToCaller)" function
		*******************************************************************************/
		void addItem(string item, void (*callBackFunction)(string, void*), void* ptr_to_caller) {
			int place = menuItems.size();						//where are we saving this callback function
			callback[place] = callBackFunction;					//save it there
			callback_pnt_to_caller[place] = ptr_to_caller;
			menuItems.push_back(item);
			//setNeedsRefresh(true);
		}

		//static_cast<void*>(

		/*******************************************************************************
		* Function Name:   getMenuItems()
		* Purpose:         Returns vector of all items in the menu.
		*******************************************************************************/
		vector<string> getMenuItems() {
			return menuItems;
		}

		/*******************************************************************************
		* Function Name:   processMouseEvent(MEVENT* mEvent)
		* Purpose:         Processes a mouseEvent, returns the index of item
		*                  that may have been clicked on, -1 for this menu
		*				   wasn't clicked on at all, and -2 for this menu was clicked
		*                  on, but no items were
		*******************************************************************************/
		int processMouseEvent(MEVENT* mEvent) {
			int returnVal = -1;

			//we don't process any mouse events if we are not visible.
			if (isVisible()) {

				//let the menubehaviour tell us if we have clicked an item
				//int itemNumClicked = menuBehaviour->menuClicked(mEvent); //returns -1 if the menu wasn't clicked, and the index if so
				int itemNumClicked = menuBehaviour->menuClicked(mEvent, menuItems, hasBorder(), _location);
				returnVal = itemNumClicked;

				//check to see if any item was clicked
				if (itemNumClicked >= 0) {

					//an item was clicked, call its callback function
					callback[itemNumClicked](menuItems.at(itemNumClicked), callback_pnt_to_caller[itemNumClicked]);
				}
			}
			return returnVal;
		}

		//These will not be available to extended classes, or anyone else.
	private:
		

	};
} // end TextEditorNamespace

#endif