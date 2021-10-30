#pragma once
#include "BSTNode.h"
#include "libraries.h"

template<class from, class to>
class BST
{
private:
	BSTNode<from, to>* pRoot;
	fstream morseFile;
	void chopTree(BSTNode<from, to>* pNode);
	void insert(BSTNode<from, to>* pTree, from newEng, to newMorse);
	void printTree(BSTNode<from, to>* pTree) const;
	void search(BSTNode<from, to>* pTree, from searchChar, to& result) const;
public:
	/*Constructors/Destructors*/
	BST();
	~BST();

	/*Member Functions*/
	bool isEmpty();
	void printTree() const;
	to search(from searchChar) const;
	void testSearch(); //not an essential function for this assignment so I'm not making it in the template
	void convert();
};

template<class from, class to>
BST<from, to>::BST()
{
	pRoot = nullptr;
	this->morseFile.open("MorseTable.txt", ios::in);
	char tempChar;
	string tempString = "";

	while (!morseFile.eof())
	{
		getline(morseFile, tempString); //getting the line with the char/letter in it
		tempChar = tempString.c_str()[0]; //because strings work like an array, we extract the 0th index and set it to the char
		getline(morseFile, tempString);
		insert(this->pRoot, tempChar, tempString); //and then insert it into the tree
	}
	morseFile.close();
}

template<class from, class to>
BST<from, to>::~BST()
{
	this->chopTree(pRoot);
}

/*
isEmpty is a predicate function that returns true if the root of the BST is null and false if it isn't
*/
template<class from, class to>
bool BST<from, to>::isEmpty()
{
	return pRoot == nullptr;
}


/*
This is the private member insert function
There is no overloaded public version because this function is ONLY called in the tree's contructor
It takes a pointer to a node and a Data object to assign values for the node
Uses recursion to find the right place in the tree to insert
*/
template<class from, class to>
void BST<from, to>::insert(BSTNode<from, to>* pTree, from newEng, to newMorse)
{
	if (pTree == nullptr) //if the tree is empty
	{
		pRoot = new BSTNode<from, to>(newEng, newMorse); //insert at the root of the tree
	}
	else
	{
		if (pTree->getEng() > newEng)
		{
			//we need to go to the left
			if (pTree->getLeft() == nullptr)
			{
				//insert here
				pTree->setLeft(new BSTNode<from, to>(newEng, newMorse));
			}
			else
			{
				//traverse the left subtree
				insert(pTree->getLeft(), newEng, newMorse);
			}
		}
		if (pTree->getEng() < newEng)
		{
			//we need to go to the right
			if (pTree->getRight() == nullptr)
			{
				//insert here
				pTree->setRight(new BSTNode<from, to>(newEng, newMorse));
			}
			else
			{
				//traverse right subtree
				insert(pTree->getRight(), newEng, newMorse);
			}
		}
	}
}

/*
Overloaded private helper function for printTree
Takes in a pointer to a node for a parameter and returns nothing
Uses in order traversal to traverse the tree and prints the english character and its associated morse string to the screen in ASCII order
*/
template<class from, class to>
void BST<from, to>::printTree(BSTNode<from, to>* pTree) const
{
	if (pTree != nullptr)
	{
		//use in order traversal to print the tree
		printTree(pTree->getLeft());
		cout << "[" << pTree->getEng() << "] -> [" << pTree->getMorse() << "]" << endl; //prints out with the format "[character] -> [morse code]
		printTree(pTree->getRight());
	}
}

template<class from, class to>
void BST<from, to>::printTree() const
{
	printTree(pRoot);
}

/*
chopTree is the helper function for the BST destructor
it uses post-order traversal to delete every node in the tree
*/
template<class from, class to>
void BST<from, to>::chopTree(BSTNode<from, to>* pTree)
{
	if (pTree != nullptr)
	{
		//using post order traversal to delete the tree
		chopTree(pTree->getLeft());
		chopTree(pTree->getRight());
		delete pTree;
	}
}

/*
Overloaded private helper function for search()
Takes in a pointer to a node, the character that the program is searching for, and a reference to the string used in the public function
Kind of uses pre-order traversal to compare the node's data to the searchChar, if it finds the right node, it sets the result string to the morse string and then returns it (breaks)
*/
template<class from, class to>
void BST<from, to>::search(BSTNode<from, to>* pTree, from searchChar, to& result) const //private one
{
	if (pTree != nullptr)
	{
		if (pTree->getEng() == searchChar) //if we find the correct node in the tree
		{
			result = pTree->getMorse(); //sets the result string to the associated morse string
			return; //returns to the public function
		}
		if (searchChar < pTree->getEng()) //if the searchChar is less than the current node's char, which means that it's closer to A
		{
			search(pTree->getLeft(), searchChar, result); //recursively call search to search the left subtree
		}
		if (searchChar > pTree->getEng()); //if the searchChar is greater than the current node's char, which means it's closer to Z
		{
			search(pTree->getRight(), searchChar, result); //search the right subtree
		}
	}
}

template<class from, class to>
to BST<from, to>::search(from searchChar) const
{
	to result = "";
	search(pRoot, toupper(searchChar), result);
	return result;
}

/*
Function to convert a line of english text from a file to morse code which is echoed to the screen
Takes no parameters and returns nothing
Precondition: tree has to be populated
*/
template<class from, class to>
void BST<from, to>::convert()
{
	morseFile.open("convert.txt", ios::in);
	string temp; //storing the line from the file
	while (!morseFile.eof())
	{
		getline(morseFile, temp);
		cout << "Translating '" << temp << "' to morse code." << endl;
		string::iterator translator = temp.begin();
		while (translator != temp.end())
		{
			if (*translator == ' ')
			{
				cout << "   "; //space for when we encounter a space in the file
			}
			else
			{
				cout << this->search(*translator) << " ";
			}
			translator++;
		}
		cout << "\n";
	}
	morseFile.close();
}