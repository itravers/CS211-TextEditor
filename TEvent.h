/*
	Isaac Travers
	I adapted this class from earlier work of my won at:
	https://github.com/itravers/ARaceInSpace/blob/master/core/src/com/araceinspace/EventSubSystem/Event.java
*/
#ifndef TEVENT_H
#define TEVENT_H

#include <string>
#include <iostream>

using std::string;
using std::cout;	//for debugging
using std::endl;	//for debugging

/**
* Defines the type of Event available.
*/
enum TTYPE { DEFAULT, TEST1 };



/*******************************************************************************
 * Class Name:   TEvent
 * Purpose:      A TEvent is an object that a dispatcher will forward along
 *               It is created by an event pool,
 * 			     when it is done being used it should be returened to eventpool
 * 				 An Event has an associated TYPE, ID and DATA.
 *				 These pieces of information are used by the EventReceiver
 *				 when it consumes the Event. The TYPE is what the EventDispatcher will filter on.
 *				 The ID is what the EventReceiver will filter on to make sure it
 *				 only uses the Events that pertain to it.

 *******************************************************************************/
class TEvent {
public:

	

	/*******************************************************************************
	 * Constructor
	 * Purpose:        Creates a new Event with the type, id and data being NULL.
	 *******************************************************************************/
	TEvent();

	/*******************************************************************************
	 * Constructor
	 * Purpose:         Creates a new Event with a specific type, id and certain data.
	 *******************************************************************************/
	TEvent(TTYPE _type, string _id, string _data);

	/**
	 * Resets the event to default
	 */
	void reset();


	//getters and setters

	void setType(TTYPE _type);

	string getID();
	void setID(string _id);

	string getData();
	void setData(string _data);



	

private:

	/**
	 * Stores the type of this event.
	 */
	TTYPE type;

	/**
	 * The id of this particular incarnation of the event.
	 * This will be changed by EventSenders to whatever they desire.
	 */
	string id;

	/**
	* This is the data that the Event encapsulates. We should change this to be more abstract
	*/
	string data;
};

#endif