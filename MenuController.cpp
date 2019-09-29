/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	August 30th, 2019
*********************************************************************************/
#include "MenuController.h"

//Used to keep track of menu windows and menu panels
WINDOW* mainMenuWindow;
WINDOW* menuWindows[MENU_NUM_ITEMS];		/* A Menu Window */
PANEL* menuPanels[MENU_NUM_ITEMS];			/* A Menu Panel  */

/*
	Default constructor doesn't need to do anything.
*/
MenuController::MenuController() {
	//textEditor = t;
}

/*
	Initializes all the menu windows and panels
*/
MenuController::MenuController(WINDOW* mainWindow, int numRows, int numCols) {
	//setup the main menu
	mainMenuWindow = subwin(mainWindow, 0, 0, 0, 0);

	//setup submenu items 2d array
	//for (int i = 0; i < rowCount; ++i)
	//	a[i] = new int[colCount];
	subMenuItems[0] = fileMenuItems;
	subMenuItems[1] = editMenuItems;
	subMenuItems[2] = viewMenuItems;
	subMenuItems[3] = toolsMenuItems;
	subMenuItems[4] = helpMenuItems;

	//set the color box for the main menu
	colorbox(mainMenuWindow, COLOR_MENU_PAIR, 0);

	for (int i = 0; i < MENU_NUM_ITEMS; i++) {
		
		WINDOW* newWin = nullptr;
		newWin = newwin(menuHeight, menuWidth, 2, ((numCols / MENU_ITEM_RATIO) * i) + XOFFSET);
		menuWindows[i] = newWin;

		//set a color box around each menuWindow
		colorbox(menuWindows[i], COLOR_MENU_PAIR, 1);

		//Set up the panels for the menu
		menuPanels[i] = new_panel(menuWindows[i]);

		//Setup the labels for each menu
		mvwaddstr(menuWindows[i], 0, XOFFSET, menuItems[i].c_str());

		//print each submenu item
		for (int j = 0; j < SUBMENU_NUM_ITEMS; j++) {
			mvwaddstr(menuWindows[i], j + 1, XOFFSET, subMenuItems[i][j].c_str());
		}

		//start the menus in hidden configuration
		hide_panel(menuPanels[i]);
	}

	
}

/*
	Draws the menu items.
*/
void MenuController::drawMenu(int numRows , int numCols) {

		//Set The Color For characters we are printing with.
		attron(COLOR_PAIR(COLOR_MENU_PAIR));	

		//loop through and print main menu items
		for (int i = 0; i <= menuItems->length(); i++) {
			mvwaddstr(mainMenuWindow, 0, ((numCols / MENU_ITEM_RATIO) * i) + XOFFSET, menuItems[i].c_str());
		}
		attroff(COLOR_PAIR(COLOR_MENU_PAIR)); //Unset the color

		//refresh the mainMenuWindow
		wrefresh(mainMenuWindow);

		//refresh all the menuWindows
		for (int i = 0; i < MENU_NUM_ITEMS; i++) {
			wrefresh(menuWindows[i]);
		}

		//update all the panels stacks
		update_panels();

		//draw the screen
		doupdate();
}

/*
	Closes all the menus
*/
void MenuController::closeAll() {
	//loop through and close all the menu windows
	for (int i = 0; i < MENU_NUM_ITEMS; i++) {
		hide_panel(menuPanels[i]);
		wrefresh(menuWindows[i]);
	}

	update_panels();
	doupdate();
}

/*
	Hides a specific menu
*/
void MenuController::closeMenu(int menuNum) {
	hide_panel(menuPanels[menuNum]);
	wrefresh(menuWindows[menuNum]);
	update_panels();
}

/*
	Causes a given menu to pop up
*/
void MenuController::popupMenu(int menuNum) {
	//hide all panels
	for (int i = 0; i < MENU_NUM_ITEMS; i++) {
		hide_panel(menuPanels[i]);
		update_panels();
	}

	show_panel(menuPanels[menuNum]);
	wrefresh(menuWindows[menuNum]);
}

/*
	This function was not written by me. I adapted it from the colorbox function in tui.c
	that the teacher supplied.
*/
void MenuController::colorbox(WINDOW* win, chtype color, int hasbox)
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
void MenuController::setcolor(WINDOW* win, chtype color)
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

/*
	Returns the current state of the menu enum to the caller
*/
MENU_STATE MenuController::getMenuState(){
	return menuState;
}

/*
	Called publically to set the state of the menu
*/
void MenuController::setMenuState(MENU_STATE state){
	menuState = state;
	switch (state) {
		case MENU_CLOSED: 
			closeAll();
			break;
		case MENU_FILE_OPEN:
			popupMenu(MENU_FILE);
			break;
		case MENU_EDIT_OPEN:
			popupMenu(MENU_EDIT);
			break;
		case MENU_VIEW_OPEN:
			popupMenu(MENU_VIEW);
			break;
		case MENU_TOOLS_OPEN:
			popupMenu(MENU_TOOLS);
			break;
		case MENU_HELP_OPEN:
			popupMenu(MENU_HELP);
			break;
	}
}

/*
	Called to check if a mouse click involves the menu
*/
bool MenuController::isMenuMouseEvent(MEVENT* mouseEvent, int numRows, 
									  int numCols) {

	bool returnVal = false;

	//check if the mouse event is clicking on a menu item
	//first we check and see if we have clicked in the menu bar at the top of the screen
	int x = mouseEvent->x;
	int y = mouseEvent->y;

	//the menu is only on the top row, not counting the first or the last item
	if (x > 0 && x < numCols - 1 && y == 0) {
		returnVal = true;
	}else {

		//now we check and see if we clicked on any open menu windows
		//check the menu state, and based off of which menu is open we will check the mouse
		MENU_STATE state = getMenuState();
		switch (state) {
			case MENU_CLOSED:

////				textEditor->changeStatus("menuClosed");
				returnVal = false;
				break;
			case MENU_FILE_OPEN:

				//file menu is between 2 <= x <= 19, 3<=y<=11later we'll remove the hard coding
				if (x >= 2 && x <= 19 && y >= 3 && y<= 11) {
					//changeStatus(" File Menu Clicked x: " + to_string(x) + " y: " + to_string(y));
					returnVal = true;
				}
				else { // the menu file is open, but we clicked outside of it, so close it
					setMenuState(MENU_CLOSED);
				}
				
				break;
			case MENU_EDIT_OPEN:

				//MENU_EDIT_OPEN menu is between 13 <= x <= 30, 3<=y<=11later we'll remove the hard coding
				if (x >= 13 && x <= 30 && y >= 3 && y <= 11) {

////					textEditor->changeStatus(" Edit Menu Clicked x: " + to_string(x) + " y: " + to_string(y));
					returnVal = true;
				}
				else { // the menu file is open, but we clicked outside of it, so close it
					setMenuState(MENU_CLOSED);
				}
				break;
			case MENU_VIEW_OPEN:

				//MENU_VIEW_OPEN menu is between 24 <= x <= 41, 3<=y<=11later we'll remove the hard coding
				if (x >= 24 && x <= 41 && y >= 3 && y <= 11) {
////					textEditor->changeStatus(" View Menu Clicked x: " + to_string(x) + " y: " + to_string(y));
					returnVal = true;
				}
				else { // the menu file is open, but we clicked outside of it, so close it
					setMenuState(MENU_CLOSED);
				}
				break;
			case MENU_TOOLS_OPEN:

				//MENU_TOOLS_OPEN menu is between 35 <= x <= 52, 3<=y<=11later we'll remove the hard coding
				if (x >= 35 && x <= 52 && y >= 3 && y <= 11) {
////					textEditor->changeStatus(" Tool Menu Clicked x: " + to_string(x) + " y: " + to_string(y));
					returnVal = true;
				}
				else { // the menu file is open, but we clicked outside of it, so close it
					setMenuState(MENU_CLOSED);
				}
				break;
			case MENU_HELP_OPEN:
				//MENU_HELP_OPEN menu is between 46 <= x <= 63, 3<=y<=11later we'll remove the hard coding
////				textEditor->changeStatus(" Help Menu Clicked x: " + to_string(x) + " y: " + to_string(y));
				if (x >= 46 && x <= 63 && y >= 3 && y <= 11) {
////					textEditor->changeStatus(" Help Menu Clicked x: " + to_string(x) + " y: " + to_string(y));
					returnVal = true;
				}
				else { // the menu file is open, but we clicked outside of it, so close it
					setMenuState(MENU_CLOSED);
				}
				break;
			default:
				returnVal = false;
				break;
		}
	}
	return returnVal;
}

/*
	Called when the mouse has clicked on the menu.
	processes the mouse click by making the menu respond accordingly
*/
void MenuController::processMouseEvent(MEVENT* mouseEvent, int numRows, 
									   int numCols) {
	//get the event coordinates
	int x = mouseEvent->x;
	int y = mouseEvent->y;

	//we have had a menu click, now we check if a specific item is being clicked
	bool mainMenuClicked = false;
	for (int i = 0; i < MENU_NUM_ITEMS; i++) {
		string name = menuItems[i];
		int startX = ((numCols / MENU_ITEM_RATIO) * i) + XOFFSET;
		int endX = ((numCols / MENU_ITEM_RATIO) * i) + XOFFSET + name.length();
		if (x >= startX && x < endX && getMenuState() == MENU_CLOSED) {
			switch (i) {
				case 0:
					setMenuState(MENU_FILE_OPEN);

					break;
				case 1:
					setMenuState(MENU_EDIT_OPEN);
					break;
				case 2:
					setMenuState(MENU_VIEW_OPEN);
					break;
				case 3:
					setMenuState(MENU_TOOLS_OPEN);
					break;
				case 4:
					setMenuState(MENU_HELP_OPEN);
					break;
			}
			break;
		} else { // we didn't click on main menu, maybe we have clicked on a submenu

			/*check each menu to see if it is open, if it IS open, check to see
			  if we clicked inside those menu's boundries. If we did click within
			  those menu's boundries, check and see which line we have clicked
			  on within that menu, then run whatever function cooresponds 
			  with that line */

			//check which menu is open
			MENU_STATE state = getMenuState();
			switch (state) {
				case MENU_CLOSED:
					//the menu is closed, and we didn't click on the main menu
					//i don't see this ever being called, but lets put it
					//here just in case.
					
					//DO NOTHING
					break;
				case MENU_FILE_OPEN: // The File Menu Is Open

					//file menu is between 2 <= x <= 19, 3<=y<=11later we'll remove the hard coding
					if (x >= 2 && x <= 19 && y >= 3 && y <= 11) {
						//we have clicked on the file menu, lets figure out which position we clicked on
						int position = y - 3;
////						textEditor->changeStatus("Clicked Position: " + to_string(position) + " in File Menu!");
						switch (position) {
							case 0:
////								textEditor->changeStatus("Open File Name: ");
								break;
						}
					}

					break;
			}

		}
	}
}