/**
	Isaac Travers
	CIS 211 - Data Structures
	August 30th, 2019
	Homework Assignment 1

	Get used to using the curses api.
	Get used to git & githubs issues and project tracking.
	Design the gui to a basic text editor.
	This was based on a template supplied by the teacher and expanded from there.
*/

/* Defines */
#define PDC_DLL_BUILD 1			//Used for Curses
#define A_ATTR (A_ATTRIBUTES)
#define ctrl(x) ((x) & 0x1f)	//CTRL-x masking

/* Includes */
#include "curses.h"
#include "panel.h"
#include "customcolors.h"
#include "MenuController.h"
#include "FileController.h"
#include "ContentController.h"
#include "DialogBox.h"
#include <string>
#include <iostream>
#include <stdio.h>

/* Namespaces */
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::to_string;

/* Function Prototypes*/
void initColor(void);			// Initialize the Color System
void drawBorder(int, int);		// Border around the screen
void drawStatus(int, int);		// Draws the status bar at the bottom of the screen
void drawScreen(int, int);		// Draws everything associated with the screen.
void changeStatus(string);		// Changes the status screen that gets printed at the bottom.
void writeLines(vector<string>);// Writes the lines from the file to the screen
void processMainMouseEvent(MEVENT*, int, int);// processes a mouse event
static void colorbox(WINDOW*, chtype, int);	// Creates a color box around given window, 1 for visible

/* Objects */
FileController fileController;
MenuController menuController;
ContentController contentController;
DialogBox dialogBox;
static WINDOW* titleWindow;

/* Variables */
string currentStatus = "Starting Program...";

/* Start of the Program. */
int main(int argc, char* argv[]) {
	string arg1;

	//Setup Window
	int numRows = 0;
	int numCols = 0;

	//Initialze Curses
	WINDOW* mainWindow = nullptr;
	
	//initialize screen to begin curses mode
	mainWindow = initscr();

	//set up all the color pairs
	initColor();

	//go near-full screen
	getmaxyx(mainWindow, numRows, numCols);
	resize_term(numRows - 1, numCols - 1);
	getmaxyx(mainWindow, numRows, numCols);

	//turn off key echo
	noecho();
	nodelay(mainWindow, TRUE);
	keypad(mainWindow, TRUE);
	
	//i cause everything
	curs_set(0);

	//Initialize File Controller
	FileController fileController;

	//Initialize Menu Controller
	MenuController menuController(mainWindow, numRows, numCols);

	//Initialize the Content Controller
	ContentController contentController(mainWindow, numRows, numCols);

	//Initialize the Dialog Box
	DialogBox dialogBox(mainWindow, "", DIALOG_Y, DIALOG_X, DIALOG_NUM_ROWS, DIALOG_NUM_COLUMNS);

	//setup mouse
	mousemask(ALL_MOUSE_EVENTS, NULL);

	//read in the file from the command line
	string fileName = "motd.txt";
	if (argv[1]) fileName = argv[1];
	vector<string>lines;
	fileController.readFile(fileName, lines, READ, changeStatus);
	contentController.displayContents(lines);
	drawScreen(numRows, numCols);
	
	MEVENT event;
	int c;
	string dialogString; //used for dialog input
	vector<string>linesToSave;

	//THIS IS OUR MAIN LOOP
	while ((c = wgetch(mainWindow)) != KEY_END) {
		
		switch (c) {
			case KEY_UP:
				contentController.moveCursorUp();
				break;
			case KEY_DOWN:
				contentController.moveCursorDown();
				break;
			case KEY_LEFT:
				contentController.moveCursorLeft();
				break;
			case KEY_RIGHT:
				contentController.moveCursorRight();
				break;
			case ctrl('f'):
				menuController.setMenuState(MENU_FILE_OPEN);
				break;
			case ctrl('e'):
				menuController.setMenuState(MENU_EDIT_OPEN);
				break;
			case ctrl('v'):
				menuController.setMenuState(MENU_VIEW_OPEN);
				break;
			case ctrl('t'):
				menuController.setMenuState(MENU_TOOLS_OPEN);
				break;
			case ctrl('h'):
				menuController.setMenuState(MENU_HELP_OPEN);
				break;
			case ctrl('d'):
				menuController.setMenuState(MENU_CLOSED);
				break;
			case ctrl('b'):
				dialogString = dialogBox.displayDialogBox("What is your FIRST name:");
				dialogBox.hide();
				contentController.displayContents(); //must call this after dialogBox.hide();
				changeStatus("My Name is: " + dialogString);
				break;
			case ctrl('c'):
				nodelay(mainWindow, TRUE);
				keypad(mainWindow, TRUE);
				mvaddstr(0, 0, "Press ANYKEY to continue...");
				endwin();

				return 0;
				break;
			case ctrl('s'):

				//get filename from user
				dialogString = dialogBox.displayDialogBox("Save File As: ");
				dialogBox.hide(); //hide box
				contentController.displayContents(); //must be called after dialogBox.hide() to delete it

				//get file data from content controller
				contentController.getCurrentLines(linesToSave);
				fileController.writeFile(dialogString, linesToSave, changeStatus);
				changeStatus("Saving File As: " + dialogString);
				break;
			case ctrl('r'): //test saveAs

				//saveAsClicked();
				break;
			case KEY_MOUSE:
					//changeStatus("key mouse");
					if (nc_getmouse(&event) == OK) {
						processMainMouseEvent(&event, numRows, numCols);
					}
				break;
			case KEY_ENTER:
				contentController.moveCursorDown();
				break;
			case 'a': case 'b': case 'c': case ' ' : default:
				changeStatus("typed: " + to_string(c));
				contentController.insertChar(c);
				contentController.moveCursorRight();
				break;
			case -1:
				//do nothing if nothing is hit
				break;
			
		}
		refresh();
		drawScreen(numRows, numCols);
	}

	refresh(); //Tells Curses to Draw
	
	//revert back to normal console mode
	nodelay(mainWindow, TRUE);
	keypad(mainWindow, TRUE);
	mvaddstr(0, 0, "Press ANYKEY to continue...");
	char pause;//
	cin >> pause;
	endwin();

	return 0;
}

/*
	Draws everything currently on the screen.
*/
void drawScreen(int numRows, int numCols) {
	drawBorder(numRows, numCols);
	menuController.drawMenu(numRows, numCols);
	//dialogBox.draw();
	drawStatus(numRows, numCols);
}

/*
	Draws a status to the bottom of the screen.
*/
void drawStatus(int numRows, int numCols) {
	int xoffset = 1;
	attron(COLOR_PAIR(COLOR_STATUS_PAIR));
	mvaddstr(numRows-1, xoffset, currentStatus.c_str());
	attroff(COLOR_PAIR(COLOR_STATUS_PAIR));
}



/*
	Draws a border to the screen
*/
void drawBorder(int numRows, int numCols) {
	//main Program here
	for (int i = 0; i < numCols; i++) {
		//top border
		mvaddch(1, i, ACS_CKBOARD);

		//bottom border
		mvaddch(numRows - 2, i, ACS_CKBOARD);
	}

	for (int i = 0; i < numRows; i++) {
		//left column border
		mvaddch(i, 0, ACS_CKBOARD);

		//right column border
		mvaddch(i, numCols - 1, ACS_CKBOARD);
	}
}

/*
	Sets up the color pairs so we can use the COLOR_*_PAIR defines later. 
*/
void initColor(void){
	start_color();
	init_pair(COLOR_MAIN_PAIR, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_TITLE_PAIR, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_STATUS_PAIR, COLOR_RED, COLOR_BLACK);
	init_pair(COLOR_MENU_PAIR, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_CURSOR_PAIR, COLOR_BLACK, COLOR_WHITE);
	init_pair(COLOR_SCROLLBAR_PAIR, COLOR_BLACK, COLOR_GREEN);
	init_pair(COLOR_WORDWRAP_PAIR, COLOR_GREEN, COLOR_BLACK);
}

/*
	Changes the current status to a new status.
	Printed at the bottom of screen in status bar.
*/
void changeStatus(string newStatus) {
	currentStatus = newStatus + "                 ";
}

/*
	Writes out the lines in vector to the screen, exactly
	how it was read in
*/
void writeLines(vector<string>lines) {
	int firstLine = 2;
	int margin = 2;
	for (int i = 0; i < lines.size(); i++) {
		mvaddstr(firstLine + i, 2, lines[i].c_str());
	}
}

/*
	Processes a Mouse Event
*/
void processMainMouseEvent(MEVENT* mouseEvent, int numRows, int numCols) {
	//changeStatus("processMouseEvent()");
	if (menuController.isMenuMouseEvent(mouseEvent, numRows, numCols, changeStatus)) {
		menuController.processMouseEvent(mouseEvent, numRows, numCols, changeStatus);
	}else if (contentController.isContentMouseEvent(mouseEvent, numRows, numCols, changeStatus)) {
		//execure the content mouse event
		contentController.processMouseEvent(mouseEvent, numRows, numCols, changeStatus);
	}
}
