#ifndef __HEAP_CPP
#define __HEAP_CPP
#include "heap.h"
#include<algorithm>


MinHeap::MinHeap(int cap)
{
	harr = NULL;
	capacity = 1000000;
	heap_size = 0;
}

void MinHeap::MinHeapify(int i)
{
	int l = left(i); 
    int r = right(i); 
    int min = i; 
    if (l < heap_size && harr[l] < harr[i]) 
        min = l;

    if (r < heap_size && harr[r] < harr[min]) 
        min = r; 
    if (min != i) 
    { 
        swap(harr[i], harr[min]); 
        MinHeapify(min); 
    } 
}
 
int MinHeap::parent(int i)
{
	return (i-1)/2;
}
 
int MinHeap::left(int i)
{
	return (2*i)+1;
}
 
int MinHeap::right(int i)
{
	return (2*i)+2;
}
 
int MinHeap::extractMin()
{
	if (harr == NULL)
	{
		return INT_MIN;
	}	

	int min = harr[0];
	harr[0] = harr[heap_size -1];
	heap_size--;
	MinHeapify(0);
	
	return min;
}
 
void MinHeap::decreaseKey(int i, int new_val)
{
	harr[i] = new_val;

	while(i != 0 && harr[i] < harr[parent(i)]) 
    { 
       swap(harr[parent(i)], harr[i]); 
       i = parent(i); 
    } 
}
 
int MinHeap::getMin()
{
	return harr[0];
}
 
void MinHeap::deleteKey(int i)
{
	if (i > heap_size-1)
	{
		return;
	}

	decreaseKey(i, -1); 
    extractMin(); 
}
 
void MinHeap::insertKey(int k)
{
	
	if (harr == NULL)
	{
		harr = new int[capacity];
	}

	if (heap_size == capacity)
	{
		return;
	}

	harr[heap_size] = k;
	heap_size++;
	int i = heap_size - 1;
	while(i != 0 && harr[i] < harr[parent(i)]) 
    { 
       swap(harr[parent(i)], harr[i]); 
       i = parent(i); 
    }
}

int* MinHeap::getHeap()
{
	return harr;
}

#endif