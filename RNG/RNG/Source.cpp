/*
Douglas Plock
CSCI 112
Random Number Generator
*/

#include <math.h>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAX = 10000;
const double BOUNDARY = 100000;


void main(){
	ofstream outFile("output.txt");
	int i = 0;
	int num = 0;
	double anum = 0.0;

	while (i < MAX){
		num = rand();
		anum = pow (num, (1.0/3.0)) * pow(-1.0, i) * i - (num + 3.14159265358979);

		if (abs(anum) < BOUNDARY){
			outFile << fixed << setprecision(3) <<  anum << endl;
			i++;
		}
	}

}