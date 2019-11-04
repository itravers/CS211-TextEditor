/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	October 3rd, 2019
 *
 *	Resizable.hpp - An interface that needs to be implemented by anything 
 *                  that needs to be resized.
*********************************************************************************/

#ifndef RESIZABLE_HPP
#define RESIZABLE_HPP

#include "../structs.h"

//we are defining a class in the namespace TextEditorNamespace
namespace TextEditorNamespace {

	class Resizable {
	public:
		virtual void resize(Size s) = 0;
	};

}

#endif // END RESIZABLE_HPP