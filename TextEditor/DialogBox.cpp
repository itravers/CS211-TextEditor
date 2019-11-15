#include "DialogBox.h"
#include "customcolors.h"

//Constructor
DialogBox::DialogBox() {}

DialogBox::DialogBox(WINDOW* parentWindow, string message, int yPos, int xPos, int nRows, int nCols) {
	this->parentWindow = parentWindow;

	//save the input values
	this->message = message;
	this->yPos = yPos;
	this->xPos = xPos;
	this->numRows = nRows;
	this->numCols = nCols;

	is_showing = false;

	//create a new window with those values
	this->window = subwin(parentWindow, numRows, numCols, yPos, xPos);
	panel = new_panel(window);
	hide_panel(panel);
}

string DialogBox::displayDialogBox(string message) {
	//delwin(window);
	this->message = message;
	//window = subwin(parentWindow, nRows, nCols, yPos, xPos);
	//move_panel(panel, 50, 50);
	//set the color box for the dialog box
	colorbox(window, COLOR_MENU_PAIR, 1);
	mvwaddstr(window, 1, 1, message.c_str());
	
	cursorLocation.x = message.size() + 1;
	cursorLocation.y = 1;
	displayCursor();
	//show();
	
	wrefresh(window);

	//freeze everything else going on and just get input for this dialog box
	int c;
	string inputValue = "";
	while ((c = wgetch(window)) != 10/*KEY_ENTER*/) {
		
		if (c == -1) continue;
		//check if this is an alpha numeric value
		if ((c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a') || (c >= '0' && c <= '9') || c == '.' || c == '-' || c == '_') {
			//it is alpha numeric, add it to the screen and to inputValue
			mvwaddch(window, cursorLocation.y, cursorLocation.x, c);
			cursorLocation.x++;
			inputValue += c;
		}

		//draw();
	}
	hide();
	return inputValue;
}

//draw the dialog box
void DialogBox::draw() {
	if (is_showing) {
		//draw here

		wrefresh(window);
	}
}

//make the dialog box show itself
void DialogBox::show() {
	is_showing = true;
	show_panel(panel);
}

//check if the dialog box is showing
bool DialogBox::isShowing() {
	return is_showing;
}

//hides the dialog box
void DialogBox::hide() {
	is_showing = false;
	hide_panel(panel);
	//werase(window);
	wrefresh(window);
	update_panels();
	doupdate();
	//wrefresh(parentWindow);
}

//returns the message the dialog box is displaying
string DialogBox::getMessage() {
	return message;
}

/*
	This function was not written by me. I adapted it from the colorbox function in tui.c
	that the teacher supplied.
*/
void DialogBox::colorbox(WINDOW* win, chtype color, int hasbox)
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
void DialogBox::setcolor(WINDOW* win, chtype color)
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
	Display the cursor on the content window
*/
void DialogBox::displayCursor() {

	//cursorChar = getChar(cursorLocation.x, cursorLocation.y);
	cursorChar = ' ';
	if (cursorChar <= 0) cursorChar = ' ';
	wattron(window, COLOR_PAIR(COLOR_CURSOR_PAIR));
	wattron(window, A_BLINK);
	mvwaddch(window, cursorLocation.y, cursorLocation.x, cursorChar);
	wattroff(window, A_BLINK);
	wattroff(window, COLOR_PAIR(COLOR_CURSOR_PAIR));
	wrefresh(window);
}