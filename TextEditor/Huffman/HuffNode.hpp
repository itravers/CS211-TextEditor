/*******************************************************************************
 * Created Date:      November 7th, 2019
 * Created By:        Isaac Travers
 * ContextMenu.hpp:   This is an abstract base class for a Huffman tree Node
 *                    This code is pretty much straight copied from the
					  class textbook, however I do modify things.
 *******************************************************************************/

#ifndef HUFF_NODE_HPP
#define HUFF_NODE_HPP

template <typename E> class HuffNode {
	virtual ~HuffNode() {}		//Base destructor
	virtual int weight() = 0;	//Return Frequency
	virtual bool isLeaf() = 0;	//Determine type
};


#endif // endif HUFF_NODE_HPP