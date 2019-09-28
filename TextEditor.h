#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <string>
#include <iostream>

#include "FileController.h"

using std::string;
using std::cout;	//for debugging
using std::endl;	//for debugging


class FileController;	//Forward Declaration

/*******************************************************************************
 * Class Name:   Text Editor
 * Purpose:      Manages ALL functions, data and communications of
 *               the text editor.
 *******************************************************************************/
class TextEditor{
public:

	/*******************************************************************************
	 * Constructor
	 * Purpose:         It like, constructs the object man.
	 *******************************************************************************/
	TextEditor(string fileName);

	/*******************************************************************************
	 * Function Name:   load()
	 * Purpose:         Initializes the Text Editor, loads the given/default file
	 * Preconditions:	main declares a new Text Editor
	 * Postcondition:	The text editor is running, the first file is open, nothing
						is yet showing on screen.
	 *******************************************************************************/
	void load();

	/*******************************************************************************
	 * Function Name:   run()
	 * Purpose:         Houses the loop of the main Text Editor processes.
	 * Preconditions:	load() has been called
	 * Postcondition:	The program is closed.
	 *******************************************************************************/
	void run();

private:

	//Field Variables
	string fileName; //The Name of the file we are working with

	//Private Member Objects
	FileController fileController;
};

#endif