#ifndef SORTING_WINDOW
#define SORTING_WINDOW

#define WORDS_PER_COLUMN


#include <string>
#include <vector>
#include <chrono>
#include "../Components/EditorComponent.hpp"
#include "MovingLabel.hpp"

using std::string;
using std::vector;
using namespace std::chrono_literals;
using std::chrono::high_resolution_clock;

namespace TextEditorNamespace {
	class SortingWindow : public EditorComponent {
	private:
		vector<string> _words;
		vector<MovingLabel*> _labels;
		int _numCols;


	public:
		SortingWindow(WINDOW* parent = 0, Location location = { 0, 0 }, Size size = { 0, 0 }, int nnumCols = 0, bool isVisible = false)
			:EditorComponent(parent, location, size, isVisible), _numCols(nnumCols) {

			if (_numCols == 0) _numCols = 5;
			setNeedsRefresh(false);

			_words.push_back("Hello");
			_words.push_back("there");
			_words.push_back("How");
			_words.push_back("are");
			_words.push_back("you");
			_words.push_back("doing");
			_words.push_back("this");
			_words.push_back("is");
			_words.push_back("a");
			_words.push_back("test");
			_words.push_back("hello");
			_words.push_back("there");
			_words.push_back("How");
			_words.push_back("are");
			_words.push_back("you");
			_words.push_back("doing");
			_words.push_back("this");
			_words.push_back("is");
			_words.push_back("a");
			_words.push_back("test");
			_words.push_back("hello");
			_words.push_back("there");
			_words.push_back("How");
			_words.push_back("are");
			_words.push_back("you");
			_words.push_back("doing");
			_words.push_back("this");
			_words.push_back("is");
			_words.push_back("a");
			_words.push_back("test");
			_words.push_back("hello");
			_words.push_back("there");
			_words.push_back("How");
			_words.push_back("are");
			_words.push_back("you");
			_words.push_back("doing");
			_words.push_back("this");
			_words.push_back("is");
			_words.push_back("a");
			_words.push_back("test");


			//how many spaces per column are we writing?
			int numSpacesPerColumn = getSize().width / _numCols;
			int col = 0;
			int row = 0;

			//put each word into a label, that will be displayed at a certain location
			for (int i = 0; i < _words.size(); i++) {

				int curCol = i % (_numCols);
				if (i > 0 && curCol == 0) {

					//we change our row
					row++;
					col = 0;
				}else if (i == 0) {
					col = 0;
				}else {
					//we stay on the same row, we go to next column
					//int curCol = i % _numCols;
					//curCol++;
					col = curCol;
					col *= numSpacesPerColumn;
				}
			
				_labels.push_back(new MovingLabel(_words[i], Vector2<float>(col, row)));
			}
		

		


			//check to see if the parent is null, if not, create our window as a subwindow
			if (parent != nullptr) {

				//create our components window
				_c_window = subwin(parent, size.height, size.width, _location.y, _location.x);

				//create our components panel
				_c_panel = new_panel(_c_window);

		
			}
		}

		//move label at index p1, to position p2
		void moveTo(int labelIndex, Vector2 <float> newlabelPosition) {
			MovingLabel* label = _labels[labelIndex];
			int labelRow = label->getLoc().y;
			int labelCol = label->getLoc().x;
			int moveToRow = newlabelPosition.y;
			int moveToCol = newlabelPosition.x;

			//this is our main text animation loop
			label->setMovingTo(Vector2<float>(100, label->getLoc().y));
			label->setVel(Vector2<float>(10.0f, .0f));

			// we use a fixed timestep of 1 / (60 fps) = 16 milliseconds
			constexpr std::chrono::nanoseconds timestep(16ms);
			std::chrono::nanoseconds lag(0ns);
			auto time_start = high_resolution_clock::now();


			while (true){
				//clear();
				//refresh();

				auto delta_time = high_resolution_clock::now() - time_start;
				time_start = high_resolution_clock::now();
				//lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);
				std::chrono::milliseconds elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(delta_time);
				
					//update all labels
					for (int i = 0; i < _labels.size(); i++) {
						//_labels[i]->update(elapsedTime.count());
						_labels[i]->update(elapsedTime.count());

					}

					//wclear(_c_window);

					//and render
					render();
				
					//clear();

					wrefresh(_c_window);
					refresh();
				

			}
		}

		virtual void render() {
			werase(_c_window);
			

			//don't render if this window isn't visible
			if (isVisible()) {

				//how many spaces per column are we writing?
				//int numSpacesPerColumn = getSize().width / _numCols;

				//loop through _labels and print them out
				for (int i = 0; i < _labels.size(); i++) {

					//if (i == 0)cout << "render: " << _labels[i]->getLoc().x << endl;

					//Get the label
					MovingLabel* label = _labels[i];

					//column and row of this word
					int col = label->getLoc().x;
					int row = label->getLoc().y;
					string word = label->getText();
					//int x = col * numSpacesPerColumn;
					int x = col;
					//print out our label
					for (int j = 0; j < word.size(); j++) { //letter by letter, j track letter in a word
			
						wattron(_c_window, COLOR_PAIR(COLOR_WHITE_BLACK));
						wmove(_c_window, row, x);
						waddch(_c_window, word[j]);
						wattroff(_c_window, COLOR_PAIR(COLOR_WHITE_BLACK));
						x++;
					}
				}
			}

		}

		/*
		virtual void render() {
			if (isVisible()) {

				//erase the window first
				werase(_c_window);

				//create the border
				colorbox(_c_window, COLOR_GREEN_BLACK, true);
				int y = 1;
				int x = 1;
				int numSpacesPerColumn = getSize().width / _numCols;
				
				//we print each word out in a row, column by column,
				//when we are out of columns, we do another row.
				for (int i = 0; i < _data.size(); i++) { //i is counting words in our list

					

					int curCol = i % (_numCols);

					if (i > 0 && curCol == 0) {

						//we change our row
						y++;
						x = 1;
					}
					else if (i == 0) {
						x = 1;
					}else {
						//we stay on the same row, we go to next column
						//int curCol = i % _numCols;
						//curCol++;
						x = curCol * numSpacesPerColumn;
					}

					//print a word out
					for (int j = 0; j < _data[i].size(); j++) { //letter by letter, j track letter in a word
						wattron(_c_window, COLOR_PAIR(COLOR_WHITE_BLACK));
						wmove(_c_window, y, x);
						waddch(_c_window, (int)_data[i].at(j));
						wattroff(_c_window, COLOR_PAIR(COLOR_WHITE_BLACK));
						x++;
					}
					
				}

			}
		}
		*/
		

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