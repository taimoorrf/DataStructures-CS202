#ifndef DOUBLEHASH_CPP
#define DOUBLEHASH_CPP
#include "doubleHash.h"
#include "hashfunctions.cpp"
HashD::HashD(){
    tableSize = 10000; // you cant change this
    count = 0;
    hashTable = new block* [tableSize];

    for (int i = 0; i < tableSize; i++)
    {
    	hashTable[i] = NULL;
    }

}

HashD::~HashD(){

	for (int i = 0; i < tableSize; i++)
    {
    	delete hashTable[i];
    }
    delete [] hashTable;

}

unsigned long HashD::hash1(string value)
{
	return bitHash(value);			//Idhar polyHash()
}

unsigned long HashD::hash2(string value)
{
	return bitHash(value);
}

void HashD::resizeTable(){

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
			key = hash1(hashTable[i]->value) % tableSize;
			string value = hashTable[i]->value;
			int j = 0;
			while(newTable[key] != NULL)		
			{
				key = (hash1(value) + j*hash2(value)) % tableSize;
				j++;
			}

			newTable[key] = hashTable[i];
			hashTable[i] = NULL; 
		}

	}

	delete[] hashTable;
	hashTable = newTable;
	newTable = NULL;

}

void HashD::insert(string value){

	double loadFactor = (count*1.0)/tableSize;
	if (loadFactor > 0.3)
	{
		resizeTable();
	}
	unsigned long key = hash1(value) % tableSize;
	int i = 1;
	while(hashTable[key] != NULL)		
	{
		key = (hash1(value) + i*hash2(value)) % tableSize;
		i++;
	}

	hashTable[key] = new block(key, value);
	count++;
}

void HashD::deleteWord(string value){

	unsigned long key = hash1(value) % tableSize;
	unsigned long originalKey = key;
	int i = 1;		
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
			key = (hash1(value) + i*hash2(value)) % tableSize;	
			i++;
		}
		
	}
	while(key != originalKey);


}

block* HashD::lookup(string value){

	unsigned long key = hash1(value) % tableSize;
	unsigned long originalKey = key;		
	int i = 1;
	do
	{
		if (hashTable[key] == NULL || hashTable[key]->value == value)
		{
			return hashTable[key];
		}
		key = (hash1(value) + i*hash2(value)) % tableSize;
		i++;
	}
	while(key != originalKey);
}

#endif