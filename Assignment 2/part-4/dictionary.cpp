#ifndef __DICTIONARY_CPP
#define __DICTIONARY_CPP
#include "dictionary.h"
#include <time.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <chrono>

Dictionary::Dictionary() {
	wordsTree = NULL; 
}

Dictionary::~Dictionary(){
    delete wordsTree;
}

void Dictionary::initialize(string wordsFile) {
	wordsTree = new BST<string>;
	ifstream x;
	x.open(wordsFile);
	string data;
	while(!x.eof())
	{
		x >> data;
		cout<<data<<endl;
		insertWord(data);
	}
	x.close();
}

bool Dictionary::deleteWord(string word) {
	if (wordsTree != NULL)
	{
		wordsTree->delete_node(word);
		return true;
	}
	return false;
}
bool Dictionary::editWord(string oldWord, string newWord) {
	if (wordsTree == NULL)
	{
		return false;
	}

	if (wordsTree->search(oldWord) != NULL)
	{
		wordsTree->insert(oldWord, newWord);
		wordsTree->delete_node(oldWord);
		return true;
	}
	return false;
}
bool Dictionary::insertWord(string word) {
	if (wordsTree != NULL)
	{
		wordsTree->insert(word, word);
		return true;
	}
	return false;
}
node<string>* Dictionary::findWord(string word) {
	//clock_t t; 
    //t = clock();
    // TODO your code here
    //t = clock() - t; 
    //double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds 
    auto startingTime = chrono::steady_clock::now(); //Storing time before search
    node<string>* data = wordsTree->search(word);
    auto endingTime = chrono::steady_clock::now(); //String time after search

    cout << "findWord() took " << chrono::duration_cast<chrono::nanoseconds>(endingTime - startingTime).count() << " nanoseconds to search for " << word << endl;  
    return NULL; // TODO
}

#endif

int main() {
	Dictionary d;
	d.initialize("words.txt");
	cout<<"Dictionary made"<<endl;
	string words[26] = {"alceste", "broad-tired", "citharoedus", "dimethylbenzene",
						"escorted", "fightwite", "gymnast", "hyenine",
						"individuation", "jumbo", "kalon", "like-sex",
						"miswish", "naivite", "overcalled", "pseudotropine", 
						"quasi-cordial", "reichsmarks", "skiddier", "topass",
						"unhating", "vernon", "whetted", "xenos", "yous", "zoomechanics"};
	for (int i = 0; i < 26; i++)
	{
		d.findWord(words[i]);
	}
return 0;
}

