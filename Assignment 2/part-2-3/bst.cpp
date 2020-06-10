#ifndef __BST_CPP
#define __BST_CPP
#include "bst.h"
#include <iostream>
#include <queue>
#include <algorithm>
// HELPER FUNCTIONS HERE...
template <class T>
BST<T>::BST(){
	root = NULL;
}

template <class T>
BST<T>:: ~BST(){

    // your destructor code goes here
    delete root;

}

template <class T>
int BST<T> :: height (node<T>* p){
   // your find height code goes here
    if (p == NULL)
    {
        return 0;
    }
    else 
    {
    	return p->height;
    }       
}

template <class T>
int BST<T> :: balanceFactor(node<T>* p){
    // you can use this to find balance factor.
    if (p == NULL)
    {
        return 0;
    }
    int rightHeight = height(p->right);
    int leftHeight = height(p->left);
    return leftHeight - rightHeight;

}

template <class T>
void BST<T> :: fixHeight(node<T>* p){
    // use this function to fix height of a node after insertion or deletion.
    //node<T>* temp = p;
    if (p == NULL)
    {
    	return;
    }
    p->height = max(height(p->left), height(p->right)) + 1;
}

// ROTATING HELPERS 
template <class T>
node<T>* BST<T> :: rotateleft(node<T>* p){
    // Rotate left code goes here.
    if (p == NULL)
    {
    	return NULL;
    }
    
    node<T>* rightChild = p->right;
    p->right = rightChild->left; 
    rightChild->left = p;
    
    fixHeight(p);
    fixHeight(rightChild);
    return rightChild;
}

template <class T>
node<T>* BST<T> :: rotateright(node<T>* p){
    // Rotate right code goes here
	if (p == NULL)
    {
    	return NULL;
    }

    node<T>* leftChild = p->left;
    p->left = leftChild->right; 
    leftChild->right = p;
    
    fixHeight(p);
    fixHeight(leftChild);
    return leftChild;
}

template <class T>
node<T>* BST<T> :: balance(node<T>* p){
	if (p == NULL)
	{
		return NULL;
	}
	int BFactor= balanceFactor(p);
	if (BFactor > 1) //Left heavy case
	{
		if (balanceFactor(p->left) > -1) //Left left case
		{
			p = rotateright(p);
		}
		else                              //Left right case
		{
			p->left = rotateleft(p->left);
			return rotateright(p);
		}

	}
	else if (BFactor < -1)                 //Right heavy case
	{
		if (balanceFactor(p->right) > -1) //Right Left case
		{
			p->right = rotateright(p->right);
			return rotateleft(p);
		}

		else                              //Right right case
		{
			p = rotateleft(p);
		}
	}
    fixHeight(p);
    return p;
    // Balancing code goes here. You might need to find balance factor and call appropriate rotations.
}
// CLASS FUNCTIONS HERE
template <class T>
void BST<T> :: insert(string value,T k){
    root = insertHelper(value,k,root);
}
// insertion helper
template <class T>
node<T>* BST<T> :: insertHelper(string value,T k, node<T> *p) { // note we need a helper because we need recursive calls
    // Insertion code goes here.
    if (p == NULL)
    {
        p = new node<T>(k, value);
        return balance(p);
    }
    if (k > p->key)
    {
        p->right = insertHelper(value, k, p->right);
    }
    else
    {
        p ->left = insertHelper(value, k, p->left);
    }
    //return p;
    return balance(p);	//Use for AVL
}
template<class T>
node<T>* BST<T> :: search(T key){
    // Search code goes here.
    node<T>* temp = root;
    while(temp != NULL)
    {
        if (temp->key == key)
        {
            return temp;
        }
        if (key > temp->key)
        {
            temp = temp->right;
        }
        else
        {
            temp = temp->left;
        }
    }
    temp = NULL;
    return NULL;
}
// DELETE HELPER FUNCTIONS
template<class T>
node<T>* BST<T> :: findmin(node<T> *p){
    // This function finds the min node of the tree.
    if (p == NULL)
    {
        return NULL;
    }
    if (p->left != NULL)
    {
        findmin(p->left);
    }
    else 
    {
    	return p;
    }
}

template<class T>
node<T>* BST<T>::removemin(node<T>* p) {
    node<T>* min = findmin(p);
    return remove(min);
    // This function recursively finds the min node and deletes it.
}

template<class T>
void BST<T>::delete_node(T k){
    root = remove(root, k);
}

template<class T>
node<T>*  BST<T>::remove(node<T>* p, T k) // k key deletion from p tree
{
	if (p == NULL)
	{
		return NULL;
	}
	if (k > p->key)
	{
		p->right = remove(p->right, k);
	}
	else if (k < p->key)
	{
		p->left = remove(p->left, k);
	}
	else
	{
		if (p->right == NULL) //Only left child exists
		{
			node<T>* toDelete = p;
			p = p->left;
			delete toDelete;
			toDelete = NULL;
		}
		else if (p->left == NULL) //Only right child exists
		{
			node<T>* toDelete = p;
			p = p->right; 
			delete toDelete;
			toDelete = NULL;
		}
		else if (p->right == NULL && p->left == NULL) //Only left child exists
		{
			delete p;
			p = NULL;
		}
		else //If two childern
		{
			node<T>* smallestRight = findmin(p->right);
			p->value = smallestRight->value;
			p->key = smallestRight->key;
			p->right = remove(p->right, smallestRight->key);
		} 
	}
    
    //return p;
    return balance(p);   //Use for AVL
    // This function uses findmin and deletemin to delete arbitrary node in the tree.
}
template<class T>
node<T>* BST<T>::getRoot(){
    return root;
}
#endif
