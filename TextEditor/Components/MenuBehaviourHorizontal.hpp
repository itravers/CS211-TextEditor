#/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	October 11th, 2019
 *
 *	MenuBehaviourHorizontal.hpp: Extends menu behaviour
 *                               responsible for rendering a menu in a horizontal
 *                               format.
*********************************************************************************/

#ifndef MENU_BEHAVIOUR_HORIZONTAL_HPP
#define MENU_BEHAVIOUR_HORIZONTAL_HPP

#include "MenuBehaviour.hpp"




//we are defining a class in the namespace TextEditorNamespace
namespace TextEditorNamespace {
	//class EditorWindow;

	//we are defining a MenuBehaviour
	class MenuBehaviourHorizontal : public MenuBehaviour {

		//We'll be extending this class later, these will be private for extended classes
	protected:


		//These will be public for all extended classes
	public:

		//constructor
		MenuBehaviourHorizontal(vector<string>&_buf)
			:MenuBehaviour(_buf) {
			//you know nothing jon snow
		}

		/*******************************************************************************
		* Function Name:   menuClicked()
		* Purpose:         Extending classes will need to implement their own menuClicked
		*                  If a Menu is clicked this should return the index of that
		*                  menu. If a menu is not clicked, it should return -1.
		*                  If the menu IS clicked, but no menu items are clicked
		*                  we'll return a -2
		*******************************************************************************/
		virtual int menuClicked(MEVENT* mEvent, vector<string> items, bool has_border, Location loc) {
			int returnVal = -1;		//returns -1 if the menu was not clicked
			int margin = 0;			//the difference between the left most buffer area and the left most screen area

			if (has_border)margin++;		//if we have a border the margin is increased by 1

			float fracOfScreen = 1 / (float)items.size();
			int itemWidth = fracOfScreen * _parent_buffer[0].size();
			int x = loc.x + margin;

			//first check if we have clicked on the menu in a horizontal fashion
			//this will only work if mEvent was clicked at a y that is loc.y + margin
			if (mEvent->y == loc.y + margin) {
				returnVal = -2; //we have clicked on the menu, but maybe not on a menu item.

				// The line the menu is on was clicked, now we have to see if we clicked
				// on any items in the menu.

				//loop item by item and see if we clicked on it
				for (int i = 0; i < items.size(); i++) {

					//define a start and end x and see if we have clicked between them inclusively, return that index
					if (mEvent->x >= x && mEvent->x <= (x + items.at(i).size()-1)) { //between start of word and end of word

						//we found that we HAVE clicked the menu item at index i, so we'll return that.
						return i;
					}

					//Increase the first index we will look for the next word at.
					x = x + itemWidth;
				}
			}

			return returnVal;
		}

		/*******************************************************************************
		* Function Name:   getLocationOfItem(string item)
		* Purpose:         Returns the location of the first character
		*                  of a menu item
		*******************************************************************************/
		virtual Location getLocationOfItem(int itemNum, vector<string>items) {
			int x = 0;
			float fracOfScreen = 1 / (float)items.size();
			int itemWidth = fracOfScreen * _parent_buffer[0].size();
			return Location{ 0, itemWidth * itemNum };
		}

		/*******************************************************************************
		* Function Name:   render()
		* Purpose:         Renders the menu in a horizontal format
		*******************************************************************************/
		virtual void render(vector<string> items) {
			// here is were we will do our horizontal rendering                    ";
			
			int x = 0;
			float fracOfScreen = 1 / (float)items.size();
			int itemWidth = fracOfScreen * _parent_buffer[0].size();

			string displayString = "";

			for (int i = 0; i < items.size(); i++) {
				
				//make sure it is large enough
				while (displayString.size() <= x) displayString += ' ';
				displayString.insert(x, items[i]);
				x = x + itemWidth;
			}
			
				imprintStringOnBuffer(displayString, 0, 0);
		}

		//These will not be available to extended classes, or anyone else.
	private:

	}; // end class MenuBehaviourHorizontal
} // end TextEditorNamespace

#endif