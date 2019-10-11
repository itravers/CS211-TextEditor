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

#include "EditorWindowMoveable.hpp"
#include "MenuBehaviour.hpp"


//we are defining a class in the namespace TextEditorNamespace
namespace TextEditorNamespace {

	//we are defining a EditorWindowScrollable, which is an extention of EditorWindowMoveable
	class EditorMenu : public EditorWindowMoveable {

		//We'll be extending this class later, these will be private for extended classes
	protected:
		MenuBehaviour menuBehaviour;			//The swappable behaviour of the menu
		vector<string> menuItems;

		//These will be public for all extended classes
	public:

		//constructor
		EditorMenu(WINDOW* parent = 0, Location location = { 0, 0 }, Size size = { 0, 0 }, bool isVisible = false, bool hasBorder = false, bool isHorizontal)
			:EditorWindowMoveable(parent, location, size, isVisible, hasBorder) {

			//initialize the menu Items
			menuItems = vector<string>();

			//check if we are horizontal or not, and initialze the proper behaviour
			if (isHorizontal) {
				menuBehaviour = MenuBehaviourHorizontal(this);
			}
			else {
				menuBehaviour = MenuBehaviourVertical(this);
			}
		}


		/*******************************************************************************
		* Function Name:   render()
		* Purpose:         Overrides the EditorWindow render()
		*				   We'll need to render our cursor, etc
		*******************************************************************************/
		virtual void render() {
			menuBehaviour.render(menuItems);
		}

		/*******************************************************************************
		* Function Name:   addItem()
		* Purpose:         Adds an item to the menu
		*******************************************************************************/
		void addItem(string item) {
			menuItems.push_back(item);
		}

		/*******************************************************************************
		* Function Name:   getMenuItems()
		* Purpose:         Returns vector of all items in the menu.
		*******************************************************************************/
		vector<string> getMenuItems() {
			return menuItems;
		}




		//These will not be available to extended classes, or anyone else.
	private:
		



	};
} // end TextEditorNamespace

#endif