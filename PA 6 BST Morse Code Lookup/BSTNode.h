#pragma once
#include "libraries.h"
#include "Data.h"

template<class from, class to>
class BSTNode
{
private:
	Data<from, to>* mData;
	BSTNode<from, to>* pLeft;
	BSTNode<from, to>* pRight;
public:

	/*Constructors/Destructors*/
	BSTNode(from newEng, to newMorse);

	/*Getters*/
	BSTNode<from, to>* getLeft();
	BSTNode<from, to>* getRight();
	from getEng();
	to getMorse();

	/*Setters*/
	void setLeft(BSTNode<from, to>* newNode);
	void setRight(BSTNode<from, to>* newNode);
};


template<class from, class to>
BSTNode<from, to>::BSTNode(from newEng, to newMorse)
{
	this->mData = new Data<from, to>(newEng, newMorse);
	pLeft = nullptr;
	pRight = nullptr;
}

template<class from, class to>
BSTNode<from, to>* BSTNode<from, to>::getLeft()
{
	return this->pLeft;
}

template<class from, class to>
BSTNode<from, to>* BSTNode<from, to>::getRight()
{
	return this->pRight;
}

template<class from, class to>
from BSTNode<from, to>::getEng()
{
	return mData->getEnglish();
}

template<class from, class to>
to BSTNode<from, to>::getMorse()
{
	return mData->getMorse();
}

template<class from, class to>
void BSTNode<from, to>::setLeft(BSTNode<from, to>* newNode)
{
	this->pLeft = newNode;
}

template<class from, class to> 
void BSTNode<from, to>::setRight(BSTNode<from, to>* newNode)
{
	this->pRight = newNode;
}


