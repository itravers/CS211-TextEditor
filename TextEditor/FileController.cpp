/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	September 6th, 2019
*********************************************************************************/
#include "FileController.h"

/*
	Default Constructor
*/
//FileController::FileController() {
//
//}

FileController::FileController() {
	
}

bool FileController::writeFile(string filename, vector<string>& lines) {
	if (outFile) outFile.close();

	//try to open the file by name
	try {
		outFile.open(filename.c_str());

		//check if the file was properly opened
		if (!outFile) {
			throw string("Error: Couldn't Open File " + filename + " for writing!");
		}

		//loop through the vector one by one, printing each line to file
		for (int i = 0; i < lines.size(); i++) {
			outFile << lines[i] << endl;
		}

		//we are done, close the outfile
		outFile.close();

	}catch (string error) {
		//print our error to the status bar
//		textEditor->changeStatus(error);
		return false;
	}
}

/*
	Opens a file in the current working directory by name.
	Reads the file into a string vector, line by line.
*/
bool FileController::readFile(string fileName, vector<string>& lines, READ_WRITE readOrWrite) {
	//check if we are reading or writing
	if (readOrWrite == READ) {
//		textEditor->changeStatus("Opening File: " + fileName);

		//Close the inFile if it is currently open
		if (inFile) inFile.close();

		//try to open the new file by name
		try {
			//open the input file
			inFile.open(fileName.c_str());

			//check if the file was properly opened
			if (!inFile) {
				throw string("Error: Couldn't Open File " + fileName + " for reading!");
			}

			//now we are going to loop through the text and read every line into the lines vector
			string line = "";
			while (getline(inFile, line)) {
				lines.push_back(line);
			}
			
			//it looks like we succeded, return true to caller
			inFile.close();

			//replace all tabs in the file, we don't want to deal with tabs
			replaceChar(lines, '\t', ' ', 4); //replace all tabs in lines with 4 spaces
			return true;
		}
		catch (string error) {
			//print our error to the status bar
			
//			textEditor->changeStatus(error);
			return false;
		}

	}
	else if(readOrWrite == WRITE) {
		//we are writing
	}
}

//replace a given character with a certain number of others in lines.
//we'll use this to replace special characters ourselves
void FileController::replaceChar(vector<string>& lines, char toReplace, char replaceWith, int numReplaces) {

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
void FileController::replaceCharInString(string& s, int n, char replaceWith) {

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