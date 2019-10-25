#ifndef TRIE_NODE_H
#define TRIE_NODE_H

#include <vector>
#include <unordered_map>
#include <cctype>
using namespace std;

class TrieNode
{
private:
    char _data;
    unordered_map<char, TrieNode*> _children;

	//For our Trie, we are using the character '$' as a sentinel
	//value to mark the end of a word.
    static const char _sentinel = '$';

public:
    TrieNode(const char &data = '\0')
    {
        setValue(data);
    }

    void setValue(const char &data)
    {
        _data = toupper(data);
    }

    const char& getValue() const
    {
        return _data;
    }

    char& getValue()
    {
        return _data;
    }

	//Returns true if the current Trie node represents the end of
	//a word.
    bool isWord() const
    {
		_children.find(_sentinel) != _children.end();
    }

	//Returns true when the current Trie node has the value of 
	//the sentiel node
    bool isSentinel() const
    {
        return _data == _sentinel;
    }

	//returns true when the Trie node has at least one child
    bool hasChild(char index) const
    {
		return _children.find(index) != _children.end();
    }

    void setChild(char index, TrieNode *node)
    {
        _children[index] = node;
    }

    TrieNode* getChild(char index)
    {
        return _children[index];
    }

	//returns a list of children.
	unordered_map<char, TrieNode*> getChildren()
	{
        return _children;
    }

	void addWord(const string& word) {
		if (word.size() > 0) {

			//if our word is our sentinal, we only add value, no children - base case
			if (word[0] == '$') {
				setValue('$');
				return;
			}

			//two cases 1- a prefix to our word already exists
			//so we strip the first character of our word, and pass
			//in the rest to the appropriate child
			
			char firstChar = word[0];
			string restOfWord = word.substr(1);

			//add a sentinal if there is not already one
			//if (restOfWord.at(restOfWord.size() - 1) != '$') {
			//	restOfWord += '$';
			//}

			if (!hasChild(firstChar)) {

				//our tree does not have this word
				//create a new child and add it to our root
				TrieNode* newChild = new TrieNode{};
				newChild->setValue(firstChar);
				setChild(firstChar, newChild);
			}

			//we should now have a child no matter what, 
			//with this prefix, add the suffix to the child
			if (hasChild(firstChar)) {
				TrieNode* child = getChild(firstChar);
				child->addWord(restOfWord);

			}
		}


		//2 - a prefix to our word does not exist
		//we must add the appropriate child,
		//and we must then strip our first letter
		//and add the rest to this new child.
	}

};

#endif // !TRIE_NODE_H
