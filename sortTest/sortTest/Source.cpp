/*
Douglas Plock
CS 112
Sort Test
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>

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
				numCmp++;
				if (a[j] < a[small]){
					small = j;
				}
			}
			if (k != small){
				swapIt(a[k], a[small]);
				numMove += 3;
			}
		}
	}
}

void insertionSort(double a[]){
	int j, k;
	double save;
	for (k = MAXSIZE - 2; k >= 0; k--){
		j = k + 1;
		save = a[k];
		numMove++;
		a[MAXSIZE] = save;
		numMove++;
		numCmp++;
		while (save > a[j]){
			a[j - 1] = a[j];
			j++;
			numCmp++;
			numMove++;
		}
		numMove++;
		a[j - 1] = save;
	}
}

void quickSort(double a[], int left, int right){

}

void improvedBubbleSort(double a[]){
	bool sorted;
	int i, j;
	sorted = false;
	i = 0;
	while (!sorted){
		sorted = true;
		for (j = 0; j < MAXSIZE - 1; j++){
			numCmp++;
			if (a[j] > a[j + 1]){
				numMove += 3;
				sorted = false;
				swapIt(a[j], a[j + 1]);
			}
			i++;
		}
	}
}

void printIt(ofstream &outFile, string name, double a[], double ms){
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
		<< 1.0 * numMove / MAXSIZE << endl << endl;

	outFile << left << "Duration: " << ms << " miliseconds" << endl << endl << endl;
}

void main(){
	int i;
	double a[MAXSIZE+1];
	clock_t start, stop;
	double ms;

	string name;
	ofstream outFile("output.txt");

	
	for (i = 0; i < numSorts; i++){
		readIt(a);
		ms = 0;
		numCmp = 0;
		numMove = 0;
		switch (i){
		case (0) :
			start = clock();
			bubbleSort(a);
			stop = clock();
			name = "Bubble Sort";
			break;
		case(1) :
			start = clock();
			selectSort(a);
			stop = clock();
			name = "Selection Sort";
			break;
		case(2) :
			start = clock();
			insertionSort(a);
			stop = clock();
			name = "Insertion Sort";
			break;
		case(3) :
			start = clock();
			quickSort(a, 0, MAXSIZE-1);
			stop = clock();
			break;
			name = "Quick Sort";
		case(4) :
			start = clock();
			improvedBubbleSort(a);
			stop = clock();
			name = "Improved Bubble Sort";
			break;					
		}
		ms = (stop - start) * 1000 / CLOCKS_PER_SEC;
		printIt(outFile, name, a, ms);

	}
}