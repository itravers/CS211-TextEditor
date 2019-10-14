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

	//we are defining a MenuBehaviour
	class MenuBehaviourVertical : public MenuBehaviour {

		//We'll be extending this class later, these will be private for extended classes
	protected:


		//These will be public for all extended classes
	public:

		//constructor
		MenuBehaviourVertical(EditorMenu* p)
			:MenuBehaviour(p) {
			//you know nothing jon snow
		}

		/*******************************************************************************
		* Function Name:   render()
		* Purpose:         Renders the menu in a vertical format
		*******************************************************************************/
		virtual void render(vector<string> items) {
			// here is were we will do our vertical rendering
		}

		//These will not be available to extended classes, or anyone else.
	private:

	}; // end class MenuBehaviourVertical
} // end TextEditorNamespace

#endif