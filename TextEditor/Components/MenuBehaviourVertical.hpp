#/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	October 13th, 2019
 *
 *	MenuBehaviourVertical.hpp:   Extends menu behaviour
 *                               responsible for rendering a menu in a vertical
 *                               format.
*********************************************************************************/

#ifndef MENU_BEHAVIOUR_VERTICAL_HPP
#define MENU_BEHAVIOUR_VERTICAL_HPP

#include "MenuBehaviour.hpp"

//we are defining a class in the namespace TextEditorNamespace
namespace TextEditorNamespace {
	//class EditorWindow;

	//we are defining a MenuBehaviour
	class MenuBehaviourVertical : public MenuBehaviour {

		//We'll be extending this class later, these will be private for extended classes
	protected:


		//These will be public for all extended classes
	public:

		//constructor
		MenuBehaviourVertical(vector<string>& _buf)
			:MenuBehaviour(_buf) {
			//you know nothing jon snow
		}

		/*******************************************************************************
		* Function Name:   menuClicked()
		* Purpose:         Extending classes will need to implement their own menuClicked
		*                  If a Menu is clicked this should return the index of that
		*                  menu. If a menu is not clicked, it should return -1.
		*******************************************************************************/
		virtual int menuClicked(MEVENT* mEvent, vector<string> items, bool has_border, Location loc) {
			int returnVal = -1;		//returns -1 if the menu was not clicked
			int margin = 0;			//the difference between the left most buffer area and the left most screen area

			if (has_border)margin++;		//if we have a border the margin is increased by 1
			int y = loc.y + margin;

			//check to make sure we have clicked on an item
			if (mEvent->y >= loc.y + margin && mEvent->y <= loc.y + margin + items.size() - 1) {

				//we have clicked in the menu
				//int candidate_returnVal = mEvent->y - margin;
				int candidate_returnVal = mEvent->y - loc.y - margin;

				//now check that we are actually clicking on a word itself
				int startx = loc.x + margin;
				int endx = startx + items[candidate_returnVal].size() - 1;

				//check if we are within x values
				if (mEvent->x >= startx && mEvent->x <= endx) {

					//we are, set this index as our return index.
					returnVal = candidate_returnVal;
				}
			}

			return returnVal;
		}

		/*******************************************************************************
		* Function Name:   render()
		* Purpose:         Renders the menu in a vertical format
		*******************************************************************************/
		virtual void render(vector<string> items) {

			// here is were we will do our horizontal rendering 
			for (int i = 0; i < items.size(); i++) {
				imprintStringOnBuffer(items[i], i, 0);
			}
		}

		//These will not be available to extended classes, or anyone else.
	private:

	}; // end class MenuBehaviourHorizontal
} // end TextEditorNamespace

#endif