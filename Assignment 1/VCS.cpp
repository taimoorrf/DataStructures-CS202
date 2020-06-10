#ifndef VCS_CPP
#define VCS_CPP
#include "VCS.h"
#include<sstream>
#include<iostream>

///We are using stack because it follows the LIFO procedue which allows us to revert back and forth between immediate files

string reader(string file)  ///Helper function to avoid code repetition
{
   ifstream in;
   in.open((file + ".txt").c_str());
   stringstream x;
   x<<in.rdbuf();
   string data;
   data=x.str();
   in.close();
   return data;
}
//base constructor, init
VCS::VCS(string filename)
{
	curr_size=0;
	this->filename=filename;
}

//destructor
VCS::~VCS()
{
	///List destructor gets called since dynamic memory gets allocated to 		linked list in the stack
}


//time to commit
void VCS::commit(string msg)
{
        VCS_node temp(msg,curr_size);	///Making node for container 1
        container1.push(temp);
	string data;
	data=reader(filename);		///Reading data from file using helper

	ofstream out;
        out.open((filename +to_string(curr_size) + ".txt").c_str());
        out<<data;			///Writing to file
        out.close();
	curr_size++;

}

//print status of every version
void VCS::status()
{
	for(int i=0;i<5;i++)	///Since the manual said only 5 recent commits
	{
		container2.push(container1.pop());	///Pushing 5 commits 								onto container 2
	}
	for(int i=0;i<5;i++)
	{
		cout<<container2.top().message<<" time stamp: "<<container2.top().time_stamp;				///Printing status
		container1.push(container2.pop()); 	///Pushing back on 								container 1
	}
}

//goes one step back
string VCS::undo()
{
    container2.push(container1.top());		///Pushing top onto container 2
    container1.pop();				///Removing from main container
    curr_size--;				///Decrementing size
    string data=reader(filename+to_string(curr_size-1));	///Reading 									version file
    ofstream out;
    out.open((filename+".txt").c_str());	///Opening original file
    out << data;				///Wriing to original file
    out.close();
    return data;
}

//one step ahead
string VCS::redo()
{
    container1.push(container2.top());		///Pushing onto container 1
    container2.pop();				///Removing from container 2
    curr_size++;				///Increasing size
    string data=reader(filename+to_string(curr_size-1));	///Reading 									version file
    ofstream out;
    out.open((filename+".txt").c_str());	
    out << data;				///Writing to original file
    out.close();
    return data;
}

//goes t_stamp step back or ahead
string VCS::revert(int t_stamp)
{
	///Finding the required node
	if (t_stamp>(curr_size-1))	//If node is on container 2
	{
		while(container1.top().time_stamp!=t_stamp)
		{
			container1.push(container2.pop());
			curr_size++;
		}		
	}
	else 	//If node is on container 1, but below top
	{
		while(container1.top().time_stamp!=t_stamp)
		{
			container2.push(container1.pop());
			curr_size--;
		}
	}	
	
	///Once the node is on top of our main container
	string data=reader(filename+to_string(curr_size-1));
    	ofstream out;
    	out.open((filename+".txt").c_str());
    	out << data;
    	out.close();
    	return data;
}

#endif
