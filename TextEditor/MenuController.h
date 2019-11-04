/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	August 30th, 2019
*********************************************************************************/
#ifndef MENU_CONTROLLER
#define MENU_CONTROLLER
#define A_ATTR (A_ATTRIBUTES)

/* Defines the fraction of the
   window a single memory item takes.
   number is the inverse. */
#define MENU_ITEM_RATIO 10
#define MENU_NUM_ITEMS 5	/* Number of Menu Items */
#define SUBMENU_NUM_ITEMS 8	/* Number of Sub Menu Items */
#define MENU_HEIGHT 10		/* Menu Height */
#define MENU_WIDTH 20		/* Menu Width  */
#define MENU_FILE 0
#define MENU_EDIT 1
#define MENU_VIEW 2
#define MENU_TOOLS 3
#define MENU_HELP 4

/* Number of characters to offset the menu from the right of the screen. */
#define XOFFSET 1

#include <string>
#include <vector>
#include "../curses.h"
#include "../panel.h"
//#include "TextEditor.h" //we don't ever need to include this it's
#include "customcolors.h"


using std::string;
using std::vector;
using std::to_string;

//enum defines different states the menu can be in
enum MENU_STATE {MENU_CLOSED, MENU_FILE_OPEN, MENU_EDIT_OPEN, MENU_VIEW_OPEN, MENU_TOOLS_OPEN, MENU_HELP_OPEN};


/*******************************************************************************
 * Class Name:   MenuController
 * Purpose:      Controls the Text Editors Menu System
 *******************************************************************************/
//class TextEditor; //forward declare TextEditor
class MenuController {
public:

	/*******************************************************************************
	 * Constructor
	 *******************************************************************************/
	MenuController();
	MenuController(WINDOW*, int, int);

	/*******************************************************************************
	 * Public Fields
	 *******************************************************************************/


	/*******************************************************************************
	 * Public Methods
	 *******************************************************************************/
	void drawMenu(int, int);
	void popupMenu(int);
	void closeMenu(int);
	void closeAll();
	void colorbox(WINDOW* win, chtype color, int hasbox);
	void setcolor(WINDOW* win, chtype color);
	void setMenuState(MENU_STATE);
	MENU_STATE getMenuState();
	bool isMenuMouseEvent(MEVENT*, int numRows, int numCols);
	void processMouseEvent(MEVENT* mouseEvent, int numRows, int numCols);

private:
	/* Objects */
	//TextEditor* textEditor;

	/*******************************************************************************
	 * Private Fields
	 *******************************************************************************/

	/* A List of the items we will have in our menu. */
	string menuItems[MENU_NUM_ITEMS] = { "File", "Edit", "View", "Tools", "Help" };
	string** subMenuItems = new string* [MENU_NUM_ITEMS]; //2d array to store all submenu items
	string fileMenuItems[SUBMENU_NUM_ITEMS] = { "Open File", "Save File", " ", " ", " ", " ", " ", "Exit"};
	string editMenuItems[SUBMENU_NUM_ITEMS] = { "Find", "Find & Replace", " ", " ", " ", " ", " ", " " };
	string viewMenuItems[SUBMENU_NUM_ITEMS] = { "View Special Char", " ", " ", " ", " ", " ", " ", " " };
	string toolsMenuItems[SUBMENU_NUM_ITEMS] ={ "Find", " ", " ", " ", " ", " ", " ", " " };
	 string helpMenuItems[SUBMENU_NUM_ITEMS] ={ "About", " ", " ", " ", " ", " ", " ", " " };

	/* The menu dimensions */
	const int menuHeight = MENU_HEIGHT;
	const int menuWidth = MENU_WIDTH;

	/* menuState keeps track of the current state of the menu. */
	MENU_STATE menuState = MENU_CLOSED;


	/*******************************************************************************
	 * Private Methods
	 *******************************************************************************/
};

#endif