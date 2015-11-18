#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

struct structTest{
	int id;
	string name;
};

struct queueStruct{
	int majors;
	string fieldStudy;
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

	outFile << "i : " << i.id << " " << i.name << " "  << " j : " << j.id << " " << j.name << endl;
	swapIt(i, j);
	outFile << "i : " << i.id << " " << i.name << " " << " j : " << j.id << " " << j.name << endl << endl;

	// Step 2A - Create a vector object and store data from file.
	outFile << "Step 2A - Create a vector object and store data from file." << endl;
	ifstream inFile("vectorInput.dat");
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

	// Step 3A - Create a queue container and read in data from file.
	outFile << "Step 3A - Create a queue container and read in data from file." << endl;
	ifstream inf("queueInput.dat");
	queue<queueStruct> q;
	queueStruct tempStruct;

	while (!inf.eof()){
		inf >> tempStruct.majors >> tempStruct.fieldStudy;
		q.push(tempStruct);
	}

	outFile << endl;

	// Step 3B - Output the number of elements in q.
	outFile << "Step 3B - Output the number of elements in q." << endl;

	outFile << "q contains " << q.size() << " elements." << endl << endl;

	// Step 3C - serve each element in the queue.
	outFile << "Step 3C - serve each element in the queue." << endl;

	while (!q.empty()){
		tempStruct = q.front();
		outFile << left << setw(14) << tempStruct.fieldStudy << tempStruct.majors << endl;
		q.pop();
	}

	
}