/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	October 1st, 2019
 *
 *	EditorWindowResizable.hpp: An extended version of EditorWindow
 *					  This class gives the editor window the ability to resize
 *  When you resize a window: if the new size is smaller than the old size
 *  your buffer will lose the data that was in it, if it is then made big
 *  again, the buffer will not have the info the was lost during the resize.
*********************************************************************************/

#ifndef EDITOR_WINDOW_RESIZABLE
#define EDITOR_WINDOW_RESIZABLE

#include "EditorWindow.hpp"
#include "Resizable.hpp"

using std::to_string;


//we are defining a class in the namespace TextEditorNamespace
namespace TextEditorNamespace {

	//we are defining a EditorWindowResizable, which is an extention of EditorWindow, and we are implementing the Resizable interface
	class EditorWindowResizable : public EditorWindow, public Resizable {

	//We'll be extending this class later, these will be private for extended classes
	protected:
		WINDOW* _parent_window = nullptr;		//we need to keep a record to our parent, because we need to be able to remake _c_window

	//These will be public for all extended classes
	public:

		//constructor
		EditorWindowResizable(WINDOW* parent = 0, Location location = { 0, 0 }, Size size = { 0, 0 }, bool isVisible = false, bool hasBorder = false)
			:EditorWindow(parent, location, size, isVisible, hasBorder), _parent_window(parent) {

			//I think we can let the Editor Window super class take care of all construction tasks?
			/*for (int i = 0; i < _size.height-2; i++) { //this is our test info
				_buffer[i] = "This is just a test : " + to_string(i);
			}*/

			//resize the buffer to the right size after we changed it
			resizeBuffer(_buffer, _size);
		}

		virtual void resize(Size s) {

			//erase everything in the current window
			werase(_c_window);
			
			//save our new size
			_size = s;

			//Resize our buffer
			resizeBuffer(_buffer, _size);

			//first delete our current window, you must create new _c_window IMMEDIATELY AFTER DOING THIS
			delwin(_c_window);
			

			//create a new window with our new size, MUST BE DONE IMMEDIATELY AFTER delwin
			_c_window = subwin(_parent_window, _size.height, _size.width, _location.y, _location.x);

			//reset our panel to our new window
			replace_panel(_c_panel, _c_window);

			//set that we need to be refreshed, so we end up getting rendered in next loop
			setNeedsRefresh(true);
		}



	//These will not be available to extended classes, or anyone else.
	private:
		void resizeBuffer(vector<string> buf, Size s) {

			//create a blank string the size of our new line, if we have to insert a new blank line
			string blankLine = string(s.width, ' ');

			//resize the number of lines in our buffer
			_buffer.resize(s.height, blankLine);

			//now we need to make sure every line is exactly newNumCols in length
			for (int i = 0; i < _buffer.size(); i++) {
				string line = _buffer[i];
				line.resize(s.width, ' ');
				_buffer[i] = line;
			}
		}
	};
} // end TextEditorNamespace

#endif