
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <bitset>
#include <cmath>
#include "Tree-Path.h"

using namespace std;

vector<string> Tree::parseString(string s) //parse string by / character
{
	 int index = 0;
	 int i = -1;
	vector<string> holder; //Use local vector to accumulate each file name 
    while (index < s.length()) 
    {  
      if (s[index] == '/') 
      { 
        i++;
		index++;
		string t = "";
		holder.push_back(t);
	  }
	  holder[i] += s[index]; 
	  index++;
    }
	reverse(holder.begin(), holder.end()); //reverse vector before returning to facilitate tree insertion functions
	return holder;
}

vector<string> Tree::parseString2(string s) // parse string by | 
{
	 int index = 0;
	 int i = 0;
	vector<string> holder;
	holder.push_back("");
    while (index < s.length()) 
    {
      if ( (s[index] == '|') ) 
      {
        i++;
		index++;
		string t = "";
		holder.push_back(t);
	  }
	  holder[i] += s[index];
	  index++;
    }
	reverse(holder.begin(), holder.end()); //reverse vector to facilitate tree insertion functions
	return holder;
}

void Tree::insertIntoTreeHelper(vector<string> v1,vector<Node*> &v2) 
{
	if (v1.empty())
		return;
	std::string fileName = v1[v1.size() - 1]; //File to search for is at end of v1 because of reversal done by parseString
	bool containsString = false; //Assume v2 (vector of Nodes) does not have node with file name corresponding to fileName
	int index = 0; //index corresponding to element of v2 to store rest of file path
	for (int i = 0; i < v2.size(); i++)
	{
		if (v2[i]->s == fileName)
		{
			containsString = true; 
			index = i; //Node v2[i] corresponds to string with correct file name, so use that index for further recursion
			break;
		}
	}
	
	if (!containsString)  
	{
		Node* n = new Node;  //file name not already present, so insert new node with that file name
		n->s = fileName;
		v2.push_back(n);
		index = v2.size() - 1; //since new element is inserted at end, use last index for further recursion
	} 
	v1.erase(v1.end() - 1); //Since file names are stored in reverse order, delete last element 
	//reversing string in parseString rendered deletion more efficient since erasing last element of vector is O(1) operation 
	
	insertIntoTreeHelper(v1, v2[index]->v);
	
}
void Tree::insertIntoTree(string s)
{   //Use helper function so recursion can be utilized
	insertIntoTreeHelper(parseString(s), globalVector); //v1 contains vector of strings in the file path, 														//v2 contains global vector which contains all root nodes 
}

void  Tree::dualInsertIntoTreeHelper(vector<string> v1,vector<Node*> &v2) 
{
	//v1 contains vector of strings in the file path, so v1[0] is first string in file path
	//v2 contains global vector which contains all root nodes 

	if (v1.empty())
		return;
	vector<std::string> vectorsize2; //vector of strings produced by parseString2 should have only two elements
	if (v1.size() == 1)				 //v1's size is 1, so last file (or pair of files) in path is being inserted
		vectorsize2 = parseString2(v1[0]); //parse this string by |
	if (vectorsize2.size() == 2)
	{
		bool containsString1 = false;     //Use same algorithm to check and insert as insertTree, but with distinct variables
		bool containsString2 = false;
	std::string firstFile = vectorsize2[0];
	std::string secondFile = vectorsize2[1];
	int index = 0; //index corresponding to element of v2 to store rest of file path
	for (int i = 0; i < v2.size(); i++)
	{
		if ( (v2[i]->s == firstFile) ) 
		{
			containsString1 = true;
			index = i;
		}
		if ( (v2[i]->s == secondFile) ) 
		{
			containsString2 = true;
			index = i;
		}

	}
	
	if (!containsString1)
	{
		Node* n1 = new Node;
		n1->s = firstFile;
		v2.push_back(n1);
		index = v2.size() - 1;
	} 
	if (!containsString2)
	{
		Node* n2 = new Node;
		n2->s = secondFile;
		v2.push_back(n2);
		index = v2.size() - 1;
	} 

	return;
	}
	//v1 has not yet been cut down to size 1, so use insertTree algorithm
	else
	{
	bool containsString = false;
	std::string file = v1[v1.size() - 1];
	int index = 0; //index corresponding to element of v2 to store rest of file path
	for (int i = 0; i < v2.size(); i++)
	{
		if (v2[i]->s == file)
		{
			containsString = true;
			index = i;
			break;
		}
	}
	
	if (!containsString)
	{
		Node* n = new Node;
		n->s = file;
		v2.push_back(n);
		index = v2.size() - 1;
	} 
	v1.erase(v1.end() - 1);
	
	dualInsertIntoTreeHelper(v1, v2[index]->v);

	}
	
}
void Tree::dualInsertIntoTree(string s) 
{
	dualInsertIntoTreeHelper(parseString(s), globalVector);
}

vector<string> Tree::combo(vector<string> vec)
{
	double size = vec.size();
	vector<std::string> v;
	if (vec.size() == 1)
		return vec;
	else
	{
	for (int i = 1; i < pow(2, double(size)); i++)
	{
		bitset<32> b = bitset<32>(i); //Obtaining bit representation of each number from 1 to 2^n will allow all combos to be found
		std::string s;
		int j = 0;
		for (int i = 0; i < 32; i++) //Treating bit representation as an array of bools: if element is true, turn corresponding element in vector of strings on
		{
			if (b[i] == 1 && j == 0)   
			{
				s += vec[i];           //if first element, don't precede with - character
				j++;
			}
			else if (b[i] == 1)
			{
				s += "-"; 
				s += vec[i];
			}
		}
		v.push_back(s);       //add combo element to combo vector
	}
	return v;
	}
}
void  Tree::combinatorialExplosionInsertIntoTreeHelper(vector<string> v1,vector<Node*> &v2) 
{
	if (v1.empty())
		return;
	bool containsString = false;
	std::string file = v1[v1.size() - 1];
	int index = 0; //index corresponding to element of v2 to store rest of file path
	for (int i = 0; i < v2.size(); i++)  //Again use similar algorithm to insert tree
	{
		if (v2[i]->s == file)
		{
			containsString = true;
			index = i;
			break;
		}
	}
	if (!containsString && v1.size() == 1) //if v1 is 1, final string after / is reached, so parse string, use combo function
	{
		std::vector<std::string> initialVector = parseString2(v1[0]);
		std::vector<std::string> vectorExplosion = combo(initialVector);
		for (int i = 0; i < vectorExplosion.size(); i++) //insert all combinations into tree
		{
			Node* n = new Node;
			n->s = vectorExplosion[i];
			v2.push_back(n);
		}
		return;
	}
		
	else if (!containsString)
	{
		Node* n = new Node;
		n->s = file;
		v2.push_back(n);
		index = v2.size() - 1;
	} 
	v1.erase(v1.end() - 1);
	
	combinatorialExplosionInsertIntoTreeHelper(v1, v2[index]->v);
	
}
void Tree::combinatorialExplosionInsertIntoTree(string s) 
{
	combinatorialExplosionInsertIntoTreeHelper(parseString(s), globalVector);
}

void  Tree::combinatorialExplosionAllLevelsInsertIntoTreeHelper(std::vector<std::string> v1,std::vector<Node*> &v2) 
{
	//v1 contains vector of strings in the file path, so v1[0] is first string in file path
	//v2 contains global vector which contains all root nodes 

	if (v1.empty())
		return;
	bool containsString = false;
	std::string file = v1[v1.size() - 1];
	int index = 0; //index corresponding to element of v2 to store rest of file path
	for (int i = 0; i < v2.size(); i++)	//Use same algorithm as combinatorialExplosionInsertIntoTree, but don't specify last level
	{
		if (v2[i]->s == file)
		{
			containsString = true;
			index = i;
			break;
		}
	}
	if (!containsString)
	{
		std::vector<std::string> initialVector = parseString2(file);
		std::vector<std::string> vectorExplosion = combo(initialVector);
		for (int i = 0; i < vectorExplosion.size(); i++)
		{
			Node* n = new Node;
			n->s = vectorExplosion[i];
			v2.push_back(n);
		}
		index = v2.size() - vectorExplosion.size();
	}
	v1.erase(v1.end() - 1);
	for (int a = index; a <= v2.size() - 1; a++) 
		combinatorialExplosionAllLevelsInsertIntoTreeHelper(v1, v2[a]->v);
}

void Tree::combinatorialExplosionAllLevelsInsertIntoTree(std::string s)
{
	combinatorialExplosionAllLevelsInsertIntoTreeHelper(parseString(s), globalVector);
}

std::string Tree::collapseTreeHelper(std::vector<Node*> vec)
{
	if (vec.size() == 0)
		return "";
	std::string s;
	s += "/";
	for (int i = 0; i < vec.size(); i++)
	{
		bool containsDash = false; //At any given level, only print out element if it does not have dash
		for (int j = 0; j < (vec[i]->s).size(); j++)
		{
			if ((vec[i]->s)[j] == '-')
			{
				containsDash = true;
				break;
			}
		}
		if (!containsDash && i != 0)
			s += "|";
		if (!containsDash)
			s += vec[i]->s;
	}
		return (s + collapseTreeHelper(vec[0]->v)); //Collapse next level
}

std::string Tree::collapseTree()
{
	return collapseTreeHelper(this->globalVector);
}

std::string Tree::synonymHelper (std::vector<std::string> v1,std::vector<Node*> &v2) 
{
	std::string firstFile = v1[v1.size() - 1];
	int index = 0; 
	for (int i = 0; i < v2.size(); i++) //look for file as previously done
	{
		if (v2[i]->s == firstFile)
		{
			index = i;
			break;
		}
	}
	if (v1.size() == 2) //keep descending until only two levels left in file path
	{
		std::string secondFile = v1[v1.size() - 2];
		int index2 = 0;
		for (int i = 0; i < v2[index]->v.size(); i++)
		{
			if (v2[index]->v[i]->s == secondFile)
			{
				index2 = i;
				break;
			}
		}			//Find leaf nodes of last level and store in vector of strings
		std::vector<std::string> fileLeafNodes;
		for ( int j = 0; j < v2[index]->v[index2]->v.size(); j++)
			fileLeafNodes.push_back(v2[index]->v[index2]->v[j]->s);
		for (int a = 0; a < v2[index]->v.size(); a++)
		{
			std::vector<std::string> fileXLeafNodes;
			if (a == index2)
				continue;
			for (int j = 0; j < v2[index]->v[a]->v.size(); j++) //For each of other Nodes on same level, store their leaf nodes in vector of strings
				fileXLeafNodes.push_back(v2[index]->v[a]->v[j]->s);
			
			if (fileXLeafNodes.size() != fileLeafNodes.size())
				continue;
			
			bool equalLeafNodes = true;
			sort(fileXLeafNodes.begin(), fileXLeafNodes.end()); //sort each vector so they can more easily be compared
			sort(fileLeafNodes.begin(), fileLeafNodes.end());
			for (int j = 0; j < fileLeafNodes.size(); j++)
			{
				if (fileXLeafNodes[j] != fileLeafNodes[j])
				equalLeafNodes = false;
			}
			if (equalLeafNodes) //if the leaf nodes are equal, print out the synonym node that's on the same level as the last file in the argument file path
				return "/" + v1[1] + "/" + v2[index]->v[a]->s;
		}
		return ""; //otherwise, return an empty string
	}
	v1.erase(v1.end() - 1);
	if (v1.size() > 2)
		return ("/" + v1[v1.size() - 1] + synonymHelper(v1, v2[index]->v));
}

std::string Tree::synonym (std::string s)
{
	return synonymHelper(parseString(s), globalVector);
}


void Tree::printTreeHelper(vector<Node*> vec, int indent) //for testing, pass in argument of 0 for indent
{
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < indent; j++)
		{  cout << "   "; }
		cout << vec[i]->s << endl;
		printTreeHelper(vec[i]->v, indent + 1);
	}
}

void Tree::printTree()
{
	printTreeHelper(this->globalVector, 0);
}