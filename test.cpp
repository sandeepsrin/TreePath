#include <string>
#include <iostream>

#include "Tree-Path.h"
using namespace std;
int main()
{ 
	Tree a, b, c, d;
	a.insertIntoTree("/home/sports/favorites");
	a.insertIntoTree("/home/music/favorites");
	b.dualInsertIntoTree("/home/sports/football/NCAA|NFL");
	c.combinatorialExplosionInsertIntoTree("/home/music/rap|rock|pop");
	d.combinatorialExplosionAllLevelsInsertIntoTree("/home/sports|music/misc|favorites|other");
	cout << d.collapseTree() << endl;
	cout << a.synonym("/home/sports") << endl;
	a.printTree();
	b.printTree();
	c.printTree();
	d.printTree();
}