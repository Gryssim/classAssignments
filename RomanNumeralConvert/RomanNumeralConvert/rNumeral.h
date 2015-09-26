#ifndef RNUMERAL_H
#define RNUMERAL_H

#include <iostream>
#include <string>

using namespace std;

class romanNumerals
{
public:
	void setRString(string roman = "");

	string getRString() const;

	void romanConvert(string& roman);
	
	void countRNum(string rnum);

	int getRCount() const;

private:
	string romanString;
	int romanCount = 0;
};


#endif