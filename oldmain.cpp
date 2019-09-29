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

/* Includes */
#include "curses.h"
#include "panel.h"
#include "customcolors.h"
#include "MenuController.h"
#include <string>
#include <iostream>

/* Namespaces */
using std::string;
using std::cin;

/* Function Prototypes*/
void initColor(void);			// Initialize the Color System
void drawBorder(int, int);		// Border around the screen
void drawStatus(int, int);		// Draws the status bar at the bottom of the screen
void drawScreen(int, int);		// Draws everything associated with the screen.

/* Objects */
MenuController menuController;

/* Start of the Program. */
int main(void) {
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
	curs_set(0);

	//Initialize Menu Controller
	MenuController::MenuController();

	//Draw the screen
	drawScreen(numRows, numCols);

	//menu item test
	WINDOW* menuWindow = nullptr;
	menuWindow = new_panel();
	mainWindow.new
	

	refresh(); //Tells Curses to Draw

	//revert back to normal console mode
	nodelay(mainWindow, TRUE);
	keypad(mainWindow, TRUE);
	mvaddstr(0, 0, "Press ANYKEY to continue...");
	char pause;
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
	drawStatus(numRows, numCols);
}

/*
	Draws a status to the bottom of the screen.
*/
void drawStatus(int numRows, int numCols) {
	int xoffset = 1;
	attron(COLOR_PAIR(COLOR_MAIN_PAIR));
	mvaddstr(numRows-1, xoffset, "STATUS: Everything IS Okay!");
	attroff(COLOR_PAIR(COLOR_MAIN_PAIR));
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
	init_pair(COLOR_STATUS_PAIR, COLOR_GREEN, COLOR_BLACK);
}
