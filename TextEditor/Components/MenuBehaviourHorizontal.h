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

#include "EditorMenu.hpp"
#include "MenuBehaviour.hpp"


//we are defining a class in the namespace TextEditorNamespace
namespace TextEditorNamespace {

	//we are defining a MenuBehaviour
	class MenuBehaviourHorizontal : public MenuBehaviour {

		//We'll be extending this class later, these will be private for extended classes
	protected:


		//These will be public for all extended classes
	public:

		//constructor
		MenuBehaviourHorizontal(EditorMenu* p)
			:MenuBehaviour(p){
			//you know nothing jon snow
		}

		/*******************************************************************************
		* Function Name:   render()
		* Purpose:         Renders the menu in a horizontal format
		*******************************************************************************/
		virtual void render(vector<string> items) {
			// here is were we will do our horizontal rendering
		}

		//These will not be available to extended classes, or anyone else.
	private:

	}; // end class MenuBehaviour
} // end TextEditorNamespace

#endif