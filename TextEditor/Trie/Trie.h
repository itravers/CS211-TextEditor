#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"
#include <string>
#include <cctype>
using namespace std;

class Trie
{
private:
    TrieNode *_root = nullptr;

protected:

public:
    Trie()
    {
        _root = new TrieNode{};
    }

    virtual ~Trie()
    {
        //TODO: clean up memory
		//delete _root;
    }

	//TODO: implement
    void addWord(const string &word){

		//add a sentinal if our word does not already have one
		string newWord = word;
		if (newWord.at(newWord.size() - 1) != '$') {
			newWord += '$';
			}
		_root->addWord(newWord);

		
    }

	vector<string> getWords() {
		vector <string> words =_root->getWords();
		return words;
	}

	//TODO: implement
    vector<string> search(const string &word)
    {
        vector<string> matches;
        return matches;
    }
};

#endif // !TRIE_H
