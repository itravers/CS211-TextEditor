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
		//MenuBehaviourHorizontal(EditorMenu* p)
		//	:MenuBehaviour(p) {
		MenuBehaviourHorizontal(vector<string>&_buf)
			:MenuBehaviour(_buf) {
			//you know nothing jon snow
			//parent = p;
		}

		/*******************************************************************************
		* Function Name:   render()
		* Purpose:         Renders the menu in a horizontal format
		*******************************************************************************/
		virtual void render(vector<string> items) {
			// here is were we will do our horizontal rendering

			//render our super class
			//parent->imprintStringOnBuffer("test", 0, 0);
			//_parent_buffer[1] = 'h';
			//_parent_buffer.at(2) = "h                       ";
			
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