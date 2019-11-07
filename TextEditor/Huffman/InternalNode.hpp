/*******************************************************************************
 * Created Date:      November 7th, 2019
 * Created By:        Isaac Travers
 * ContextMenu.hpp:   This is an internal node for a Huffman tree Node
 *                    This code is pretty much straight copied from the
					  class textbook, however I do modify things.
 *******************************************************************************/

#ifndef INTERNAL_NODE_HPP
#define INTERNAL_NODE_HPP

#include "HuffNode.hpp"

template <typename E> class InternalNode : public HuffNode<E> {
private:
	HuffNode<E>* leftChild;
	HuffNode<E>* rightChild;
	int wgt;	//subtree weight

public:
	InternalNode(HuffNode<E>* l, HuffNode<E>* r) {
		wgt = l->weight() + r->weight();
		leftChild = l;
		rightChild = r;
	}

	int weight() {
		return wgt;
	}

	bool isLeaf() {
		return false;
	}

	HuffNode<E>* left() const {
		return leftChild;
	}

	HuffNode<E>* right() const {
		return rightChild;
	}

	void setLeft(HuffNode<E>* l) {
		leftChild = (HuffNode<E>*)l;
	}

	void setRight(HuffNode<E>* r) {
		rightCHild = (HuffNode<E>*)r;
	}
};


#endif // endif INTERNAL_NODE_HPP