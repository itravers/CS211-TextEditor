#include "TextEditor/TextEditor.h"

/* Start of the Program. */
int main(int argc, char* argv[]) {
	string fileName = "motd.txt";		//motd.txt is the default fileName

	//check if we have a command line argument, if we do, we'll treat it as a filename
	if (argc > 1) {
		fileName = argv[1];
	}
	

	TextEditor textEditor = TextEditor();
	textEditor.load(fileName);		//load editor with initial file
}