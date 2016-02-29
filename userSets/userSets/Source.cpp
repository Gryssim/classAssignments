#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int maxSet = 'Z' + 1;

class userSet{
public:
	bool set[maxSet];

	userSet();
	userSet(int i, string name);
	userSet(string file, string name);
	void fillSet();
	void setName(string name);
	string getName();
	int getLength();

private:
	string name = "";


};

// Default constructor sets all values to false, empty set.

userSet::userSet(){
	for (int i = 0; i < maxSet; i++) set[i] = false;
}

// variable constructor. If param > 0, set vowels true. Else full set.

userSet::userSet(int i, string name) {
	this->name = name;
	for (int i = 'A'; i < maxSet; i++) set[i] = false;

	if (i > 0) {
		set['A'] = true;
		set['E'] = true;
		set['I'] = true;
		set['O'] = true;
		set['U'] = true;
	}
	else
		for (int i = 0; i < maxSet; i++) set[i] = false;

}

// Constructor with file stream

userSet::userSet(string file, string name) {
	this->name = name;
	
	for (int i = 'A'; i < maxSet; i++) set[i] = false;
	
	ifstream inFile(file);
	char ch;
	while (!inFile.eof()) {
		inFile >> ch;
		set[ch] = true;
	}

}


void userSet::fillSet() {
	for (int i = 'A'; i < maxSet; i++) set[i] = true;
}

void userSet::setName(string name)
{
	this->name = name;
}

string userSet::getName()
{
	return this->name;
}

int userSet::getLength() {
	int answer = 0;

	for (int i = 'A'; i < maxSet; i++) {
		if (set[i]) answer++;
	}

	return answer;
}

void printSet(ofstream &outFile, userSet set) {
	outFile << "The " + set.getName() +" set includes:" << endl;
	
	for (int j = 'A'; j < maxSet; j++) {
		if (set.set[j] == true) {
			outFile << (char)j << " ";
		}
		else
			outFile << "  ";
	}
	outFile << endl << endl;
}

userSet setUnion(userSet x, userSet y) {
	userSet answer;
	string newSetName = "Union (" +  x.getName() + " + " + y.getName() + ")";
	
	answer.setName(newSetName);

	for (int i = 'A'; i < maxSet; i++) {
		if (x.set[i] == true || y.set[i] == true)
			answer.set[i] = true;
	}

	return answer;
}

userSet setInt(userSet x, userSet y) {
	userSet answer;
	string newSetName = "Intercept (" + x.getName() + " U " + y.getName() + ")";

	answer.setName(newSetName);

	for (int i = 'A'; i < maxSet; i++) {
		if (x.set[i] == true && y.set[i] == true)
			answer.set[i] = true;
	}

	return answer;
}
        
userSet setDiff(userSet x, userSet y) {
	userSet answer;
	string newSetName = "Difference (" + x.getName() + " \\ " + y.getName() + ")";

	answer.setName(newSetName);

	for (int i = 'A'; i < maxSet; i++) {
		if (x.set[i] == true)
			answer.set[i] = true;
		if (x.set[i] == true && y.set[i] == true)
			answer.set[i] = false;
	}

	return answer;
}

void isEqual(ofstream &outFile, userSet x, userSet y) {
	bool equal = true;
	int i = 'A';

	while (i < maxSet && equal) {
		if (x.set[i] == y.set[i])
			equal = true;
		else
			equal = false;
		i++;
	}
	if (equal)
		outFile << "The sets " + x.getName() + " and " + y.getName() + " are equal." << endl << endl;
	else
		outFile << "The sets " + x.getName() + " and " + y.getName() + " are not equal." << endl << endl;
}

void isSubset(ofstream &outFile, userSet subOf, userSet set) {
	bool subset = true;
	int i = 'A';

	while (i < maxSet && subset) {
		if (subOf.set[i])
			if (set.set[i])
				subset = true;
			else
				subset = false;
		i++;
	}

	if (subset)
		outFile << subOf.getName() + " is a subset of " + set.getName() << endl << endl;
	else
		outFile << subOf.getName() + " is not a subset of " + set.getName() << endl << endl;

}


void main() {
	userSet universalSet(0, "Universal");
	userSet vowelSet(1, "Vowel");
	userSet nameSet("name.dat", "Name");
	
	ofstream outFile("output.ot");

	universalSet.fillSet();

	printSet(outFile, universalSet);
	printSet(outFile, vowelSet);
	printSet(outFile, nameSet);
	printSet(outFile, setUnion(vowelSet, nameSet));
	printSet(outFile, setInt(nameSet, vowelSet));
	printSet(outFile, setDiff(vowelSet, nameSet));
	printSet(outFile, setDiff(nameSet, vowelSet));

	isEqual(outFile, universalSet, nameSet);
	isEqual(outFile, nameSet, nameSet);

	isSubset(outFile, vowelSet, universalSet);
	isSubset(outFile, vowelSet, nameSet);


}
