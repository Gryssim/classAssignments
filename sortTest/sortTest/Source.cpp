/*
Douglas Plock
CS 112
Sort Test
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int MAXSIZE = 10000;
const int numSorts = 5;

int numMove = 0;
int numCmp = 0;



void readIt(double a[]){
	ifstream inFile("input.dat");
	int i;

	for (i = 0; i < MAXSIZE; i++){
		inFile >> a[i];
	}
}

void swapIt(double &a, double &b){
	double temp;
	temp = b;
	b = a;
	a = temp;
}

void bubbleSort(double a[]){
	int i, j;
	for (j = 0; j < MAXSIZE - 1; j++)
		for (i = 0; i < MAXSIZE - 1; i++){
			numCmp++;
			if (a[i] > a[i + 1]){
				swapIt(a[i], a[i + 1]);
				numMove += 3;
			}
		}

}

void selectSort(double a[]){
	int j, k, small;

	if (MAXSIZE > 1){
		for (k = 0; k <= MAXSIZE - 2; k++){
			small = k;
			for (j = k + 1; j <= MAXSIZE - 1; j++){
				if (a[j] < a[small]){
					small = j;
					numCmp++;
				}
				if (k != small){
					swapIt(a[k], a[small]);
					numMove += 3;
				}
			}
		}
	}
}

void insertionSort(double a[]){

}

void quickSort(double a[], int left, int right){

}

void improvedBubbleSort(double a[]){
	bool sorted;
	int i;
	sorted = false;
	while (!sorted){
		sorted = true;
		for (i = 0; i < MAXSIZE - 1; i++){
			numCmp++;
			if (a[i] > a[i + 1]){
				numMove += 3;
				sorted = false;
				swapIt(a[i], a[i + 1]);
			}
		}
	}
}

void printIt(ofstream &outFile, string name, double a[]){
	int i;
	int counter = 0;
	int numPerRow = 5;
	int incr = MAXSIZE / 10;

	outFile << name << "   " << "N = " << MAXSIZE << endl;

	for (i = 0; i < MAXSIZE; i += incr){
		outFile << setprecision(3) << fixed << right << setw(15) << a[i];
		counter++;
		if (counter >= numPerRow){
			outFile << endl;
			counter = 0;
		}
	}

	outFile << endl;
	outFile << left << setw(28) << "Number of comparisons: " << numCmp
		<< " " << "Number of copies: " << numMove << endl << endl;

	outFile << left << setw(28) << "Relative # of comparisons: "
		<< 1.0 * numCmp / MAXSIZE << " " << "Relative # of copies: "
		<< 1.0 * numMove / MAXSIZE << endl << endl << endl;
}

void main(){
	int i;
	double a[MAXSIZE];

	string name;
	ofstream outFile("output.txt");

	
	for (i = 0; i < numSorts; i++){
		readIt(a);
		numCmp = 0;
		numMove = 0;
		switch (i){
		case (0) : 
			bubbleSort(a);
			name = "Bubble Sort";
			break;
		case(1) :
			selectSort(a);
			name = "Selection Sort";
			break;
		case(2) :
			insertionSort(a);
			name = "Insertion Sort";
			break;
		case(3) :
			quickSort(a, 0, MAXSIZE);
			name = "Quick Sort";
			break;
		case(4) :
			improvedBubbleSort(a);
			name = "Improved Bubble Sort";
			break;					
		}
		printIt(outFile, name, a);

	}
}