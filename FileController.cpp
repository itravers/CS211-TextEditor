#include "FileController.h"

FileController::FileController(string fName) {
	cout << "Contructing : FileController()" << endl;
	fileName = fName;
}

void FileController::load() {
	cout << "load() : FileController" << endl;
}

void FileController::run() {
	cout << "run() : FileController" << endl;
}