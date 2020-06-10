//include any header files as required
#include "cacheClass.cpp"
#include <fstream>
#include <sstream>
#include <vector>

//Discussed some of the logics with my friend Ayaz Ur Rehman 21100036. 
//Helper functions 
string readFromDictionary(unsigned long key)
{
	ifstream in;
	in.open("dictionary.txt");
	string data = "a";
	unsigned long number;
	string word;
	while(!in.eof())
	{
		getline(in, data);
		if (number == key)
		{	
			break;
		}
	}

		istringstream iss(data);
		iss >> number;
		iss >> word;
		in.close();
		return word;
}


void cachedSearch(string file)
{
	ifstream infile(file);
	string word = "";
	unsigned long ID;
	char c;
	cache mycache;
	while(true)
	{
		infile>> ID;
		infile>>c;

		block* mysearch = mycache.lookup(ID);

		if(mysearch != NULL)
			word = mysearch->value;
		else
		{
			word = readFromDictionary(ID);
			mycache.insert(ID, word);
		}
		cout<<word<<" ";	
	}
	infile.close();
}


int main()
{

	cachedSearch("secret1.txt");

	return 0;
}