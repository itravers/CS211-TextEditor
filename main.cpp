#ifdef _WIN32
//Windows includes
#include "curses.h"
#include "panel.h"
#include "curspriv.h"
#else
//Linux / MacOS includes
#include <curses.h>
#endif
#include <string>
#include <sstream>
#include "TextEditor.h"

//test a TEvent
#include "TEvent.h"

using namespace std;

#define ctrl(x)           ((x) & 0x1f)

void draw_centered(WINDOW* win, int max_y, int max_x, string text);

int main(int argc, char* argv[]) {

	//get the filename we want to load from the command line
	string fileName = "motd.txt";	//motd.txt will be our default filename

	//check if we have a command line argument
	if (argc > 1) {

		//we do have a command line argument, we'll assume this is a filename, without checking
		fileName = argv[1];
	}

	//Contruct, Load & Run The Text Editor
	/*TextEditor textEditor = TextEditor(fileName);
	textEditor.load();
	textEditor.run();*/

	//test a TEvent
	TEvent eventTest = TEvent(DEFAULT, "test_id", "test_data");
	
}

//int main(void)
//{
//	WINDOW* main_window = nullptr;
//	int num_cols = 0;
//	int num_rows = 0;
//
//	//SETUP
//	//initialize our window
//	main_window = initscr();
//
//	//resize our window
//	resize_term(5000, 5000);
//	getmaxyx(main_window, num_rows, num_cols);
//	resize_term(num_rows - 1, num_cols - 1);
//	getmaxyx(main_window, num_rows, num_cols);
//
//	//turn keyboard echo
//	noecho();
//
//	cbreak();
//
//	//turn on keypad input
//	keypad(main_window, TRUE);
//
//	//hide the cursor
//	curs_set(FALSE);
//
//	//MAIN PROGRAM LOGIC GOES HERE
//
//	//pause for user input
//	bool keep_going = true;
//	resize_term(0, 0);
//	while (keep_going == true)
//	{
//		//clear window
//		wclear(main_window);
//
//		ostringstream temp_str{};
//		temp_str << "width: " << num_cols << " height: " << num_rows;
//		draw_centered(main_window, num_rows, num_cols, temp_str.str().c_str());
//		refresh();
//		int input = wgetch(main_window);
//
//		//Curses documentation says to use KEY_RESIZE, but you can also use
//		//is_termresized.  In real life, use either/or but not both.
//		if (is_term_resized(0, 0) == true)
//		{
//			resize_term(0, 0);
//			getmaxyx(main_window, num_rows, num_cols);
//		}
//		switch (input)
//		{
//		case ctrl('c'):
//			keep_going = false;
//		case KEY_RESIZE:
//			resize_term(0, 0);
//			getmaxyx(main_window, num_rows, num_cols);
//		}
//	}
//	//end curses mode
//	endwin();
//}
//
//void draw_centered(WINDOW* win, int max_y, int max_x, string text)
//{
//	int length = text.length();
//	int left_margin = (max_x - length) / 2;
//	int top_margin = (max_y - 1) / 2;
//	mvwprintw(win, top_margin, left_margin, text.c_str());
//}
