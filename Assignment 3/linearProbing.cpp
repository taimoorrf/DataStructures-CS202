#ifndef LINEARPROBING_CPP
#define LINEARPROBING_CPP

#include "linearProbing.h"
#include "hashfunctions.cpp"


HashL::HashL(){
    tableSize = 1000; // you cant change this
    count = 0;
    hashTable = new block* [tableSize];

    for (int i = 0; i < tableSize; i++)
    {
    	hashTable[i] = NULL;
    }

}

HashL::~HashL(){

    for (int i = 0; i < tableSize; i++)
    {
    	delete hashTable[i];
    }
    delete [] hashTable;
}

unsigned long HashL :: hash(string value){

	return madCompression(bitHash(value), tableSize);
}

void HashL::resizeTable(){

	tableSize = tableSize*10;							// By a factor of 10 gives the best time efficiency
	block** newTable = new block* [tableSize];			//Making new table
	unsigned long key;
	for (int i = 0; i < tableSize; i++)
	{
		newTable[i] = NULL;
	}
	
	for (int i = 0; i < tableSize/10; i++)				//Copying value to new table
	{
		if (hashTable[i] != NULL)
		{
			key = hash(hashTable[i]->value);
			
			while(newTable[key] != NULL)		
			{
				key = (key + 1) % tableSize;
			}

			newTable[key] = hashTable[i];
			hashTable[i] = NULL; 
		}

	}

	delete[] hashTable;
	hashTable = newTable;
	newTable = NULL;
}

void HashL::insert(string value){


	double loadFactor = count/tableSize;
	if (loadFactor > 0.5)
	{
		resizeTable();
	}
	unsigned long key = hash(value);
	while(hashTable[key] != NULL)		
	{
		key = (key + 1) % tableSize;
	}

	hashTable[key] = new block(key, value);
	count++;
}

void HashL::deleteWord(string value){

	unsigned long key = hash(value);
	unsigned long originalKey = key;		
	do
	{
		if (hashTable[key] == NULL || hashTable[key]->value == value)
		{
			delete hashTable[key];
			hashTable[key] = NULL;
			count--;
			break;
		}
		else
		{
			key = (key + 1) % tableSize;	
		}
		
	}
	while(key != originalKey);
}

block* HashL::lookup(string value){

	unsigned long key = hash(value);
	unsigned long originalKey = key;		
	do
	{
		if (hashTable[key] == NULL || hashTable[key]->value == value)
		{
			return hashTable[key];
		}
		key = (key + 1) % tableSize;
	}
	while(key != originalKey);

}

#endif
