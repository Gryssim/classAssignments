#include <iostream>
#include <fstream>
#include <iostream>

using namespace std;

class playClass1{
public:
	double length, width;
	playClass1();
	playClass1(double l, double w);
	void printIt(ofstream &outFile);
};

class playClass2{
private:
	double length, width;
public:
	void setLength(double l);
	void setWidth(double w);
	double getLength();
	double getWidth();
	void printIt(ofstream &outFile);
	playClass2();
	playClass2(double l, double w);

};

void main(){
	playClass1 a;
	playClass2 b;
	ofstream outFile("playing.out");

	outFile << "Object has w = " << a.width << " l = " << a.length << endl;
	outFile << "Object has w = " << b.getWidth() << " l = " << b.getLength() << endl;

	outFile << endl;

	//Step 3A - Use new constructors with new variables and print.
	outFile << "Step 3A - Use new constructors with new variables and print" << endl << endl;
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

playClass1::playClass1(){
	length = 2.0;
	width = 1.0;
}

playClass1::playClass1(double l, double w){
	length = l;
	width = w;
}

void playClass1::printIt(ofstream &outFile){
	outFile << "the playClass1 object has : length = " << length << " width = " << width << endl;
}

playClass2::playClass2(){
	length = 4.0;
	width = 2.0;
}

playClass2::playClass2(double l, double w){
	length = l;
	width = w;
}

void playClass2::printIt(ofstream &outFile){
	outFile << "the playClass1 object has : length = " << length << " width = " << width << endl;
}


double playClass2::getLength(){
	return length;
}

double playClass2::getWidth(){
	return width;
}

void playClass2::setLength(double l){
	length = l;
}

void playClass2::setWidth(double w){
	width = w;
}