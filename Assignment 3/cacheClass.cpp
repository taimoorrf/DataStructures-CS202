#include "cacheClass.h"
#include "hashfunctions.cpp"
#include <fstream>

cache::cache(){
    tableSize = 1000;
    count = 0;
    hashTable = new block* [tableSize];

    for (int i = 0; i < tableSize; i++)
    {
    	hashTable[i] = NULL;
    }

}

cache::~cache(){

    for (int i = 0; i < tableSize; i++)
    {
    	delete hashTable[i];
    }
    delete [] hashTable;
}

unsigned long cache::hash(unsigned long key){

	return madCompression(key, tableSize);
}

void cache::insert(unsigned long key, string value){

	unsigned long index = madCompression(key, tableSize);
	int i = 0;	
	if (count < tableSize)
	{	
		
		while(hashTable[index] != NULL)		
		{
			index = (index + 1) % tableSize;
		}

		hashTable[index] = new block(key, value);
		count++;	
	}

	else 
	{
		while (i < tableSize)
		{
			if (hashTable[i]->frequency > hashTable[key]->frequency)
			{
				continue;
			}

			else
			{
				key = i;
			}
			i++;
		}
		delete hashTable[key];
		hashTable[key] = NULL;
		hashTable[key] = new block(key, value);
	}

}

block* cache::lookup(unsigned long key){

	unsigned long index = hash(key) % tableSize;
	unsigned long originalIndex = index;		
	do
	{
		if (hashTable[index] == NULL || hashTable[index]->key == key)
		{
			hashTable[index]->frequency = hashTable[index]->frequency + 1;
			return hashTable[index];
		}
		index = (index + 1) % tableSize;
	}
	while(index != originalIndex);

}

