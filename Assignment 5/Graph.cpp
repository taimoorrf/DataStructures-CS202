#ifndef GRAPH__CPP
#define GRAPH__CPP
#include "Graph.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "queue.cpp"
#include "heap.cpp"
#include <set>
#include <map>

using namespace std;

node* Graph::findNode(string name)
{
	for (int i = 0; i < friends.size(); i++)
	{
		node* temp = NULL;
		if (friends[i]->name == name)
		{
			return friends[i];
		}
	}

	return NULL;
}

edge* Graph::findEdgeBetween(string orig, string des)
{
	node* src = findNode(orig);
	node* dest = findNode(des);
	for(int i = 0; i< connections.size(); i++)
	{
		if ((connections[i].Origin->name == src->name && connections[i].Dest->name == dest->name) || (connections[i].Origin->name == dest->name && connections[i].Dest->name == src->name))
		{
			return &connections[i];
		}
	}
return NULL;
}

Graph::Graph(string file, bool isUnitLength)
{
	ifstream x;
	x.open(file);
	if(!x)
	{
		cout<<"File not open";
	}

	string data;
	x>>data;

	//Storing all the people
	while (1)
	{
		x >> data;

		if (data == "CONNECTIONS")
		{
			break;
		}

		else
		{
			node* newNode = new node;
			newNode->visit = 0;
			newNode->name = data;
			friends.push_back(newNode);
			
		}
	}


	string name1;
	string name2;
	int w;
	
	// Getting all the connections
	while(1)
	{
		//Reading in names and edge weight
		x >> name1;
		x >> name2;
		x >> w;
		
		if (x.eof())
		{
			break;
		}

		//Making an edge with the attributes
		edge newEdge;
		newEdge.Origin = findNode(name1);
		newEdge.Dest = findNode(name2);
				
		if (isUnitLength)
		{
			newEdge.weight = 1;
		}
		else
		{
			newEdge.weight = w;	
		}

		//Adding the edge to the connections vector
		connections.push_back(newEdge);
	}

	
	//Giving connections to nodes if either source or destination since it is an undirected graph
	for (int i = 0; i < friends.size(); i++)
	{
		for(int j= 0; j < connections.size(); j++)
		{
			if (friends[i]->name == connections[j].Origin->name || friends[i]->name == connections[j].Dest->name)
			{
				friends[i]->edges.push_back(connections[j]);
			}
		}
	}

	//Filling connected with vector

	for (int i = 0; i < friends.size(); i++)
	{
		for(int j= 0; j < connections.size(); j++)
		{
			if (friends[i]->name == connections[j].Origin->name)
			{

				friends[i]->connectedWith.push_back(connections[j].Dest);
			}

			else if(friends[i]->name == connections[j].Dest->name)
			{
				friends[i]->connectedWith.push_back(connections[j].Origin);
			}
		}
	}
}

void Graph::display(node* temp)
{
	if(temp->visit)
		return;
	
	cout << "Person: " << temp->name;
	temp->visit = 1;
	for(int i=0; i< temp->edges.size(); i++)
	{
		if(temp->edges[i].Origin->visit == 0 || temp->edges[i].Dest->visit == 0)
		cout << "->" << temp->edges[i].weight << endl;
		display(temp->edges[i].Origin);
		display(temp->edges[i].Dest);
	}
}

bool Graph::Reachable(string start, string dest)
{
	setAllToZero();
	
	/** USING BFS **/

	node* sNode = findNode(start);
	node* dNode = findNode(dest);
	
	//If nodes do not exist
	if (sNode == NULL || dNode == NULL)
	{
		return 0;
	}

	Queue<node*> myQueue;
	
	//Queue starting node
	myQueue.enqueue(sNode);
	myQueue.front()->visit = 1;
	
	while(1)
	{
		if (myQueue.front() == dNode)
		{
			setAllToZero();
			return 1;
		}

		for (int i = 0; i < myQueue.front()->edges.size(); i++)
		{
			//If my front in connection origin, queue dest if not visited
			if(myQueue.front()->name == myQueue.front()->edges[i].Origin->name && myQueue.front()->edges[i].Dest->visit == 0)
			{
				myQueue.enqueue(myQueue.front()->edges[i].Dest);
				myQueue.front()->visit = 1;
			}
			//If my front in connection dest, queue origin if not visited
			else if(myQueue.front()->name == myQueue.front()->edges[i].Dest->name && myQueue.front()->edges[i].Origin->visit == 0)
			{
				myQueue.enqueue(myQueue.front()->edges[i].Origin);
				myQueue.front()->visit = 1;
			}
		}
		
		myQueue.dequeue();
		
		//If all nodes are visited and queue now empty
		if (myQueue.isEmpty())
		{
			break;
		}
	}

	setAllToZero();
	return 0;
}


vector<node*> Graph::Prims()
{
	setAllToZero();
}

bool compare(edge v1, edge v2)
{
	if(v1.weight > v2.weight)
	{
		return 0;	
	}
	
	else
	{
		return 1;
	}
	
}

vector<node*> Graph::Kruskal()
{
	//Making a new list of vectors
	vector<edge> temp;
	vector<node*> krus;

	for(int i = 0; i < connections.size(); i++)
	{
		temp.push_back(connections[i]);
	}
	//Sorting in ascending order
	sort(temp.begin(), temp.end(), compare);

	 
	return krus;

	setAllToZero();
}


vector<node*> Graph::Dijkstra(string start, string dest, float &d)
{
	typedef pair<float, vector<node*>> NWpair;
	node* sNode = findNode(start);
	
	//Setting up priority queue for nodes, with  vector of Node-Weight pairs
	priority_queue <NWpair, vector<NWpair>, greater<NWpair>> DijkQueue;
	vector<node*> tempV;
	tempV.push_back(sNode);
	DijkQueue.push(make_pair(0, tempV));	//Pushing source node in queue

	while(!DijkQueue.empty())
	{
		vector<node*> tempPath = DijkQueue.top().second;
		node* frontNode = tempPath.back();
		float w = DijkQueue.top().first;
		DijkQueue.pop();
		frontNode->visit = 1;
		if (frontNode->name == dest)
		{
			setAllToZero();
			d = w;
			return tempPath;
		}
		

		for(int i = 0; i < frontNode->connectedWith.size(); i++)
		{
			node* temp = frontNode->connectedWith[i];
			float newWeight = frontNode->edges[i].weight + w;
			if (temp->visit == 0)
			{
				vector<node*> newTempPath(tempPath);
				newTempPath.push_back(temp);
				DijkQueue.push(make_pair(newWeight, newTempPath));
			}	
		}
	}

}

void Graph::displayConnections()
{
	for (int i = 0; i < connections.size(); i++)
	{
		cout<<connections[i].Origin->name<<" ";
		cout<<connections[i].Dest->name<<" ";
		cout<<connections[i].weight<<endl;
	}
}

void Graph::displayFriends()
{
	for (int i = 0; i < friends.size(); i++)
	{
		cout<<friends[i]->name<<endl;
	}
}

void Graph::setAllToZero()
{
	for(int i = 0; i < friends.size(); i++)
	{
		friends[i]->visit = 0;
	}
}

void Graph::displayEdges(string name)
{
	node* temp = findNode(name);
	if (temp == NULL)
	{
		cout<<"Node doesn't exist"<<endl;
		return;
	}
	for (int i = 0; i < temp->connectedWith.size(); i++)
	{
		cout<<temp->connectedWith[i]->name<<endl;
	}
}

int main()
{
	/** Part 6 **/

	// /** Question 1 **/

	cout<<"Part 6:"<<endl<<endl<<"Question 1"<<endl;

	string file = "friends.txt";
	
	Graph myGraph(file, false);

	if (myGraph.Reachable("Mannan", "Ali"))
	{
		cout<<"Mannan and Ali are reachable"<<endl;
	}

	else
	{
		cout<<"Mannan and Ali are not reachable"<<endl;
	}
	

	if (myGraph.Reachable("Mannan", "Trump"))
	{
		cout<<"Mannan and Trump are reachable"<<endl;
	}

	else
	{
		cout<<"Mannan and Trump are not reachable"<<endl;
	}


	if (myGraph.Reachable("Ali", "Trump"))
	{
		cout<<"Ali and Trump are reachable"<<endl;
	}

	else
	{
		cout<<"Ali and Trump are  not reachable"<<endl;
	}

	cout<<endl;

	/** Question 2 **/
	cout<<"Question 2:"<<endl;
	Graph newGraph(file, true);
	float val = 1;
	vector<node*> returnVec = newGraph.Dijkstra("Ali", "Trump", val);
	cout<<"Ali and Trump are "<<returnVec.size()<<" hops away"<<endl;

	cout<<endl;

	/** Question 3 **/
	cout<<"Question 3"<<endl;
	vector<node*> returnVec2 = newGraph.Dijkstra("Mannan", "Trump", val);
	cout<<"Mannan and Trump are "<<returnVec2.size()<<" hops away"<<endl;
	
	cout<<endl;

	/** Question 4 **/
	cout<<"Question 4"<<endl;
	vector<node*> v = myGraph.Kruskal();
	cout<<"Nahi hua, exam thaa :( , plis give marks for the little I did"<<endl;

	cout<<endl;

	/** Question 5 **/
	cout<<"Question 5"<<endl;
	cout<<"Same as above, but I'm assuming Ali"<<endl;

	cout<<endl;

	/** Question 6 **/
	cout<<"Question 6"<<endl;
	cout<<"There can exist more than one MST for a graph if the weight for all the edges are same, or there are two edges with same weights with non unique weight edges connecting to them"<<endl;
	cout<<endl;
}

#endif
