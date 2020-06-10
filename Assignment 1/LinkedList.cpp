#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include "LinkedList.h"

template <class T>
LinkedList<T>::LinkedList()
{
    head=NULL;
    tail=NULL;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{
    if (otherLinkedList.head==NULL)
    {
	head=NULL;
	tail=head;
    }
    head =new ListItem<T>(otherLinkedList.head->value);
    tail = head;
    ListItem<T>* traverser=otherLinkedList.head->next;

    while (traverser!=NULL)
    {
        insertAtTail(traverser->value);
        traverser=traverser->next;
    }
}

template <class T>
LinkedList<T>::~LinkedList()
{
    while(head!=NULL)
    {
        ListItem<T>* traverser;
        traverser=head;
        head=head->next;
        delete traverser;
    }
    delete head;
}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{
    if (head==NULL)
    {
        head=new ListItem<T>(item);
        head->next=NULL;
        head->prev=NULL;
        tail=head;
    }
    else
    {
        ListItem<T>* temp=new ListItem<T>(item);
        temp->next=head;
        temp->prev=NULL;
        head->prev=temp;
        head=temp;
        temp=NULL;
	delete temp;
    }
}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
    if (tail==NULL)     //If list is empty
    {
        insertAtHead(item);
    }
    else
    {
        ListItem<T>* temp=new ListItem<T>(item);
        temp->next=NULL;
        temp->prev=tail;
        tail->next=temp;
        tail=temp;
	temp=NULL;
        delete temp;
    }
}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
    ListItem<T>* traverser;
    traverser=head;
    while(traverser!=NULL)
    {
        if(traverser->value==afterWhat)
        {
            break;
        }
        else
        {
            traverser=traverser->next;
        }
    }
    ListItem<T>* temp=new ListItem<T>(toInsert);
    temp->prev=traverser;
    temp->next=traverser->next;
    traverser->next=temp;
    traverser=NULL;
    delete traverser;
}


template <class T>
ListItem<T>* LinkedList<T>::getHead()
{
    return head;
}

template <class T>
ListItem<T>* LinkedList<T>::getTail()
{
    return tail;
}

template <class T>
ListItem<T> *LinkedList<T>::searchFor(T item)
{
    ListItem<T>* traverser=head;
    while(traverser!=NULL)
    {
        if(traverser->value==item)
        {
            return traverser;
        }
        else
        {
            traverser=traverser->next;
        }
    }
    traverser=NULL;
    delete traverser;
    return NULL;
}

template <class T>
void LinkedList<T>::deleteElement(T item)
{
    ListItem<T>* temp;
    temp=searchFor(item);
    if (temp==NULL)
    {
        return;
    }
    else if (temp==tail)
    {
        deleteTail();
    }
    else if (temp==head)
    {
        deleteHead();
    }
    else
    {
	temp->prev->next=temp->next;
	temp->next->prev=temp->prev;
	delete temp;
    }
}

template <class T>
void LinkedList<T>::deleteHead()
{
    if (head==NULL)
    {
	return;
    }

    ListItem<T>* temp=head;
    head=head->next;
    if (head!=NULL)
    {
	head->prev=NULL;
    }
    delete temp;
}

template <class T>
void LinkedList<T>::deleteTail()
{   ///Question(Note to self): Why not working with tail pointer?
    ListItem<T>* traverser;
    if (traverser==NULL)
    {
        return;
    }
    if (traverser==head)
    {
        deleteHead();
    }
    traverser=head;
    while(traverser->next!=NULL)
    {
        traverser=traverser->next;
    }
    traverser->prev->next=NULL;
    delete traverser;
}

template <class T>
int LinkedList<T>::length()
{
    int counter=0;
    ListItem<T>* traverser=head;
    while(traverser!=NULL)
    {
        counter++;
        traverser=traverser->next;
    }
    return counter;
}

#endif
