/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	September 7th, 2019
*********************************************************************************/
#include "ContentController.h"

/*
	The default constructor
*/
ContentController::ContentController() {
	cursorLocation.x = 0;
	cursorLocation.y = 0;
	cursorChar = 'Q';
}

ContentController::ContentController(WINDOW* mainWindow, int numRows, int numCols) {
	startLine = 0;
	wordWrapRecord = vector<int>();
	this->numCols = numCols - 4;
	this->numRows = numRows - 4;
	cursorLocation.x = 0;
	cursorLocation.y = 0;
	cursorChar = 'Q';

	//create the window where the file content will be
	contentWindow = subwin(mainWindow, this->numRows, this->numCols, 2, 1); //we should change these magic number
	nodelay(contentWindow, TRUE);

	//create a 1 column bar that will be placed after the content where we can display the wordwrap char
	//to signify which lines have been word wrapped by the editor.
	wrapBar = subwin(mainWindow, this->numRows, 1, 2, numCols-3);
	scrollBar = subwin(mainWindow, this->numRows, 1, 2, numCols - 2);
}

void ContentController::displayContents() {
	displayContents(currentLines);
}

/*
	Displays the contents of a lines vector to the content window
*/
void ContentController::displayContents(vector<string> lines) {
	displayContentsFromLine(lines, startLine);
	displayCursor();
}

void ContentController::getCurrentLines(vector<string>& lines) {
	lines = currentLines;
}

/*
	Displays the contents of the lines vector to the content window
	starting at line startLine
*/
void ContentController::displayContentsFromLine(vector<string> lines, int startLine) {
	currentLines = lines;
	werase(contentWindow);
	werase(wrapBar);
	werase(scrollBar);
	int firstLine = 0, margin = 2;
	int n = 0;

	replaceChar(currentLines, '\t', ' ', 4); //replace all tabs in lines with 4 spaces
	breakLongLines(&currentLines); //break longer lines up into multiple lines

	//int numWraps = 0; //track how many times we word wrap
	for (int i = startLine; i < currentLines.size(); i++) {
		mvwaddstr(contentWindow, firstLine + n, margin, currentLines[i].c_str());

		//check if this is a line that was word wrapped, print appropriate char if so
		if (vectorContains(wordWrapRecord, i)) {
			wattron(wrapBar, COLOR_PAIR(COLOR_WORDWRAP_PAIR));
			mvwaddch(wrapBar, firstLine + n, 0, ACS_LRCORNER);
			wattroff(wrapBar, COLOR_PAIR(COLOR_WORDWRAP_PAIR));
		}


		//check if this line should be a scroll bar line
		if (isScrollbarLine(startLine + i, firstLine + n, 0, lines.size()+numRows)) {
			wattron(scrollBar, COLOR_PAIR(COLOR_SCROLLBAR_PAIR));
			mvwaddch(scrollBar, firstLine + n, 0, ' ');
			wattroff(scrollBar, COLOR_PAIR(COLOR_SCROLLBAR_PAIR));
		}

		n++;
	}

	//REFRESH AND DISPLAY
	wrefresh(contentWindow);
	wrefresh(wrapBar);
	wrefresh(scrollBar);
	displayCursor();
}

/*
	Calculates if a given line is a scoll bar line or not
	currentLine is our currentLine in the file, currentRow, is the row we are printing out on
*/
bool ContentController::isScrollbarLine(int currentLine, int currentRow, int startLine, int numLines) {
	bool returnVal = false;
	//find the range for scroll bars
	int scrollRow = mapToRange(currentLine, startLine, numLines+numRows-4, 0, numRows-1);
	if (scrollRow == currentRow) {
		returnVal = true;
	}
	return returnVal;
}

/*
	Inserts a character at the current index on screen
	and at the current index in the lines vector
*/
void ContentController::insertChar(char c) {
	//mvwaddch(contentWindow, cursorLocation.y, cursorLocation.x, (int)c);
	//we only need to add the char to the lines vector, the page will auto refresh and show it
	
	//get the cursor location
	int y = cursorLocation.y;
	int x = cursorLocation.x;

	//calculate which line we are inserting in, when we adjust for current scrolling position
	int yAdjusted = y + startLine;

	//if we are trying to add a character to a line that doesn't exist, we need to add blank lines
	if (currentLines.size() <= yAdjusted) {
		while (currentLines.size() <= yAdjusted) {
			currentLines.push_back("");
		}
	}

	//edit the character at the current cursor location (+ startLine adjusts the correct line when scrolling)
	string line = currentLines[ yAdjusted];
	
	replaceCharInString(line, x-2, c);

	
	
	currentLines[yAdjusted] = line;
	wrefresh(contentWindow);
}

//replace a given character with a certain number of others in lines.
//we'll use this to replace special characters ourselves
void ContentController::replaceChar(vector<string>& lines, char toReplace, char replaceWith, int numReplaces) {
	
	//loop through lines, finding the char toReplace
	for (int i = 0; i < lines.size(); i++) {
		string line = lines.at(i);
		
		//loop through each character
		for (int j = 0; j < line.size(); j++) {

			//check if the character is what we are looking for
			char c = line.at(j);
			if (c == toReplace || c < 0) {

				//we want to replace this character with numReplaces number of the character replaceWith
				lines[i][j] = replaceWith;
			}
		}
	}
}

/*
	Replaces a given character in a given string
*/
void ContentController::replaceCharInString(string& s, int n, char replaceWith) {
	
	//we don't want to insert before the string
	if (n < 0)return;

	//if the string is not long enough, we have to add spaces, before we enter this character
	if (s.length() <= n) {
		 s.insert(s.length(), n - s.length(), ' ');
		 s += replaceWith;
		return;
	}

	s[n] = replaceWith;
}

//check if v contains item
//in this case the vector should be pre sorted
bool ContentController::vectorContains(vector<int>&v, int item) {
	bool returnVal = false;
	if (binary_search(v.begin(), v.end(), item)) {
		returnVal = true;
	}else {
		returnVal = false;
	}
	return returnVal;
}


/*
	Checks if this mouse event has anything to do with the content controller
*/
bool ContentController::isContentMouseEvent(MEVENT* mouseEvent, int numRows, int numCols, void(*changeStatus)(string)) {
	//check if the mouse is over the content pane
	int x = mouseEvent->x;
	int y = mouseEvent->y;

	if (x > 0 && y > 1 && x < numCols - 1 && y < numRows - 2) {
		//changeStatus("Mouse Clicked: " + to_string(x) + " : " + to_string(y));
		return true;
	}
	else {
		return false;
	}
}

/*
	Called for a mouse event on the window
*/
void ContentController::processMouseEvent(MEVENT* mouseEvent, int numRows, int numCols, void(*changeStatus)(string)) {
	wrefresh(contentWindow);
}

/*
	Display the cursor on the content window
*/
void ContentController::displayCursor() {
	
	cursorChar = getChar(cursorLocation.x, cursorLocation.y);
	if (cursorChar <= 0) cursorChar = ' ';
	wattron(contentWindow, COLOR_PAIR(COLOR_CURSOR_PAIR));
	wattron(contentWindow, A_BLINK);
	mvwaddch(contentWindow, cursorLocation.y, cursorLocation.x, cursorChar);
	wattroff(contentWindow, A_BLINK);
	wattroff(contentWindow, COLOR_PAIR(COLOR_CURSOR_PAIR));
	wrefresh(contentWindow);
}

//returns the character in current lines, given by x and y, as an integer
int ContentController::getChar(int x, int y) {
	int returnVal = ' ';
	y += startLine; //adjust for the current starting line of the page

	//make sure we stay within the lines
	if (y < currentLines.size() - 1) {
		int lineSize = currentLines[y].size();
		x -= 2; //adjust margins with magic number

		//check and make sure we aren't trying to get out of bound values from currentLines
		if (lineSize > x) {
			string currentLine = currentLines[y];

			//only try to read this new value if it's in valid range
			if (lineSize > x && x >= 0) {
				char c = currentLine.at(x);
				returnVal = (int)c;
			}
		}
	}
	return returnVal;
}

/*
	Moves the cursor up
*/
void ContentController::moveCursorUp() {
	int y = cursorLocation.y;
	if (y <= 0) {
		y = 0;
		if (startLine > 0) {
			startLine -= 1;
			displayContentsFromLine(currentLines, startLine);
		}
	}
	else {
		y--;
	}
	cursorLocation.y = y;
	displayContents(currentLines);
}

/*
	Moves the cursor down
*/
void ContentController::moveCursorDown() {
	int y = cursorLocation.y;
	if (y >= numRows-5) {
		//make sure we wan't scroll down past the file
		if (startLine < currentLines.size()-1) {
			startLine += 1;
			displayContentsFromLine(currentLines, startLine);
		}
	}
	else {
		y++;
		cursorLocation.y = y;
		displayContents(currentLines);
	}
}

/*
	Moves the cursor left
*/
void ContentController::moveCursorLeft() {
	int x = cursorLocation.x;
	if (x != 0) {
		x--;
		cursorLocation.x = x;
	}
	else {
		int y = cursorLocation.y;
		if (y != 0) {
			y--;
			cursorLocation.y = y;
			x = numCols - 2;
			cursorLocation.x = x;
		}
	}
	displayContents(currentLines);
}

/*
	Moves the cursor right
*/
void ContentController::moveCursorRight() {
	int x = cursorLocation.x;
	if (x > numCols-3) {
		int y = cursorLocation.y;
		if (y > numRows - 6) {

			//do nothing
		}
		else {

			//put curser on next row at first column
			x = 0;
			y++;
			cursorLocation.x = x;
			cursorLocation.y = y;
		}
	}
	else {
			x++;
			cursorLocation.x = x;
	}
	displayContents(currentLines);
}

/*
	Breaks long lines in the lines vector up
	if the line is longer than numCols, the line
	is broken up and added to itself.
*/
void ContentController::breakLongLines(vector<string>*lines) {
	
	//scroll through until we find the first line that is too long
	for (int i = 0; i < lines->size(); i++) {
		string line = (*lines)[i];

		//strings with a \t have 4 bigger size for each \t present
		size_t numTabs = numTabsInString(line)*8;
		if (line.size() > numCols) {

			//we found a line too long`
			int overLength = line.size() - numCols + numTabs;
			
			//break the line into two strings
			string overFlowString = line.substr(numCols - numTabs, overLength);
			string mainString = line.substr(0, numCols - numTabs);

			//change current line to mainString
			(*lines)[i] = mainString;

			//insert overFlowString after currentLine we just edited
			auto it = lines->begin() + i + 1;
			lines->insert(it, overFlowString);

			//we are wrapping this line, keep a record of it so we can display later
			wordWrapRecord.push_back(i);
			
			//we only wanted to find the first one
			break;
		}
		//if we haven't found any lines to long we'll return, this is the base case
		if(i == lines->size() - 1) return;
	}
	//now we will find the rest of them.
	breakLongLines(lines);
}

/*
	Gives us the count of how many \t tabs are in a string
*/

int ContentController::numTabsInString(string s) {
	//loop through string and count num '\t'
	int numTabs = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '\t')numTabs++;
	}
	return numTabs;
}



/*
	Take a number n between minInput and maxInput, and return a
	number that is in the same proportional place between
	minOutput and maxOutput
*/
int ContentController::mapToRange(int n, int minInput, int maxInput, int minOutput, int maxOutput)
{
	return (n - minInput) * (maxOutput - minOutput) /
		(maxInput - minInput) + minOutput;
}
