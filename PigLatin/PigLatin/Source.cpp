
#include <iostream> 
#include <string>
#include <string.h>

using namespace std;

bool isPunc(char ch);
bool isVowel(char ch);
string rotate(string pStr);
string pigLatinString(string pStr);

int main()
{
	string str;
	string::size_type len;
	len = str.length();

	cout << "Please enter a sentence: ";
	cout << endl;

	do
	{
		cin >> str;
		cout << pigLatinString(str) << " ";
		cin.clear();
		
	} while (str.length()==0);

}

bool isVowel(char ch)
{
	if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'y'
		|| ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' || ch == 'Y')
		return true;
	else
		return false;
}

bool isPunc(char ch)
{
	if ((ch == '!') || (ch == '.') || (ch == ',') || (ch == '?') || (ch == ';') || (ch == ':'))
		return true;
	else return false;
}

string rotate(string pStr)
{
	string::size_type len = pStr.length();

	string rStr;

	rStr = pStr.substr(1, len - 1) + pStr[0];

	return rStr;
}

string pigLatinString(string pStr)
{
	string::size_type len;
	len = pStr.length();
	bool foundVowel;
	string::size_type counter;
	int i;
	string fStr;

	if (isVowel(pStr[0]))
		pStr = pStr + "-way";
	else
	{
		pStr = pStr + '-';
		pStr = rotate(pStr);

		len = pStr.length();
		foundVowel = false;

		for (counter = 1; counter < len - 1; counter++)
			if (isVowel(pStr[0]))
			{
				foundVowel = true;
				break;
			}
			else
				pStr = rotate(pStr);

		if (!foundVowel)
		{
			pStr = pStr.substr(1, len) + "-way";
		}
		else
			pStr = pStr + "ay";
	}

	for (int i = 0; i < len; i++)
	
		if (isPunc(pStr[i]))
		{
			pStr = pStr.substr(0, i) + pStr.substr(i+1)  + pStr[i];
			break;
		}
	
	return pStr;
}
