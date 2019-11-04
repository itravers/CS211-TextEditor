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

		//strip the $ off of every word
		for (int i = 0; i < words.size(); i++) {
			//if (words[i].at(words[i].length - 1) == '$') {
			string newString = words[i].substr(0, words[i].length() - 1);
				words[i] = newString;
			//}
		}

		return words;
	}

	//TODO: implement
    vector<string> search(const string &word){

		//we wills store words here
		vector<string> matches;

		//search for this word
		if (_root != nullptr) {
			matches = _root->search(word);
		}

		//strip the $ off of every word
		for (int i = 0; i < matches.size(); i++) {
			string newString = matches[i].substr(0, matches[i].length() - 1);
			matches[i] = newString;
		}
        return matches;
    }
};

#endif // !TRIE_H
