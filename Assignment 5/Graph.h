#ifndef GRAPH__H
#define GRAPH__H
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <set>
#include <algorithm>
#include <queue>
// You may include more libraries.

using namespace std;

class node;

class edge
{
	// You may add more variables and functions in this class
	public:
		node* Origin;
		node* Dest;
		float weight;	
};

class node
{
	// You may add more variables and functions in this class
	public:
		bool visit; // flag to check if the node has been already visited
		string name;
		vector<edge> edges; // edges connected to node
		vector<node*> connectedWith; //Storing all the nodes with which my current node is connected
};	

class Graph
{
	public:
		vector<node*> Mst; // minimum spanning tree
		vector<node*> friends;
		vector<edge> connections;
		Graph(string filename, bool isUnitLenght);
		void display(node* temp);// displays the graph

		bool Reachable(string start, string dest);
		vector<node*> Prims();
		vector<node*> Kruskal(); //runs kruskal algorithm and returns the Minimum spanning tree
		vector<node*> Dijkstra(string start, string dest, float &d);
		node* findNode(string name);
		void displayConnections();
		void displayFriends();
		void setAllToZero();
		void displayEdges(string name);
		node* findMin(node* n);
		edge* findEdgeBetween(string orig, string des);
};

#endif

