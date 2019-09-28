#include "TextEditor.h"

//constructor
TextEditor::TextEditor(string fName){
	cout << "Constructing : TextEditor()" << endl;
	fileName = fName;
}

//load the text editor
void TextEditor::load() {
	cout << "load() : TextEditor" << endl;

	//construct and load member objects
	fileController = FileController(fileName);
	fileController.load();
}

//run the text editor
void TextEditor::run() {
	cout << "run() : TextEditor" << endl;

	fileController.run();
	
}
