Start Microsoft Visual Studio Project with Tree-Path.cpp, Tree-Path.h, and test.cpp
 Select PROJECT / Properties. In the Property Pages dialog, in the left panel,
 select Configuration Properties / Linker / System. 
In the right panel, select SubSystem, and in the drop down list to its right, 
Console (/SUBSYSTEM:CONSOLE). 

Select Debug->Start Without Debugging to run the submission. 

Edit test.cpp by creating Tree class variables within the main function and using the following functions:
[Enter the file path as a string.]

void insertIntoTree(std::string s); //PART 1: INSERT INTO TREE
void dualInsertIntoTree(std::string s);		  //PART 2: SUPPORT DUAL LEAF-NODE INSERTS
void combinatorialExplosionInsertIntoTree(std::string s); //PART 3: SUPPORT A COMBINATORIAL LEAF-NODE INSERT
void combinatorialExplosionAllLevelsInsertIntoTree(std::string s);//PART 4: SUPPORT COMBINATORIAL NODES AT ANY LEVEL
std::string collapseTree(); // PART 5: COLLAPSE A COMBINATORIAL TREE INTO A PATH
std::string synonym (std::string s); //PART 6: SUBTREE SIMILARITY DETECTION
void printTree(); //function for testing 

Run the submission by altering the main function as required. 