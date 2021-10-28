#include "BST.h"
BST::BST()
{
	pRoot = nullptr;
	this->morseFile.open("MorseTable.txt", ios::in);
	char tempChar;
	string tempString = "";
	Data* insertionData;

	while (!morseFile.eof())
	{
		getline(morseFile, tempString); //getting the line with the char/letter in it
		tempChar = tempString.c_str()[0]; //because strings work like an array, we extract the 0th index and set it to the char
		getline(morseFile, tempString);
		insertionData = new Data(tempChar, tempString); //create a new data object with the character and string
		insert(this->pRoot, *insertionData); //and then insert it into the tree
	}
	morseFile.close();
}

BST::~BST()
{
	chopTree(pRoot);
}

void BST::chopTree(BSTNode* pNode)
{
	if (pNode != nullptr)
	{
		//using post order traversal to delete the tree
		chopTree(pNode->getLeft());
		chopTree(pNode->getRight());
		delete pNode;
	}
}

bool BST::isEmpty()
{
	return pRoot == nullptr;
}

void BST::insert(BSTNode* pTree, Data newData)
{
	if (pTree == nullptr) //if the tree is empty
	{
		pRoot = new BSTNode(newData);
	}
	else
	{
		if (pTree->getData().getEnglish() > newData.getEnglish())
		{
			//we need to go to the left
			if (pTree->getLeft() == nullptr)
			{
				//insert here
				pTree->setLeft(new BSTNode(newData));
			}
			else
			{
				insert(pTree->getLeft(), newData);
			}
		}
		if (pTree->getData().getEnglish() < newData.getEnglish())
		{
			//we need to go to the right
			if (pTree->getRight() == nullptr)
			{
				//insert here
				pTree->setRight(new BSTNode(newData));
			}
			else
			{
				//traverse right subtree
				insert(pTree->getRight(), newData);
			}
		}
	}
	
}

void BST::printTree() const
{
	printTree(pRoot);
}

void BST::printTree(BSTNode* pTree) const
{
	if (pTree != nullptr)
	{
		//we're going to use in order traversal to print the tree with the format [A] = [.-]
		printTree(pTree->getLeft());
		cout << "[" << pTree->getData().getEnglish() << "] = [" << pTree->getData().getMorse() << "]" << endl;
		printTree(pTree->getRight());
	}
}

string BST::search(BSTNode* pTree, char searchChar, string& result) const //private function
{
	if (pTree != nullptr)
	{
		//use in order traversal to find the target character
		search(pTree->getLeft(), searchChar, result);
		if (pTree->getData().getEnglish() == searchChar)
		{
			result = pTree->getData().getMorse();
			return result;
		}
		search(pTree->getRight(), searchChar, result);
	}
}

string BST::search(char searchChar) const
{
	string result = "";
	search(this->pRoot, toupper(searchChar), result);
	return result;
}

void BST::testSearch()
{
	char testChar;
	string testMorseString;
	cout << "Enter a character to search for" << endl;
	cin >> testChar;
	cout << "The morse equivalent for " << testChar << "is " << this->search(testChar) << endl;
}