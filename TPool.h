/*
	Isaac Travers
	I adapted this class from earlier work of my won at:
	https://github.com/itravers/ARaceInSpace/blob/master/core/src/com/araceinspace/EventSubSystem/Event.java
*/
#ifndef TPOOL_H
#define TPOOL_H

#include <stack>
#include <string>
#include <iostream>

using std::string;
using std::cout;	//for debugging
using std::endl;	//for debugging


/*******************************************************************************
 * Class Name:   TPool
 * Purpose:      An Abstract class that implements a pool
 *******************************************************************************/
template <class T>
class TPool {
public:

	/*******************************************************************************
	 * Constructor
	 * Purpose:        Creates a new Event with the type, id and data being NULL.
					   minCapacity is expected to be less than or equal to maxCapacity
	 *******************************************************************************/
	TPool(int _minCapacity, int _maxCapacity) {
		minCapacity = _minCapacity;
		maxCapacity = _maxCapacity;

		//initialize the stack
		elementStack

		//increase # elements in stack to the min
		
		while (elementStack.s) {

		}
	}

	/*******************************************************************************
	 * Function:	   obtain()
	 * Purpose:        Returns an Item from the pool,
	 *				   The Item may be newly created, or reused
	 *******************************************************************************/
	<T> obtain();

	/*******************************************************************************
	 * Function:	   free()
	 * Purpose:        Puts item back into pool, making it available to be obtained
	 *                 if this item is already somehow in the pool, we won't readd
	 *******************************************************************************/
	<T> free();

	/*******************************************************************************
	 * Function:	   newObject()
	 * Purpose:        create a new item to add to the pool, and add it to the pool
	 *******************************************************************************/
	virtual <T> newObject() = 0;
	

private:
	stack<T> elementStack; //the elements of the pool itself
	int minCapacity;	//the minimum number of elements allowed to be in this pool
	int maxCapacity;   //the total number of elements allowed to be in this pool
	
};

#endif