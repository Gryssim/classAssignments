#include <iostream>

using namespace std;

bool isVowel(char letter);

int main()
{
	char inputChar=' ';
	int vowels = 0;
	
	for (int i = 0; inputChar != '.'; i++)
	{
		cout << "Please input a character: ";
		cin >> inputChar;
		if (isVowel(inputChar))
		{
			vowels++;
		}
	}
	cout << "\nThere are " << vowels << " vowels in your provided characters!" << endl;
	
	return 0;
}


bool isVowel(char letter)
{
	if ((letter == 'a') || (letter == 'e') || (letter == 'i') || (letter == 'o') || (letter == 'u') || (letter == 'y')
		|| (letter == 'A') || (letter == 'E') || (letter == 'I') || (letter == 'O') || (letter == 'U') || (letter == 'Y'))
	{
		return true;
	}

		return false; 

	
}
