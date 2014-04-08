#include <string>
#include <vector>
class Tree
{
private: 
struct Node 
{
	std:: string s;
	std:: vector<Node*> v;	//Number of children for a given member of tree not predetermined 
};
public:
	void insertIntoTree(std::string s); //PART 1: INSERT INTO TREE
	void dualInsertIntoTree(std::string s);		  //PART 2: SUPPORT DUAL LEAF-NODE INSERTS
	void combinatorialExplosionInsertIntoTree(std::string s); //PART 3: SUPPORT A COMBINATORIAL LEAF-NODE INSERT
	void combinatorialExplosionAllLevelsInsertIntoTree(std::string s);//PART 4: SUPPORT COMBINATORIAL NODES AT ANY LEVEL
	std::string collapseTree(); // PART 5: COLLAPSE A COMBINATORIAL TREE INTO A PATH
	std::string synonym (std::string s); //PART 6: SUBTREE SIMILARITY DETECTION
	void printTree();
private:
	std::vector<Node*> globalVector; //Vector containing root nodes of all inserted trees
	std::vector<std::string> parseString(std::string s); //parse string by / character
	std::vector<std::string> parseString2(std::string s); // parse string by | 
	void insertIntoTreeHelper(std::vector<std::string> v1,std::vector<Node*> &v2);
	void  dualInsertIntoTreeHelper(std::vector<std::string> v1,std::vector<Node*> &v2);
	void  combinatorialExplosionInsertIntoTreeHelper(std::vector<std::string> v1,std::vector<Node*> &v2);
	void  combinatorialExplosionAllLevelsInsertIntoTreeHelper(std::vector<std::string> v1,std::vector<Node*> &v2);
	std::vector<std::string> Tree::combo(std::vector<std::string> vec); //takes in vector of strings and returns vector of combinatorial explosion of strings
	std::string Tree::synonymHelper (std::vector<std::string> v1,std::vector<Node*> &v2);
	std::string Tree::collapseTreeHelper(std::vector<Node*> vec);
	void Tree::printTreeHelper(std::vector<Node*> vec, int indent);
};




