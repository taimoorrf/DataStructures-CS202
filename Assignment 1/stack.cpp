#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"

///Assuming front of list as top of stack

template <class T>
Stack<T>::Stack()
{
	///Constructor of list is automatically called
}

template <class T>
Stack<T>::Stack(Stack<T>& otherStack): list(otherStack.list)
{
	
}

template <class T>
Stack<T>::~Stack()
{
	///Desctuctor of list is automatically called
}

template <class T>
void Stack<T>::push(T item)
{
	list.insertAtHead(item);
}

template <class T>
T Stack<T>::top()
{
	return list.getHead()->value;
}

template <class T>
T Stack<T>::pop()
{
	T val=top();
	list.deleteHead();
	return val;
}


template <class T>
int Stack<T>::length()
{
	return list.length();
}

template <class T>
bool Stack<T>::isEmpty()
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
