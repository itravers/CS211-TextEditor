/*******************************************************************************
 * Created Date:      September 25th, 2019
 * Created By:        Isaac Travers
 * Purpose:           Manage the operation of a Text Editor
 *******************************************************************************/

#include "TextEditor.h"



void TextEditor::testCallback2(string menuData) {
	int i = 0;
	int j = 0;
	if (menuData == "Open Huffman") {
		openHuffman();
	}else if (menuData == "Save Huffman") {
		saveHuffman();
	}
	else if (menuData == "Set Srt Vis") {
		components[1]->setIsVisible(true);
	}
	else if (menuData == "Set Srt Invis") {
		components[1]->setIsVisible(false);
		components[0]->setNeedsRefresh(true);
	}
}



/*static void  testCallback(int other_arg, void* this_pointer) {
	TextEditor* self = static_cast<TextEditor*>(this_pointer);
	self->testCallback2();
}*/

void TextEditor::menuCallback(string menuData, void* this_pointer)
{
	TextEditor* self = static_cast<TextEditor*>(this_pointer);
	self->testCallback2(menuData);
}

void TextEditor::contextEditorHelper(string wordToInsert) {
	//insert the word wordToInsert into our content window
	((EditorWindowInteractive*)components[0])->insertString(wordToInsert);

}

void TextEditor::contextEditorCallback(string menuData, void* this_pointer) {
	TextEditor* self = static_cast<TextEditor*>(this_pointer);
	self->contextEditorHelper(menuData);
}




TextEditor::TextEditor() : fileController()/*, menuController(this), contentController(this)*/ {
//TextEditor::TextEditor() {

}

void TextEditor::load(string fileName) {
	string arg1;

	//Setup Window
	int numRows = 0;
	int numCols = 0;

	//Initialze Curses
	//WINDOW* mainWindow = nullptr;
	mainWindow = nullptr;

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
	
	components.push_back(
		new TextEditorNamespace::EditorWindowInteractive{ mainWindow , Location{3, 0}, Size{(numRows - 5) / 1, (numCols - 4) / 1}, true, true }
	);

	components.push_back(
		new TextEditorNamespace::SortingWindow{ mainWindow , Location{3, 0}, Size{(numRows - 5) / 1, (numCols - 4) / 1}, 5, false }
	);
    //components[1]->setIsVisible(true);


	menuBar = MenuBar(mainWindow, Location{ 0, 0 }, Size{ 3, numCols - 4 });
	menuBar.addItem("File", "Open", menuCallback, this);
	menuBar.addItem("File", "Open Huffman", menuCallback, this);
	menuBar.addItem("File", "Save", menuCallback, this);
	menuBar.addItem("File", "Save Huffman", menuCallback, this);
	menuBar.addItem("File", "Exit", menuCallback, this);
	menuBar.addItem("View", "Set Srt Vis", menuCallback, this);
	menuBar.addItem("View", "Set Srt Invis", menuCallback, this);
	menuBar.addItem("Edit", "ContextMenu", menuCallback, this);
	menuBar.addItem("Help", "About", menuCallback, this);

	contextMenu = ContextMenu(mainWindow, Location{ numRows-13, numCols-20 }, Size{ 10, 15 });

	//CREATE a NEW Dialog Box, to be used later
	dialogBox = DialogBox(mainWindow, "", DIALOG_Y, DIALOG_X, DIALOG_NUM_ROWS, DIALOG_NUM_COLUMNS);


	

	//Initialize File Controller
	FileController fileController = FileController();

	//Read display File
	vector<string>lines;
	//fileController.readFile("TextEditor/ContentController.cpp", lines, READ);
	fileController.readFile("test.txt", lines, READ);
	((EditorWindowScrollable*)components[0])->setData(lines);

	
	//read keywords.txt and add to a trie
	vector<string>keywords;
	fileController.readFile("keywords.txt", keywords, READ);
	contextMenuTrie = Trie();
	for (int i = 0; i < keywords.size(); i++) {
		contextMenuTrie.addWord(keywords[i]);
	}

	//setup mouse
	mousemask(ALL_MOUSE_EVENTS, NULL);
	MEVENT event;
	

	while (keep_going == true)
	{
		int input = wgetch(mainWindow);

		//Curses documentation says to use KEY_RESIZE, but you can also use
		//is_termresized.  In real life, use either/or but not both.
		if (is_termresized() == true)
		{
			//resize_term(0, 0);
			//getmaxyx(mainWindow, numRows, numCols);/////this doesn't work yet
		}

		char mychar;
		vector<string>contextWords;
		string currentword;

		switch (input){
			case KEY_MOUSE:
				//changeStatus("key mouse");
				if (nc_getmouse(&event) == OK) {
					//processMainMouseEvent(((EditorMenuPanel*)components[1]), &event);
					int itemClicked = menuBar.processMouseEvent(&event);
					if (itemClicked == -2) {
						components[0]->setNeedsRefresh(true);
						//menuBar.render();
					}
					else if (itemClicked >= 0) {
						for (auto& component : components) {
							component->setNeedsRefresh(true);
							
						}
						//menuBar.render();
					}


					itemClicked = contextMenu.processMouseEvent(&event);
					if (itemClicked == -2) {
						components[0]->setNeedsRefresh(true);
						//menuBar.render();
					}
					else if (itemClicked >= 0) {
						for (auto& component : components) {
							component->setNeedsRefresh(true);

						}
						//menuBar.render();
					}
				}
				break;
			case ctrl('f'):
				//get word from current cursor position
				currentword = ((EditorWindowInteractive*)components[0])->searchBufferForCurrentWord();

				//search for this word in the trie
				contextWords = contextMenuTrie.search(currentword);

				//delete all current word in our contextMenu
				contextMenu.clearMenu();

				for (int i = 0; i < contextWords.size(); i++) {
					contextMenu.addItem(contextWords[i], contextEditorCallback, this);
				}
				contextMenu.toggleVisibility();
				
					for (auto& component : components) {
						component->setNeedsRefresh(true);

					}
				
				break;
			
			default:
				((EditorWindowInteractive*)components[0])->handleKeyboardInput(input);
				break;
		}

		//dialogBox.draw();

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

		

		//render the menubar
		menuBar.render();
		//menuBar.refresh();

		if (contextMenu.needRefresh()) {
			contextMenu.render();
			contextMenu.refresh();
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



void TextEditor::refreshComponents(vector<EditorComponent*> v) {
	for (auto& component : v) {
		component->setNeedsRefresh(true);
	}
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

/*******************************************************************************
* Function Name:   openHuffman()
* Purpose:         Queries the user for which file we want to open
*                  Checks to see if there is a huffmanTree type of this file
*                  If there is, we read in the huffman tree structure,
*                  then we read in the compressed data.
*                  then we decode the compressed data using the tree
*                  Once everything is completed, we replace what is
*                  currently showing in the content area, with all
*                  the data we just decompressed.
*******************************************************************************/
void TextEditor::openHuffman() {

	//let us get the file name from the user, using a dialog box.
	string fileName = dialogBox.displayDialogBox("Name of File:");
	dialogBox.hide();
	wrefresh(mainWindow);//
}

string TextEditor::encodeTextWithHuffman(vector<string> dataToEncode, HuffTree<char>* hT) {
	unordered_map<char, string> encodingTable = {};
	hT->getEncodingTable(encodingTable);

	//loop through string and encode
	string encodedData = "";

	for (int i = 0; i < dataToEncode.size(); i++) {
		string line = dataToEncode[i];
		for (int j = 0; j < line.size(); j++) {
			encodedData += encodingTable[line[j]];
		}
	}

	encodedData = s_binaryToHex(encodedData);

	return encodedData;
}

string TextEditor::s_binaryToHex(string binaryData) {
	string text = "";
	for (int i = 0; i < binaryData.size(); i += 8) {
		string group = binaryData.substr(i, 8);
		bitset<8> temp(group);
		unsigned long u_temp = temp.to_ulong();
		text += u_temp;
	}
	return text;
}

string TextEditor::s_hexToBinary(string hexData) {
	string newBinary = "";
	for (int i = 0; i < hexData.size(); i++) {
		bitset<8> temp(hexData[i]);
		newBinary += temp.to_string();
	}
	return newBinary;
}



/*******************************************************************************
* Function Name:   saveHuffman()
* Purpose:         Queries the user for which file we want to save
*                  Encodes the huffman tree itself into: FILENAME-code.txt
*                  Compresses our text into file: FILENAME-compressed.txt
*                  saves both files.
*				   I decided to write this function without breaking it
*                  down via functional decomposition. To allow me
*                  to read through easier.
*******************************************************************************/
void TextEditor::saveHuffman() {

	//let us get the file name from the user, using a dialog box.
	string fileName = dialogBox.displayDialogBox("Name of File:");
	dialogBox.hide();
	// do we set needs refresh here for all other components?, that may take care of dialog box bug?
	wrefresh(mainWindow);//

	////make a frequency distribution of letters in the buffer.
	vector<string> buf = ((EditorWindowInteractive*)components[0])->getBuffer();

	//loop through buffer line by line
	for (int i = 0; i < buf.size(); i++) {

		string line = buf[i];
		
		//loop through line char by char
		for (int j = 0; j < line.size(); j++) {

			char c = line[j];	//this is a character.

			//std::unordered_map<std::string, double>::const_iterator got = mymap.find(input);
			auto it = freq_dist.find(c);

			if (it == freq_dist.end()) {
				
				//we have not found this character in our freq_dist add it
				freq_dist[c] = 1;
			}else {
				
				//we have found this character before, increment it
				freq_dist[c]++;
			}
		}
	}

	//we now have a frequency_distribution of characters in freq_dist
	//we now loop through freq_dist creating huffman tree's and adding them to a priority queue
	for (auto it : freq_dist) {
		char c = it.first;
		int freq = it.second;
		HuffTree<char>* huffTree = new HuffTree<char>(c, freq);
		huffmanQueue.push(huffTree);
		int size = huffmanQueue.size();
	}

	//now we have a huffmanqueue with all individual chars in their own trees, we need to combine
	while (huffmanQueue.size() > 1) {

		//get our two lowest weight huffman trees from our priority queue
		HuffTree<char>* t1 = huffmanQueue.top();
		huffmanQueue.pop();

		HuffTree<char>* t2 = huffmanQueue.top();
		huffmanQueue.pop();

		//create our merged
		HuffTree<char>* mergedTree;// = new HuffTree<char>(t2, t1);

		//put larger children as left child
		if (t1->weight() >= t2->weight()) {
			mergedTree = new HuffTree<char>(t1, t2);
		}else {
			mergedTree = new HuffTree<char>(t2, t1);
		}

		//put this merged tree back into the priority queue
		huffmanQueue.push(mergedTree);
	}

	//Now we need to encode our text into binary using the huffman tree
	HuffTree<char>* huffTree = huffmanQueue.top();
	string binaryTree = encodeFreqDist(freq_dist);
	string binaryText = encodeTextWithHuffman(buf, huffTree);

	string headerFlag = "-";

	//put the frequency distribution on the first line of our file
	//and put the 
	vector<string>binaryFile;
	binaryFile.push_back(binaryTree);
	binaryFile.push_back(binaryText);

	fileController.writeFile(fileName, binaryFile);
		
	int pause = 0;
}

string TextEditor::encodeFreqDist(unordered_map<char, int> freqDist) {
	string freqDistString = "";
	for (auto it : freqDist) {
		char c = it.first;
		int i = it.second;
		freqDistString += c;
		freqDistString += ':';
		freqDistString += to_string(i);
		freqDistString += ':';
	}

	return freqDistString;
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
	init_pair(COLOR_GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);
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
void TextEditor::processMainMouseEvent(EditorMenuPanel* menuPanel, MEVENT* mouseEvent) {
	//changeStatus("processMouseEvent()");

	//tell the menu to check if this mouse event is its?
	//((EditorMenuPanel*)components[1])->processMouseEvent(mouseEvent);
	//menuPanel->processMouseEvent(mouseEvent);

}
/*void TextEditor::processMainMouseEvent(MEVENT* mouseEvent, int numRows, int numCols) {
	//changeStatus("processMouseEvent()");

	if (menuController.isMenuMouseEvent(mouseEvent, numRows, numCols)) {
		menuController.processMouseEvent(mouseEvent, numRows, numCols);
	}
	
	else if (contentController.isContentMouseEvent(mouseEvent, numRows, numCols)) {
		//execure the content mouse event
		contentController.processMouseEvent(mouseEvent, numRows, numCols);
	}

}
*/
