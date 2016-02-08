/*
Douglas Plock
CSCI 113
Random Number Generator
*/

#include <math.h>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAX = 5000;
const double BOUNDARY = 100000;


void main() {
	ofstream outFile1("double.ot");
	ofstream outFile2("struct.ot");
	int i = 0;
	int num = 0;
	double anum = 0.0;

	outFile1.setf(ios::fixed);
	outFile2.setf(ios::fixed);


	while (i < MAX) {
		num = rand();
		anum = pow(num, (1.0 / 3.0)) * pow(-1.0, i) * i - (num + 3.14159265358979);

		if (abs(anum) < BOUNDARY) {
			outFile1 << setprecision(3) << anum << endl;
			outFile2 << setprecision(3) << anum << " " << 50;
			for (int j = 1; j <= 50; j++) outFile2 << " Lucy";
			outFile2 << endl;
			i++;
		}
	}

}