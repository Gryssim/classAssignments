/*
Douglas Plock
CSCI 113
SortTest
*/

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream> 
#include <time.h>

using namespace std;

struct testStruct
{
	double crn;
	int numS;
	string student[50];
};

const int numToSeeDouble = 100;
const int numToSeeStruct = 5;
const int maxNum = 5001;

void readItDoubles(double a[]) {
	ifstream inFileDoubles("double.dat");

	for (int i = 0; i < maxNum - 1; i++)
		inFileDoubles >> a[i];
}

void readItStructs(testStruct a[]) {
	ifstream inFileStructs("struct.dat");
	int i;

	for (i = 0; i < maxNum - 1; i++) {
		if (i % 50 == 0) cout << " * ";
		inFileStructs >> a[i].crn >> a[i].numS;
		for (int j = 0; j < 50; j++)
			inFileStructs >> a[i].student[j];
	}
}

void swapItDouble(double &a, double &b) {
	double temp;
	temp = b;
	b = a;
	a = temp;
	
}

void swapItStructs(testStruct &a, testStruct &b) {
	testStruct temp;
	temp = b;
	b = a;
	a = temp;
}

void bubbleSortDoubles(double a[]) {
	for (int j = 0; j < maxNum - 1; j++) {
		for (int i = 0; i < maxNum - j - 1; i++) {
			if (a[i] > a[i + 1]) swapItDouble(a[i], a[i + 1]);
		}
	}
}

void bubbleSortStructs(testStruct a[]) {
	for (int j = 0; j < maxNum - 1; j++) {
		if (j % 50 == 0) cout << "[]";
		for (int i = 0; i < maxNum - j - 1; i++) {
			if (a[i].crn > a[i + 1].crn) swapItStructs(a[i], a[i + 1]);;				
		}
	}
}

void selectSortDoubles(double a[]) {
	int j, k, small;

	if (maxNum > 1) {
		for (k = 0; k <= maxNum - 2; k++) {
			small = k;
			for (j = k + 1; j <= maxNum - 1; j++) {
				if (a[j] < a[small]) small = j;
			}
			if (k != small) swapItDouble(a[k], a[small]);
		}
	}
}

void selectSortStructs(testStruct a[]) {
	cout << "Select";
	int j, k, small;

	if (maxNum > 1){
		for (k = 0; k < maxNum - 2; k++) {
			if (k % 50 == 0) cout << "{}";
			small = k;
			for (j = k + 1; j < maxNum; j++) {
				if (a[j].crn < a[small].crn) small = j;
			}
			if (k != small) swapItStructs(a[k], a[small]);
		}
	}
}

void quickSortDoubles(int left, int right, double a[]) {
	int j, k;
	
	if (left < right) {
		j = left;
		k = right + 1;

		do {
			do {
				j++;
			} while (j <= k && a[j] < a[left]);
			do {
				k--;
			} while (k >= left && a[k] > a[left]);
			if (j < k) swapItDouble(a[j], a[k]);
		} while (j < k);
		
		swapItDouble(a[left], a[k]);

		quickSortDoubles(left, k - 1, a);
		quickSortDoubles(k + 1, right, a);
	}
}

void quickSortStructs(int left, int right, testStruct a[]) {
	int j, k;

	if (left < right) {
		j = left;
		k = right + 1;

		do {
			do {
				j++;
			} while (j <= k && a[j].crn < a[left].crn);
			do {
				k--;
			} while (k >= left && a[k].crn > a[left].crn);
			if (j < k) swapItStructs(a[j], a[k]);
		} while (j < k);

		swapItStructs(a[left], a[k]);

		quickSortStructs(left, k - 1, a);
		quickSortStructs(k + 1, right, a);
	}
}

void printItDouble(ofstream &outFile, double a[], string sortName, time_t time) {
	int lineCount = 0;
	
	outFile << "Sorted double array output for: " << sortName << endl;
	for (int i = 0; i < maxNum - 1; i += 500) {
		if (lineCount < 5) {
			outFile << setw(15) << a[i] << " ";
			lineCount++;
		}
		else {
			outFile << setw(15) << endl << a[i] << " ";
			lineCount = 0;
		}
	}
	outFile << endl << "Timing: " << 1.0 * time / CLOCKS_PER_SEC << endl << endl;

}

void printItStructs(ofstream &outFile, testStruct a[], string sortName, time_t time) {
	int lineCount = 0;

	outFile << "Sorted heavy structure array output for: " << sortName << endl;
	for (int i = 0; i < maxNum - 1; i += 500) {
		if (lineCount < 5) {
			outFile << setw(15) << a[i].crn << " ";
			lineCount++;
		}
		else {
			outFile << setw(15) << endl << a[i].crn << " ";
			lineCount = 0;
		}
	}
	outFile << endl << "Timing: " << 1.0 * time / CLOCKS_PER_SEC << endl << endl;

}

void initItDouble(double a[]) {
	for (int i = 0; i < maxNum; i++) {
		a[i] = 0;
	}
}

void initItStructure(testStruct a[]) {
	for (int i = 0; i < maxNum; i++) {
		a[i].crn = 0;
		a[i].numS = -1;
		for (int j = 0; j < 50; j++) a[i].student[j] = "NA";
	}
}

void main() {
	int numSorts = 3;
	int quickSortLeft = 0;
	double testDouble[maxNum];
	ofstream outFile("output.ot");
	testStruct *heavyStruct;
	heavyStruct = new testStruct[maxNum];
	string sortName = "";
	
	outFile.setf(ios::fixed);
	outFile.precision(3);

	time_t start, finish, timeDiff, timeAverage;

	initItDouble(testDouble);
	initItStructure(heavyStruct);

	for (int i = 1; i <= numSorts; i++) {
		start = clock();
		for (int j = 1; j <= numToSeeDouble; j++) {
			readItDoubles(testDouble);
			switch (i) {
			case 1:
				bubbleSortDoubles(testDouble);
				sortName = "Bubble Sort";
				break;
			case 2:
				selectSortDoubles(testDouble);
				sortName = "Select Sort";
				break;
			case 3:
				quickSortDoubles(quickSortLeft, maxNum - 1, testDouble);
				sortName = "Quick Sort";
				break;
			}
			
			finish = clock();
			timeDiff = finish - start;
			timeAverage = timeDiff / numToSeeDouble;


		}
		printItDouble(outFile, testDouble, sortName, timeAverage);
	}

	for (int i = 1; i <= numSorts; i++) {
		start = clock();
		for (int j = 1; j <= numToSeeStruct; j++) {
			cout << " - ";
			readItStructs(heavyStruct);
			switch (i) {
			case 1:
				bubbleSortStructs(heavyStruct);
				sortName = "Bubble Sort";
				break;
			case 2:
				selectSortStructs(heavyStruct);
				sortName = "Select Sort";
				break;
			case 3:
				quickSortStructs(quickSortLeft, maxNum - 1, heavyStruct);
				sortName = "Quick Sort";
				break;
			}

			finish = clock();
			timeDiff = finish - start;
			timeAverage = timeDiff / numToSeeStruct;
			
		}
		printItStructs(outFile, heavyStruct, sortName, timeAverage);
	}


}