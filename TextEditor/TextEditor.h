/*******************************************************************************
 * Created Date:      September 25th, 2019
 * Created By:        Isaac Travers
 * Purpose:           Manage the operation of a Text Editor
 *******************************************************************************/

#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

/* Defines */
#define PDC_DLL_BUILD 1			//Used for Curses
#define A_ATTR (A_ATTRIBUTES)   //Shorten
#define ctrl(x) ((x) & 0x1f)	//CTRL-x masking

//INCLUDES
#include "../curses.h"									/* This is Curses */
#include "../panel.h"									/* Curses Library to Manipulate Windows */
#include "Components/EditorWindow.hpp"					/* The Window */
#include "Components/EditorWindowResizable.hpp"			/* A resizable window */
#include "Components/EditorWindowMoveable.hpp"			/* A Moveable window */
#include "Components/EditorWindowScrollable.hpp"		/* A SCrollable Window */
#include "Components/EditorWindowEditable.hpp"			/* A Editable Window */
#include "Components/EditorWindowInteractive.hpp"			/* An Interactive Window */
#include "Components/EditorMenu.hpp"					/* An Menu Window */
#include "customcolors.h"								/* Reference to console colors */
#include "../TextEditor/MenuController.h"				/* Everything to do with Menu's */
#include "FileController.h"								/* Manipulating Files */
#include "ContentController.h"							/* All Content Manipulation. */
#include "DialogBox.h"									/* Everything to do with dialogs. */

#include <string>
#include <iostream>
#include <stdio.h>

/* Namespaces */
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::to_string;
using TextEditorNamespace::EditorComponent;
using TextEditorNamespace::EditorWindow;
using TextEditorNamespace::EditorWindowResizable;
using TextEditorNamespace::EditorWindowMoveable;
using TextEditorNamespace::EditorWindowScrollable;
using TextEditorNamespace::EditorWindowEditable;
using TextEditorNamespace::EditorWindowInteractive;
using TextEditorNamespace::EditorMenu;

/*******************************************************************************
 * Class Name:   Text Editor
 * Purpose:      Manages ALL functions, data and communications of 
 *               the text editor.
 *******************************************************************************/
//forward declare class
class FileController;

//class C {};
class TextEditor {

public:

	TextEditor();

	/*******************************************************************************
	 * Function Name:   load()
	 * Purpose:         Initializes the Text Editor, loads the given/default file
	 * Preconditions:	main declares a new Text Editor
	 * Postcondition:	The text editor is running, the first file is open, nothing
	                    is yet showing on screen.
	 *******************************************************************************/
	void load(string fileName);

	/*******************************************************************************
	 * Function Name:   run()
	 * Purpose:         Houses the loop of the main Text Editor processes.
	 * Preconditions:	load() has been called
	 * Postcondition:	The program is closed.
	 *******************************************************************************/
	void run();

	void changeStatus(string);		// Changes the status screen that gets printed at the bottom.
	static void testCallback(int other_arg, void* this_pointer);
	void testCallback2();
	//void testCallback();
private:

	/* Objects */
	FileController fileController;
	MenuController menuController;
	ContentController contentController;
	DialogBox dialogBox;
	static WINDOW* titleWindow;	

	/* Field Variables */
	string currentStatus = "Starting Program...";

	/* Function Prototypes*/
	void initColor(void);				// Initialize the Color System
	void drawBorder(int, int);			// Border around the screen
	void drawStatus(int, int);			// Draws the status bar at the bottom of the screen
	void drawScreen(int, int);			// Draws everything associated with the screen.
	
	void writeLines(vector<string>);				// Writes the lines from the file to the screen
	void processMainMouseEvent(MEVENT*, int, int);	// processes a mouse event
	static void colorbox(WINDOW*, chtype, int);		// Creates a color box around given window, 1 for visible
	bool componentNeedsRefresh(vector<EditorComponent*> v);
	void refreshComponents(vector<EditorComponent*> v);
	

};
#endif