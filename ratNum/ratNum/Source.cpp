/*
Douglas Plock
CSCI 112
RationalNumber
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

#include "ratNum.h"

const int MAXCOMP = 5;


void main(){
	ofstream outFile("output.txt");
	ifstream inFile("input.dat");
	ratNum x, y(2, 5);

	x.printIt(outFile);
	y.printIt(outFile);

	system("pause");

	//STEP 1 - set x to new rational number and multiply for Z.
	outFile << "STEP 1 - Set x to new rational number and multiply" << endl << endl;
	x.setNom(3);
	x.setDenom(5);
	outFile << "X:" << endl;
	x.printIt(outFile);
	outFile << "Y:" << endl;
	y.printIt(outFile);

	ratNum z = x * y;

	outFile << "Z:" << endl;
	z.printIt(outFile);

	//STEP 2 - test divide operator with x and y.
	outFile << "STEP 2 - test divide operator with x and y." << endl << endl;
	z = x / y;

	outFile << "X:" << endl;
	x.printIt(outFile);
	outFile << "Y:" << endl;
	y.printIt(outFile);

	outFile << "Z:" << endl;
	z.printIt(outFile);

	//STEP 3 - test input and output overloaded functions.
	/*outFile << "STEP 3 - test input and output overloaded functions." << endl << endl;
	 inFile >> z;
	z.printIt(outFile);
	outFile << z << endl;
	*/

	//STEP 4 - test addition and subtraction methods.
	outFile << "STEP 4 - test addition and subtraction methods." << endl << endl;
	x.printIt(outFile);
	y.printIt(outFile);
	outFile << x + y << endl;
	outFile << x - y << endl;

	//STEP 5 - change values of x and y and test different denom ratNums.
	outFile << "STEP 5 - change values of x and y and test different denom ratNums." << endl << endl;
	x.setNom(3);
	x.setDenom(12);
	y.setNom(9);
	y.setDenom(23);

	x.printIt(outFile);
	y.printIt(outFile);

	outFile << x + y << endl;
	outFile << x - y << endl << endl;

	//STEP 6 - test reduceIt.
	outFile << "STEP 6 - test reduceIt." << endl << endl;
	z = x + y;
	outFile << z << endl;
	//outFile << z.reduceIt() << endl << endl;
	z = x - y;
	outFile << z << endl;
	//outFile << z.reduceIt() << endl << endl;

	//STEP 7 - test getMin.
	outFile << "STEP 7 - test getMin." << endl << endl;
	int min;
	z = x + y;
	min = z.getMin();
	outFile << "min -should- be 59." << endl << "Min is: " << min << endl << endl;

	//STEP 8 - Read in input file of rational pairs and output each pair.
	outFile << "STEP 8 - Read in input file of rational pairs and output each pair." << endl << endl;

	ratNum a, b;
	for (int i = 0; i < 5; i++){
		inFile >> a >> b;
		outFile << "Rational Number a: " << a << setw(30) << "Rational Number b: " << b << endl << endl;
		outFile << "a + b:   " << a + b << endl;
		outFile << "a - b:   " << a - b << endl;
		outFile << "a * b:   " << a * b << endl;
		outFile << "a / b:   " << a / b << endl;
	}

}
