#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

struct queueStruct{
	int majors;
	string fieldStudy;
};


void main(){
	ofstream outFile("output.out");

	// Step 3A - Create a queue container and read in data from file.
	outFile << "Step 3A - Create a queue container and read in data from file." << endl;
	ifstream inf("input.dat");
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