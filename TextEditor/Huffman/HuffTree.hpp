/*******************************************************************************
 * Created Date:      November 7th, 2019
 * Created By:        Isaac Travers
 * ContextMenu.hpp:   This is a Huffman Tree
 *                    This code is pretty much straight copied from the
					  class textbook, however I do modify things.
 *******************************************************************************/

#ifndef HUFF_TREE_HPP
#define HUFF_TREE_HPP

#include "LeafNode.hpp"
#include "InternalNode.hpp"

template <typename E> class HuffTree {
private:
	HuffNode<E>* root;

public:
	//leaf constructor
	HuffTree(E& val, int freq) {
		root = new LeafNode<E>(val, freq);
	}

	//internal node constructor
	HuffTree(HuffTree<E>* l, HuffTree<E>* r) {
		root = new InternalNode<E>(l->getRoot(), r->getRoot());
	}

	//destructor
	~HuffTree() {

	}

	//getroot
	HuffNode<E>* getRoot() {
		return root;
	}

	//root weight
	int weight() {
		return root->weight();
	}
	//unordered_map<char, int> freq_dist
	void getEncodingTable(unordered_map<char, string>& encodingTable) {
		//unordered_map<char, string>* encodingTable = {};

		//traverse the tree building the encodingTAble
		root->buildEncodingTable(encodingTable);
	}
};


#endif // endif HUFF_TREE_HPP