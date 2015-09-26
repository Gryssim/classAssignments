#include <iostream>
#include <string>
#include "rNumeral.h"

using namespace std;

int main()
{
	string rom, rom1, rom2;
	romanNumerals roman1, roman2, roman3;

	rom = "mcxiv";
	rom1 = "ccclix";
	rom2 = "mdclxvi";

	roman1.romanConvert(rom);

	cout << rom << endl;

	roman1.setRString(rom);

	roman1.countRNum(roman1.getRString());

	cout << roman1.getRCount() << endl;

	roman2.romanConvert(rom1);

	cout << rom1 << endl;

	roman2.setRString(rom1);

	roman2.countRNum(roman2.getRString());

	cout << roman2.getRCount() << endl;

	roman3.romanConvert(rom2);

	cout << rom2 << endl;

	roman3.setRString(rom2);

	roman3.countRNum(roman3.getRString());

	cout << roman3.getRCount() << endl;


}