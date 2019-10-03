#/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	October 1st, 2019
 *
 *	EditorWindowMovable.hpp: An extended version of EditorWindowResizable
 *					  This class further extends the ability of an Editor
 *					  window to be moved.
*********************************************************************************/

#ifndef EDITOR_WINDOW_MOVABLE
#define EDITOR_WINDOW_MOVABLE

#include "EditorWindowResizable.hpp"
#include "Moveable.hpp"

using std::to_string;


//we are defining a class in the namespace TextEditorNamespace
namespace TextEditorNamespace {

	//we are defining a EditorWindowMovable, which is an extention of EditorWindowResizable, and we are implmenting the Movable interface
	class EditorWindowMoveable : public EditorWindowResizable, public Moveable {

		//We'll be extending this class later, these will be private for extended classes
	protected:

	//These will be public for all extended classes
	public:

		//constructor
		EditorWindowMoveable(WINDOW* parent = 0, Location location = { 0, 0 }, Size size = { 0, 0 }, bool isVisible = false, bool hasBorder = false)
			:EditorWindowResizable(parent, location, size, isVisible, hasBorder) {

		}

		virtual void move(Location l) {

			//erase what is currently in our window
			werase(_c_window);

			//remember new location
			_location = l;

			//tell the panel to move
			move_panel(_c_panel, l.y, l.x);

			//update all panels
			update_panels();

			//refresh next loop
			setNeedsRefresh(true);
		}



		//These will not be available to extended classes, or anyone else.
		private:
		
	};
} // end TextEditorNamespace

#endif