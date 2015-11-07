#include <iostream>
#include <fstream>

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