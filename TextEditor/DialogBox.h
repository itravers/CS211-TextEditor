/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	September 23rd, 2019
*********************************************************************************/
#ifndef DIALOG_BOX
#define DIALOG_BOX

#define DIALOG_NUM_COLUMNS 45
#define DIALOG_NUM_ROWS 3
#define DIALOG_X 1
#define DIALOG_Y 2

#define A_ATTR (A_ATTRIBUTES)

#include "../curses.h"
#include "../panel.h"
#include "structs.h"
#include <string>

using std::string;

//struct Location {
//	int x;
//	int y;
//};

/*******************************************************************************
 * Class Name:   DialogBox
 * Purpose:      The DialogBox is a box that is displayed for the user
                 the user can input to type into the dialog box,
				 once the user hits enter the dialog box input
				 if fed to whereever it should be fed.
 *******************************************************************************/
class DialogBox {
public:

	/*******************************************************************************
	 * Constructor
	 *******************************************************************************/
	DialogBox();
	DialogBox(WINDOW* parentWindow, string message, int yPos, int xPos, int nRows, int nCols);

	/*******************************************************************************
	 * Public Fields
	 *******************************************************************************/

	 /*******************************************************************************
	  * Public Methods
	  *******************************************************************************/
	//getters
	string displayDialogBox(string message);
	void show();
	void hide();
	//int getXPos();
	//int getYPos();
	//int getNumCols();
	//int getNumRows();
	string getMessage();
	bool isShowing();
	//WINDOW* getWindow();
	//PANEL getPanel();

	void draw(); //draws the dialog box window if it is not hidden

	//setters
	//void setXPos(int x);
	//void setYPos(int y);
	//void setNumCols(int c);
	//void setNumRows(int r);
	//void setMessage(string m);
	void setcolor(WINDOW*, chtype);
	void colorbox(WINDOW*, chtype, int);

private:
	/*******************************************************************************
	 * Private Fields
	 *******************************************************************************/
	bool is_showing; /* Is the DialogBox showing? */
	int xPos, yPos, nCols, nRows;
	string message;
	WINDOW* window;
	WINDOW* parentWindow;
	PANEL* panel;
	
	int numCols; /* The Number of columns the dialog box takes. */
	int numRows; /* The number of rows the dialog box takes. */
	int posX;	 /* The X position of the dialog box. */
	int posY;	/* The Y position of the dialog box. */

	int cursorChar; //the ncurses char type
	Location cursorLocation;

	/*******************************************************************************
	 * Private Methods
	 *******************************************************************************/
	void displayCursor();
};
#endif