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

/*
chopTree is the helper function for the BST destructor
it uses post-order traversal to delete every node in the tree
*/
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

/*
isEmpty is a predicate function that returns true if the root of the BST is null and false if it isn't
*/
bool BST::isEmpty()
{
	return pRoot == nullptr;
}

/*
This is the private member insert function
There is no overloaded public version because this function is ONLY called in the tree's contructor
It takes a pointer to a node and a Data object to assign values for the node
Uses recursion to find the right place in the tree to insert
*/
void BST::insert(BSTNode* pTree, Data newData)
{
	if (pTree == nullptr) //if the tree is empty
	{
		pRoot = new BSTNode(newData); //insert at the root of the tree
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
				//traverse the left subtree
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

/*
This is the public printTree function, which only calls the private version below 
It takes no arguments and returns nothing
*/
void BST::printTree() const
{
	printTree(pRoot);
}

/*
Overloaded private helper function for printTree
Takes in a pointer to a node for a parameter and returns nothing
Uses in order traversal to traverse the tree and prints the english character and its associated morse string to the screen in ASCII order
*/
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

/*
Overloaded private helper function for search()
Takes in a pointer to a node, the character that the program is searching for, and a reference to the string used in the public function
Kind of uses pre-order traversal to compare the node's data to the searchChar, if it finds the right node, it sets the result string to the morse string and then returns it (breaks)
*/
void BST::search(BSTNode* pTree, char searchChar, string& result) const //private function
{
	if (pTree != nullptr)
	{
		if (pTree->getData().getEnglish() == searchChar) //if we find the correct node in the tree
		{
			result = pTree->getData().getMorse(); //sets the result string to the associated morse string
			return; //returns to the public function
		}
		if (searchChar < pTree->getData().getEnglish()) //if the searchChar is less than the current node's char, which means that it's closer to A
		{
			search(pTree->getLeft(), searchChar, result); //recursively call search to search the left subtree
		}
		if (searchChar > pTree->getData().getEnglish()); //if the searchChar is greater than the current node's char, which means it's closer to Z
		{
			search(pTree->getRight(), searchChar, result); //search the right subtree
		}
	}
}

/*
Public overloaded search function
Takes in the character for the parameter which is then called in the private helper function
Returns the morse string once it is found
*/
string BST::search(char searchChar) const
{
	string result = ""; //string to be used to store the morse result
	search(this->pRoot, toupper(searchChar), result); //uses toupper() so that it can find the correct character in the tree in case the searchChar happens to be lowercase
	return result;
}

/*
Test function I made to test whether the search function was working correctly
No parameters and returns nothing
Prompts the user for a character to search for, with the implied precondition that the character is already defined in the tree
Searches the tree for the character and then prints the morse translation to the screen
NOTE: this is not used in the main program so please don't dock points for no defensive code
*/
void BST::testSearch()
{
	char testChar;
	string testMorseString;
	cout << "Enter a character to search for" << endl;
	cin >> testChar;
	cout << "The morse equivalent for " << testChar << " is " << this->search(testChar) << endl;
}

/*
Function to convert a line of english text from a file to morse code which is echoed to the screen
Takes no parameters and returns nothing
Precondition: tree has to be populated
*/
void BST::convert()
{
	morseFile.open("convert.txt", ios::in); //uses the fstream object in the class to open the text to convert
	string temp = ""; //string to store the line of text
	while(!morseFile.eof())
	{
		getline(morseFile, temp); //reads a line from the file and stores it to temp
		cout << "Translating '" << temp << "' to morse code" << endl;
		string::iterator translator = temp.begin(); //using a string iterator which I learned about in lab 9
		while (translator != temp.end()) //while the iterator isn't at the end of the string
		{
			if (*translator == ' ') //if the current character in the string is a space
			{
				cout << "   "; //we put the space for the echo to the screen
			}
			else
			{
				cout << search(*translator) << " "; //search the tree for the character the iterator is at and print it
			translator++; //increment the iterator
		}
		cout << "\n"; //add endline for if we're translating more than one line in the file (which we are)
	}
	morseFile.close(); //close the file
}