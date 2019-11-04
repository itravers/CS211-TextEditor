/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	October 3rd, 2019
 *
 *	Moveable.hpp - An interface that needs to be implemented by anything
 *                  that needs to be moved.
*********************************************************************************/

#ifndef MOVEABLE_HPP
#define MOVEABLE_HPP

#include "../structs.h"

//we are defining a class in the namespace TextEditorNamespace
namespace TextEditorNamespace {

	class Moveable {
	public:
		virtual void move(Location l) = 0;
	};

}

#endif // END MOVEABLE_HPP