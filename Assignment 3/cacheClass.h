#ifndef CACHECLASS_H
#define CACHECLASS_H

#include <string>
#include <iostream>

using namespace std;
class block{
    public:
        unsigned long key;
        string value;
        int frequency;
        block(unsigned long _key,string _value){
            key = _key;
            value = _value;
            frequency = 1;
        }
};

class cache{
    private:
        block** hashTable;
        long tableSize;
        unsigned long hash(unsigned long key); 
        long count; 
    
    public:
    cache();
        ~cache();
        void insert(unsigned long key, string value);
        block* lookup(unsigned long key);
};

#endif
