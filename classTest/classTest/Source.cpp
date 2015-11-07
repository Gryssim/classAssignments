/*
Douglas Plock
CSCI 112
playClass
*/

#include <iostream>
#include <fstream>

using namespace std;

#include "playClass.h"

void main(){
	playClass1 a;
	playClass2 b;
	ofstream outFile("playing.out");

	outFile << "Object has w = " << a.width << " l = " << a.length << endl;
	outFile << "Object has w = " << b.getWidth() << " l = " << b.getLength() << endl;

	outFile << endl;

	//Step 3A - Use new constructors to create objects x and y with parameters then print.
	outFile << "Step 3A - Use new constructors to create objects x and y with parameters then print." << endl << endl;
	playClass1 x(6.235, 4.375);
	playClass2 y(12.725, 10.000);
	x.printIt(outFile);
	y.printIt(outFile);

	outFile << endl;

	//Step 3B - Create new double var Area and print for x and y.
	outFile << "Step 3B - Create new double var Area and print for 'x' and 'y'." << endl << endl;
	double area;
	area = x.length * x.width;
	outFile << "'x' has area : " << area << endl;
	area = y.getLength() * y.getWidth();
	outFile << "'y' has area : " << area << endl;

	outFile << endl;

	//Step 3C - Change the dimensons of a and print the area.
	outFile << "Step 3C- Change the dimensions of 'a' and print the area." << endl << endl;
	a.length = 16.503;
	a.width = 3.333;
	area = a.length * a.width;
	outFile << "'a' has area : " << area << endl;

	outFile << endl;

	//Step 3D - Change the dimensons of b and print the area.
	outFile << "Step3D - Change the dimensons of 'b' and print the area." << endl << endl;
	b.setLength(11.125);
	b.setWidth(9.507);
	area = b.getLength() * b.getWidth();
	outFile << "'b' has area : " << area << endl;
}
