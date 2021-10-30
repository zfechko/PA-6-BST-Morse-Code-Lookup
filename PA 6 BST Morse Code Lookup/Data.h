#pragma once
#include "libraries.h"

template<class from, class to>
class Data
{
private:
	from english;
	to morse;

public:
	Data(from newEng, to newMorse);
	Data();
	from getEnglish();
	to getMorse();
};


template<class from, class to>
Data<from, to>::Data(from newEng, to newMorse)
{
	this->english = newEng;
	this->morse = newMorse;
}

template<class from, class to>
from Data<from, to>::getEnglish()
{
	return english;
}

template<class from, class to>
to Data<from, to>::getMorse()
{
	return morse;
}
