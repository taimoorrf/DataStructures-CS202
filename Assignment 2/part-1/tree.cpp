#ifndef __TREE_CPP
#define __TREE_CPP
#include "tree.h"

// try to make get_node() and get_file() after tree initialization


Tree::Tree(string data)
{
	TreeItem* new_node= new TreeItem();
	new_node->id = 1;

	// write the rest of the code here
	new_node->container.push_back(VCS_node(data,0));
	new_node->latest_data = data;
	root = new_node;
}

Tree::~Tree()
{
	delete root;
}


void Tree::branch(int id)
{	

}

void Tree::merge(int src_id,int dst_id)
{

}

void Tree::commit(int src_id,string new_data)
{ 

}

string Tree::get_file(int id, int t_stamp)
{

} 

TreeItem* Tree::get_node(int id)
{
	if (root == NULL)
	{
		return NULL;
	}
	
} 

vector<merge_state> Tree::merge_history()
{
	return history;
}

void Tree::level_traversal() 
{ 
	if(root == NULL)
	{
		return;
	}

	Queue <TreeItem*> tempQueue;	//Make a temporary queue
	tempQueue.enqueue(root);		//Add root to the front of the queue
	while(tempQueue.isEmpty() != true)
	{
		TreeItem* temp = tempQueue.front();
		int children = temp->child.size();
		cout<<"ID: "<<temp->id<<endl;	//Print ID of front
		cout<<"Latest data: "<<temp->latest_data<<endl;		//Print data of front
		if (temp->child[0] != NULL)
		{
			for (int i=0;i<children;i++)
			{	
				tempQueue.enqueue(temp->child[i]);	//Enqueue all the children of the front most node
			}	
		}

		tempQueue.dequeue();	//Dequeue the front most node
	}
	return;
} 


#endif
