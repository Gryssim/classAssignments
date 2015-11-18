/*
Douglas Plock
CSCI 112
Class Assignment 2
*/

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct structTest{
	int id;
	string name;
};

template <class type>
type getMin(type a, type b){
	type ans;
	if (a < b)
		ans = a;
	else
		ans = b;

	return ans;
}

template <class type>
void swapIt(type &a, type &b){
	type temp;
	temp = b;
	b = a;
	a = temp;
}


void main(){

	ofstream outFile("output.out");


	//Step 1A - set Integer and String values to test getMin;
	outFile << "Step 1A - set Integer and String values to test getMin" << endl;
	int x = 2, y = 4;
	string a = "Henry", b = "James";

	outFile << "x : " << x << " y : " << y << endl;
	outFile << "The smaller of the two is " << getMin(x, y) << endl << endl;

	outFile << "a : " << a << " b : " << b << endl;
	outFile << "The smaller of the two is " << getMin(a, b) << endl << endl;

	//Step 1B - Create instance of struct and test swap template on all values.
	outFile << "Step 1B - Create instance of struct and test swap template on all values." << endl;

	structTest i = { 1234, "Luke Skywalker" }, j = { 2345, "Han Solo" };

	outFile << "x : " << x << " y : " << y << endl;
	swapIt(x, y);
	outFile << "x : " << x << " y : " << y << endl;

	outFile << "a : " << a << " b : " << b << endl;
	swapIt(a, b);
	outFile << "a : " << a << " b : " << b << endl;

	outFile << "i : " << i.id << " " << i.name << " " << " j : " << j.id << " " << j.name << endl;
	swapIt(i, j);
	outFile << "i : " << i.id << " " << i.name << " " << " j : " << j.id << " " << j.name << endl << endl;
}