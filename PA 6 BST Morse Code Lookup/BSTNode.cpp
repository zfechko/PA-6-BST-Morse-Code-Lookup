#include "BSTNode.h"

/*Constructors*/
BSTNode::BSTNode(Data newData)
{
	pLeft = nullptr;
	pRight = nullptr;
	mData = newData;
}

/*Getters*/
BSTNode* BSTNode::getLeft()
{
	return pLeft;
}

BSTNode* BSTNode::getRight()
{
	return pRight;
}
 
Data BSTNode::getData()
{
	return this->mData;
}

/*Setters*/
void BSTNode::setLeft(BSTNode* newNode)
{
	pLeft = newNode;
}

void BSTNode::setRight(BSTNode* newNode)
{
	pRight = newNode;
}