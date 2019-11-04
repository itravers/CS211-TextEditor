/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	October 5th, 2019
 *
 *	KeyboardHandler.hpp - An interface that needs to be implemented by anything
 *                  that that handle keyboard input
*********************************************************************************/

#ifndef KEYBOARD_HANDLER_HPP
#define KEYBOARD_HANDLER_HPP

#include "../structs.h"

//we are defining a class in the namespace TextEditorNamespace
namespace TextEditorNamespace {

	class KeyboardHandler {
	public:
		virtual void handleKeyboardInput(int input) = 0;
	};
}

#endif // END KEYBOARD_HANDLER_HPP