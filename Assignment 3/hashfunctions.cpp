#ifndef HASHFUNCTIONS_CPP
#define HASHFUNCTIONS_CPP
#include <string>
#include <iostream>
#include <cmath>

using namespace std;
// this takes in a string and returns a 64bit hash.
unsigned long polyHash(std::string value,int a = 9){

	unsigned long sum = 0;
	for (int i = 1; i < value.length(); i++)
	{
		sum += int(value[i-1]) * pow(a, value.length() - i);
	}
	
	return sum;
}

//does some bitwise operation and generates a 64bit hash.
unsigned long bitHash(std::string value){
	
	unsigned long bitWiseHash = 0;
	for (int i = 0; i < value.length(); i++)
	{
		bitWiseHash ^= (bitWiseHash << 5) + (bitWiseHash >> 2) + int(value[i]); 
	}

	return bitWiseHash;
}
// Size is the size of array maintained by the hashtable.
unsigned long divCompression(unsigned long hash,long size){
	
	unsigned long compressedHash = hash % size;
	return compressedHash;
}
// multiplication addition and division compression. 
unsigned long madCompression(unsigned long hash,long size,int m = 1993,int a = 1637){
	
	unsigned long compressedHash = (m*hash + a) % size;
	return compressedHash; 
}
#endif
// you may write your own program to test these functions.
