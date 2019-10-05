/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	October 5th, 2019
 *
 *	Scrollable.hpp - An interface that needs to be implemented by anything
 *                  that that can be scrolled
*********************************************************************************/

#ifndef SCROLLABLE_HPP
#define SCROLLABLE_HPP

#include "../structs.h"

//we are defining a class in the namespace TextEditorNamespace
namespace TextEditorNamespace {

	class Scrollable {
	public:
		virtual Location getScrollLocation() = 0;
		virtual void setScrollLocation(Location l) = 0;
		virtual void incrementScroll(char xOry) = 0;
		virtual void decrementScroll(char xOry) = 0;
	};
}

#endif // END SCROLLABLE_HPP