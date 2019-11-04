/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	September 23rd, 2019
*********************************************************************************/
#ifndef MY_STRUCTS
#define MY_STRUCTS

//This should be used for any location within the TextEditor, this is how we will disinguish between curses and our libraries.
struct Location {
	int y;
	int x;
};

//This should be used for any size within the TextEditor
struct Size {
	int height;
	int width;
};

#endif