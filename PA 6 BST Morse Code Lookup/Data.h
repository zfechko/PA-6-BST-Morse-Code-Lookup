#pragma once
#include "libraries.h"
//will eventually be turning this into a class template
class Data
{
private:
	char english;
	string morse;

public:
	Data(char newEng, string newMorse);
	Data();
	char getEnglish();
	string getMorse();
};

