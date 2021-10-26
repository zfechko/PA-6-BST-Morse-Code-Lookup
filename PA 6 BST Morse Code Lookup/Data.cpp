#include "Data.h"

Data::Data(char newEng, string newMorse)
{
	this->english = newEng;
	this->morse = newMorse;
}

Data::Data()
{
	//implicit
}

char Data::getEnglish()
{
	return this->english;
}

string Data::getMorse()
{
	return this->morse;
}
