#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

void main(){
	ofstream outFile("output.out");

	// Step 2A - Create a vector object and store data from file.
	outFile << "Step 2A - Create a vector object and store data from file." << endl;
	ifstream inFile("input.dat");
	vector<int> vect;
	int tempInt;

	while (!inFile.eof()){

		inFile >> tempInt;
		vect.push_back(tempInt);
	}

	outFile << endl;

	// Step 2B - output the vector.
	outFile << "Step 2B - output the vector." << endl;
	outFile << "The elements in vector vect are: ";
	for (int i = 0; i < 10; i++){
		int j = vect.at(i);
		outFile << j << " ";
	}
	outFile << endl << endl;

	// Step 2C - Sort using an STL algorithm and output the sorted vector.
	outFile << "Step 2C - Sort using an STL algorithm and output the sorted vector." << endl;
	sort(vect.begin(), vect.end());

	outFile << "The elements in vector vect are: ";
	for (int i = 0; i < 10; i++){
		int j = vect.at(i);
		outFile << j << " ";
	}
	outFile << endl << endl;
}