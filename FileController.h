#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include <string>
#include <iostream>

using std::string;
using std::cout;	//for debugging
using std::endl;	//for debugging


/*******************************************************************************
 * Class Name:   Text Editor
 * Purpose:      Manages ALL functions, data and communications of
 *               the text editor.
 *******************************************************************************/
class FileController {
public:

	//default constructor, do nothing
	FileController() {};

	/*******************************************************************************
	 * Constructor
	 * Purpose:         It like, constructs the object man.
	 *******************************************************************************/
	FileController(string fileName);

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
};

#endif