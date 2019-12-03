#ifndef SORTING_WINDOW
#define SORTING_WINDOW

#include "../Components/EditorComponent.hpp"
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace TextEditorNamespace {
	class SortingWindow : public EditorComponent {
	private:
		vector<string> data;
		int numCols;
		int numRows;

		//do we have a border
		bool _hasBorder;

	public:
		SortingWindow(WINDOW* parent = 0, Location location = { 0, 0 }, Size size = { 0, 0 }, int nnumCols = 0, int nnumRows = 0,  bool isVisible = false, bool hasBorder = false)
			:EditorComponent(parent, location, size, isVisible), _hasBorder(hasBorder), numCols(nnumCols), numRows(nnumRows) {

			//check to see if the parent is null, if not, create our window as a subwindow
			if (parent != nullptr) {

				//create our components window
				_c_window = subwin(parent, size.height, size.width, _location.y, _location.x);

				//create our components panel
				_c_panel = new_panel(_c_window);

				//Do we want our Component to be visible? //Set it up now, beyond the auto constructor
				if (_isVisible) {
					setIsVisible(true);
				}
				else {
					setIsVisible(false);
				}
			}
		}

		virtual void render() {

		}
	};
}




#endif