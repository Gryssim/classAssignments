#include <iostream>
#include <string>
#include "rNumeral.h"

using namespace std;

void romanNumerals::setRString(string roman)
{
	romanString = roman;
}

string romanNumerals::getRString() const
{
	return romanString;
}

void romanNumerals::romanConvert(string& roman)
{
	for (int i = 0; i < roman.length(); i++)
		roman[i] = toupper(roman[i]);
}

void romanNumerals::countRNum(string rnum)
{
	for (int i = 0; i < rnum.length(); i++)
		if (rnum[i] == 'I')
		{
			if (rnum[i + 1] == 'V')
			{
				romanCount = romanCount + 4;
				i++;
			}
			else if (rnum[i + 1] == 'X')
			{
				romanCount = romanCount + 9;
				i++;
			}
			else
				romanCount = romanCount + 1;
		}
		else if (rnum[i] == 'V')
		{
			if (rnum[i + 1] == 'I')
			{
				romanCount = romanCount + 6;
				i++;
			}
			else
				romanCount = romanCount + 5;
		}
		else if (rnum[i] == 'X')
		{
			if (rnum[i + 1] == 'I')
			{
				if (rnum[i + 2] == 'V')
				{
					romanCount = romanCount + 10;
				}
				else
				{
					romanCount = romanCount + 11;
					i++;
				}
			}
			else if (rnum[i + 1] == 'L')
			{
				romanCount = romanCount + 40;
				i++;
			}
			else if (rnum[i + 1] == 'C')
			{
				romanCount = romanCount + 90;
				i++;
			}
			else
				romanCount = romanCount + 10;
		}
		else if (rnum[i] == 'L')
		{
			romanCount = romanCount + 50;
		}
		else if (rnum[i] == 'C')
		{
			if (rnum[i + 1] == 'M')
			{
				romanCount = romanCount + 900;
				i++;
			}
			else
				romanCount = romanCount + 100;
		}
		else if (rnum[i] == 'D')
		{
			romanCount = romanCount + 500;
		}
		else if (rnum[i] == 'M')
		{
			romanCount = romanCount + 1000;
		}
		else
			cout << "No valid Roman Numeral characters detected." << endl;
		
			
}

int romanNumerals::getRCount() const
{
	return romanCount;
}
