#ifndef CHAINING_CPP
#define CHAINING_CPP
#include "Chaining.h"
#include "hashfunctions.cpp"

HashC::HashC(int size){

	tableSize = size;
	hashTable = new LinkedList<string>[size];

}
HashC::~HashC(){

	delete hashTable;

}

unsigned long HashC :: hash(string input){

	return madCompression(bitHash(input), tableSize);
 
}

void HashC::insert(string word){

	unsigned long key = hash(word);
	hashTable[key].insertAtHead(word);
} 

ListItem<string>* HashC :: lookup(string word){

	unsigned long key = hash(word);
	ListItem<string>* temp = hashTable[key].getHead();	
	temp = hashTable[key].searchFor(word);

	return temp;
}

void HashC :: deleteWord(string word){

	unsigned long key = hash(word);
	hashTable[key].deleteElement(word);
	
}

#endif