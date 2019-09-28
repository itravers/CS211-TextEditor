#include "TEvent.h"

//empty constructor
TEvent::TEvent() {
	
}

//constructor with data type and id
TEvent::TEvent(TTYPE _type, string _id, string _data) {
	type = _type;
	id = _id;
	data = _data;
}

//reset to default
void TEvent::reset() {
	this->type = DEFAULT;
	this->id = "";
	this->data = "";
}

//set the type
void TEvent::setType(TTYPE _type) {
	type = _type;
}

//get the id
string TEvent::getID() {
	return id;
}

//set the id
void TEvent::setID(string _id) {
	id = _id;
}

//get the data
string TEvent::getData() {
	return data;
}

//set the data
void TEvent::setData(string _data) {
	data = _data;
}