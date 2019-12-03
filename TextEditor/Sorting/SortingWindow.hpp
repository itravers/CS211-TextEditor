#ifndef SORTING_WINDOW
#define SORTING_WINDOW

#define WORDS_PER_COLUMN

#include "../Components/EditorComponent.hpp"
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace TextEditorNamespace {
	class SortingWindow : public EditorComponent {
	private:
		vector<string> _data;
		int _numCols;


	public:
		SortingWindow(WINDOW* parent = 0, Location location = { 0, 0 }, Size size = { 0, 0 }, int nnumCols = 0, bool isVisible = false)
			:EditorComponent(parent, location, size, isVisible), _numCols(nnumCols) {

			setNeedsRefresh(false);

			//data test
			_data.push_back("hello");
			_data.push_back("there");

			//check to see if the parent is null, if not, create our window as a subwindow
			if (parent != nullptr) {

				//create our components window
				_c_window = subwin(parent, size.height, size.width, _location.y, _location.x);

				//create our components panel
				_c_panel = new_panel(_c_window);

		
			}
		}

		virtual void render() {
			if (isVisible()) {

				//erase the window first
				werase(_c_window);

				//create the border
				colorbox(_c_window, COLOR_GREEN_BLACK, true);
				int y = 1;
				//loop through each item in data
				for (int i = 0; i < _data.size(); i++) {
					int x = 1;
					

					for (int j = 0; j < _data[i].size(); j++) {

						wattron(_c_window, COLOR_PAIR(COLOR_WHITE_BLACK));
						wmove(_c_window, y, x);
						waddch(_c_window, (int)_data[y - 1].at(x - 1));
						wattroff(_c_window, COLOR_PAIR(COLOR_WHITE_BLACK));
						x++;
					}
					y++;
					
				}

				//we do have a border
				//loop through each line
				/*for (int y = 1; y < getSize().height - 1; y++) { //we won't print on the first or last line, because the border is there

					//loop through each character in the line
					for (int x = 1; x < _data[y].size() + 1 && x < getSize().width - 2; x++) {
						wattron(_c_window, COLOR_PAIR(COLOR_WHITE_BLACK));
						wmove(_c_window, y, x);
						waddch(_c_window, (int)_data[y - 1].at(x - 1));
						wattroff(_c_window, COLOR_PAIR(COLOR_WHITE_BLACK));
					}
				}*/
			}
		}

			/*
				This function was not written by me. I adapted it from the colorbox function in tui.c
				that the teacher supplied.
			*/
			void colorbox(WINDOW * win, chtype color, int hasbox)
			{
				int maxy;
#ifndef PDCURSES
				int maxx;
#endif
				chtype attr = color & A_ATTR;  /* extract Bold, Reverse, Blink bits */

				setcolor(win, color);

#ifdef A_COLOR
				if (has_colors())
					wbkgd(win, COLOR_PAIR(color & A_CHARTEXT) | (attr & ~A_REVERSE));
				else
#endif
					wbkgd(win, attr);

				werase(win);

#ifdef PDCURSES
				maxy = getmaxy(win);
#else
				getmaxyx(win, maxy, maxx);
#endif
				if (hasbox && (maxy > 2))
					box(win, 0, 0);

				touchwin(win);
				wrefresh(win);
			}

			/*
				This function was not written by me. I adapted it from the setcolor
				function in tui.c, supplied by the teacher.
			*/
			void setcolor(WINDOW* win, chtype color)
			{
				chtype attr = color & A_ATTR;  /* extract Bold, Reverse, Blink bits */

#ifdef A_COLOR
				attr &= ~A_REVERSE;  /* ignore reverse, use colors instead! */
				wattrset(win, COLOR_PAIR(color & A_CHARTEXT) | attr);
#else
				attr &= ~A_BOLD;     /* ignore bold, gives messy display on HP-UX */
				wattrset(win, attr);
#endif
			}
	};
}




#endif