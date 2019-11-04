/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	October 5th, 2019
 *
 *	Editable.hpp - An interface that needs to be implemented by anything
 *                  that that can be edited character by character
*********************************************************************************/

#ifndef EDITABLE_HPP
#define EDITABLE_HPP

#include "../structs.h"

//we are defining a class in the namespace TextEditorNamespace
namespace TextEditorNamespace {

	class Editable {
	public:
		virtual void putChar(char c, Location l) = 0;
		virtual char getChar(Location l) = 0;
	};
}

#endif // END EDITABLE_HPP