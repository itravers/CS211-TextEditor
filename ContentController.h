/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	September 7th, 2019
*********************************************************************************/
#ifndef CONTENT_CONTROLLER
#define CONTENT_CONTROLLER

#define SCROLL_BAR_SIZE 2

#include "curses.h"
#include "customcolors.h"
#include "structs.h"
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::to_string;
using std::binary_search;




/*******************************************************************************
 * Class Name:   ContentController
 * Purpose:      The ContentController is responsible for controlling
				 the main displays displays contents. This doesn't include
				 the menu's or the status bar, or the borders, but just the
				 files we want to display
 *******************************************************************************/
class ContentController {
public:

	/*******************************************************************************
	 * Constructor
	 *******************************************************************************/
	ContentController();
	ContentController(WINDOW* mainWindow, int numRows, int numCols);

	/*******************************************************************************
	 * Public Fields
	 *******************************************************************************/

	 /*******************************************************************************
	  * Public Methods
	  *******************************************************************************/
	void displayContents();
	void displayContents(vector<string> lines);
	void displayContentsFromLine(vector<string> lines, int startLine);
	bool isContentMouseEvent(MEVENT* mouseEvent, int numRows, int numCols);
	void processMouseEvent(MEVENT* mouseEvent, int numRows, int numCols);
	void moveCursorUp();
	void moveCursorDown();
	void moveCursorLeft();
	void moveCursorRight();
	int mapToRange(int n, int minInput, int maxInput, int minOutput, int maxOutput);
	void insertChar(char c); //inserts a character at the current point on screen and in lines vector
	void getCurrentLines(vector<string>&);

private:

	/*******************************************************************************
	 * Private Fields
	 *******************************************************************************/
	WINDOW* contentWindow;
	WINDOW* wrapBar; //A 1 column section at the end of each column where we can put word wrap chars
	WINDOW* scrollBar;
	Location cursorLocation;
	int cursorChar; //the ncurses char type
	vector<string>currentLines;
	vector<int> wordWrapRecord; // keeps a record of which lines have been word wrapped

	
	int numCols;
	int numRows;
	int startLine; // this is the line that we start printing at, it changes with scrolling

	/*******************************************************************************
	 * Private Methods
	 *******************************************************************************/
	void displayCursor();
	void breakLongLines(vector<string>*lines);
	int numTabsInString(string s);
	bool vectorContains(vector<int>&v, int item);
	int getChar(int x, int y); //returns the character in the currentLines vector given by x and y
	void replaceChar(vector<string>&lines, char toReplace, char replaceWith, int numReplaces);
	void replaceCharInString(string& s, int n, char replaceWith);
	bool isScrollbarLine(int currentLine, int currentRow, int startLine, int numLines);
	
};

#endif