#pragma once
#include "BSTNode.h"
#include "libraries.h"
//will eventually turn this into a class template
class BST
{
private:
	BSTNode* pRoot;
	fstream morseFile;
	void chopTree(BSTNode* pNode);
	void insert(BSTNode* pTree, Data newData);
	void printTree(BSTNode* pTree) const;
	string search(BSTNode* pTree, char searchChar, string& result) const;
public:
	/*Constructors/Destructors*/
	BST();
	~BST();

	/*Member Functions*/
	bool isEmpty();
	void printTree() const;
	string search(char searchChar) const;
	void testSearch();
};

