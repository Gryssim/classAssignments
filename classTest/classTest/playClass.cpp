#include "playClass.h"

using namespace std;

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