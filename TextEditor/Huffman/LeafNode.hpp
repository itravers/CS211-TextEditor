/*******************************************************************************
 * Created Date:      November 7th, 2019
 * Created By:        Isaac Travers
 * ContextMenu.hpp:   This is a leaf node for a Huffman tree Node
 *                    This code is pretty much straight copied from the
					  class textbook, however I do modify things.
 *******************************************************************************/

#ifndef LEAF_NODE_HPP
#define LEAF_NODE_HPP

#include "HuffNode.hpp"

template <typename E> class LeafNode: public HuffNode<E> {
private:
	E it;		//value
	int wgt;	//weight

public:
	//constructor
	LeafNode(const E& val, int freq) {
		it = val;
		wgt = freq;
	}

	int weight() {
		return wgt;
	}

	E val() {
		return it;
	}

	bool isLeaf() {
		return true;
	}
};


#endif // endif LEAF_NODE_HPP