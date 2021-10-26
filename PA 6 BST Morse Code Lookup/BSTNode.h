#pragma once
#include "libraries.h"
#include "Data.h"
//will eventually turn this into a class template
class BSTNode
{
private:
	Data mData;
	BSTNode* pLeft;
	BSTNode* pRight;
public:

	/*Constructors/Destructors*/
	BSTNode(Data newData);

	/*Getters*/
	BSTNode* getLeft();
	BSTNode* getRight();
	Data getData();

	/*Setters*/
	void setLeft(BSTNode* newNode);
	void setRight(BSTNode* newNode);
};

