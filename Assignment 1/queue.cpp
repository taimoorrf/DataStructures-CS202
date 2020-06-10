#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

///Assuming head as the front of the queue

template <class T>
Queue<T>::Queue()
{

}
    
template <class T>
Queue<T>::Queue(Queue<T>& otherQueue): list(otherQueue.list)
{

}

template <class T>
Queue<T>::~Queue()
{

}

template <class T>
void Queue<T>::enqueue(T item)
{
	list.insertAtTail(item);
}

template <class T>
T Queue<T>::front()
{
	return list.getHead()->value;
}

template <class T>
T Queue<T>::dequeue()
{
	T val=front();
	list.deleteHead();
	return val;
}

template <class T>
int Queue<T>::length()
{
	return list.length();
}

template <class T>
bool Queue<T>::isEmpty()
{
	if(list.getHead==NULL)
	{
		return 1;	
	}
	else
	{
		return 0;
	}
}


#endif
