#/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	October 11th, 2019
 *
 *	MenuBehaviour.hpp: Encapsulates the behaviour of a menu
 *                     This is using the strategy class
 *                     Each menu has a menu behaviour, the behaviour decides
 *                     how the menu will be rendered. Each behaviour can
 *                     render the menu in a different way.
*********************************************************************************/

#ifndef MENU_BEHAVIOUR_HPP
#define MENU_BEHAVIOUR_HPP

#include "EditorWindowMoveable.hpp"
#include "MenuBehaviour.hpp"


//we are defining a class in the namespace TextEditorNamespace
namespace TextEditorNamespace {

	//we are defining a MenuBehaviour
	class MenuBehaviour {

		//We'll be extending this class later, these will be private for extended classes
	protected:
		EditorMenu* parent;



		//These will be public for all extended classes
	public:

		//constructor
		MenuBehaviour(EditorMenu* p) {
			parent = p;
		}

		/*******************************************************************************
		* Function Name:   render()
		* Purpose:         Extending classes will need to implement their own render
		*******************************************************************************/
		virtual void render() = 0;

		//These will not be available to extended classes, or anyone else.
	private:

	}; // end class MenuBehaviour
} // end TextEditorNamespace

#endif