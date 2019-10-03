/*******************************************************************************
 * Created Date:      September 25th, 2019
 * Created By:        Isaac Travers
 * Purpose:           Manage the operation of a Text Editor
 *******************************************************************************/

#include "TextEditor.h"



TextEditor::TextEditor() : fileController()/*, menuController(this), contentController(this)*/ {
//TextEditor::TextEditor() {

}

void TextEditor::load(string fileName) {
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
	resize_term(1000, 1000);
	getmaxyx(mainWindow, numRows, numCols);
	resize_term(numRows - 1, numCols - 1);
	getmaxyx(mainWindow, numRows, numCols);

	//turn off key echo
	noecho();
	nodelay(mainWindow, TRUE);
	keypad(mainWindow, TRUE);

	//i cause everything
	curs_set(0);

	

	///////////////////TESTING
	bool keep_going = true;
	vector<TextEditorNamespace::EditorComponent*> components{};

	components.push_back(
		new TextEditorNamespace::EditorWindow{ mainWindow, TextEditorNamespace::Location{0, 0}, TextEditorNamespace::Size{20, 20}, true, true }
	);

	components.push_back(
		new TextEditorNamespace::EditorWindow{ mainWindow, TextEditorNamespace::Location{10, 10}, TextEditorNamespace::Size{20, 20}, true, true }
	);


	while (keep_going == true)
	{
		//wrefresh(mainWindow);
		//refresh();
		//werase(mainWindow);

		

		int input = wgetch(mainWindow);

		//Curses documentation says to use KEY_RESIZE, but you can also use
		//is_termresized.  In real life, use either/or but not both.
		if (is_termresized() == true)
		{
			//resize_term(0, 0);
			//getmaxyx(mainWindow, numRows, numCols);/////this doesn't work yet
		}
		switch (input)
		{
		case ctrl('c'):
			keep_going = false;
			break;
		case 'h':
			components[0]->setIsVisible(false);
			break;
		case 's':
			components[0]->setIsVisible(true);
			break;
		case KEY_RESIZE:
			resize_term(0, 0);
			getmaxyx(mainWindow, numRows, numCols);
			break;

		}

		//render components
		for (auto& component : components)
		{
			//TODO: render
			if (component->needsRefresh() == true)
			{

				component->render();
				component->refresh();
			}
		}

		wrefresh(mainWindow);//
	}

	///////////////////////////////END TESTING


	//COMMENT OUT FOR TESTING COMPONENTS
	/*
	//Initialize File Controller
	FileController fileController = FileController();

	//Initialize Menu Controller
	MenuController menuController = MenuController(mainWindow, numRows, numCols);



	//Initialize the Content Controller
	ContentController contentController = ContentController(mainWindow, numRows, numCols);

	//Initialize the Dialog Box
	DialogBox dialogBox = DialogBox(mainWindow, "", DIALOG_Y, DIALOG_X, DIALOG_NUM_ROWS, DIALOG_NUM_COLUMNS);

	//setup mouse
	mousemask(ALL_MOUSE_EVENTS, NULL);

	
	vector<string>lines;
	fileController.readFile(fileName, lines, READ);
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

			//return 0;
			//exit;
			break;
		case ctrl('s'):

			//get filename from user
			dialogString = dialogBox.displayDialogBox("Save File As: ");
			dialogBox.hide(); //hide box
			contentController.displayContents(); //must be called after dialogBox.hide() to delete it

			//get file data from content controller
			contentController.getCurrentLines(linesToSave);
			fileController.writeFile(dialogString, linesToSave);
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
		case 'a': case 'b': case 'c': case ' ': default:
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


	*/
	//revert back to normal console mode
	nodelay(mainWindow, TRUE);
	keypad(mainWindow, TRUE);
	mvaddstr(0, 0, "Press ANYKEY to continue...");
	char pause;//
	cin >> pause;
	endwin();

	//return 0;
}

bool TextEditor::componentNeedsRefresh(vector<EditorComponent*>v) {
	bool returnVal = false;

	//loop through the vector, and see if any specific element needs refreshed, if ANY elemnt does, return true
	for (int i = 0; i < v.size(); i++) {
		if (v[i]->needsRefresh()) {
			returnVal = true;
			break;
		}
	}
	return returnVal;
}

/*
	Draws everything currently on the screen.
*/
void TextEditor::drawScreen(int numRows, int numCols) {
	drawBorder(numRows, numCols);
	menuController.drawMenu(numRows, numCols);
	//dialogBox.draw();
	drawStatus(numRows, numCols);
}

/*
	Draws a status to the bottom of the screen.
*/
void TextEditor::drawStatus(int numRows, int numCols) {
	int xoffset = 1;
	attron(COLOR_PAIR(COLOR_STATUS_PAIR));
	mvaddstr(numRows - 1, xoffset, currentStatus.c_str());
	attroff(COLOR_PAIR(COLOR_STATUS_PAIR));
}



/*
	Draws a border to the screen
*/
void TextEditor::drawBorder(int numRows, int numCols) {
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
void TextEditor::initColor(void) {
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
void TextEditor::changeStatus(string newStatus) {
	currentStatus = newStatus + "                 ";
}

/*
	Writes out the lines in vector to the screen, exactly
	how it was read in
*/
void TextEditor::writeLines(vector<string>lines) {
	int firstLine = 2;
	int margin = 2;
	for (int i = 0; i < lines.size(); i++) {
		mvaddstr(firstLine + i, 2, lines[i].c_str());
	}
}

/*
	Processes a Mouse Event
*/
void TextEditor::processMainMouseEvent(MEVENT* mouseEvent, int numRows, int numCols) {
	//changeStatus("processMouseEvent()");

	if (menuController.isMenuMouseEvent(mouseEvent, numRows, numCols)) {
		menuController.processMouseEvent(mouseEvent, numRows, numCols);
	}
	
	else if (contentController.isContentMouseEvent(mouseEvent, numRows, numCols)) {
		//execure the content mouse event
		contentController.processMouseEvent(mouseEvent, numRows, numCols);
	}

}
