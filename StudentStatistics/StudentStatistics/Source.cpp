// This program is to compile student statistics
// and organize results in a descending list 
// based on student test average, as well as class
// statistics. Written by Douglas Plock

#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

struct studentStats
{
	int sTest1 = 0;
	int sTest2 = 0;
	int sTest3 = 0;
	int sTest4 = 0;
	double testSum = 0;
	double studentAverage = 0;
	char studentGrade;
	string studentFName = "";
	string studentLName = "";
};

void inputData(ifstream&, studentStats sData[], int);

void studentAverage(studentStats sData[], int);

void setStudentGrade(studentStats sData[], int, double&, double&, double&, double&, double&);

void descendingSort(studentStats sData[], int);

void classAveMinMax(ofstream& outData, studentStats sData[], int);

void classTotals(ofstream& outData, double, double, double, double, double);

void outputData(ofstream&, studentStats sData[], int);

//Request data file name, open file, toss error if no file found and request file name,
//input data from file into struct studentStats, Sum each test score and average for each student
//read student average and provide a grade, sort struct array in descending order based on student
//average, request user for output file name, create file, output data to file,
//determine class average, minimum, and maximum per test and print below main data,
//determine overall grade percentage and print below average/min/max.

int main()
{
	const int SIZE = 50;
	studentStats sData[SIZE];
	ifstream inData;
	ofstream outData;
	string inFile, outFile;
	double aCount = 0, bCount = 0, cCount = 0, dCount = 0, fCount = 0;
	
	cout << "Please enter the name of the student text file: " << endl;
	cin >> inFile;

	inData.open(inFile.c_str());

	while (!inData)
	{
		cin.clear();
		cout << "Unable to locate file." << endl << "Please enter the name of the student text file or enter Q to quit: " << endl;
		cin >> inFile;
		inData.open(inFile.c_str());
		
		if (inFile == "q" || inFile == "Q")
			return 1;
	}

	inputData(inData, sData, SIZE);

	studentAverage(sData, SIZE);

	setStudentGrade(sData, SIZE, aCount, bCount, cCount, dCount, fCount);

	descendingSort(sData, SIZE);

	cout << "Please enter a file name to save the data to: " << endl;
	cin >> outFile;
	outData.open(outFile.c_str());

	outputData(outData, sData, SIZE);

	classAveMinMax(outData, sData, SIZE);
	
	classTotals(outData, aCount, bCount, cCount, dCount, fCount);
}

void inputData(ifstream& inData, studentStats sData[], int SIZE)
{
	int i = 0;
	while (inData)											//Input data from file to i-th array position.
	{
		inData >> sData[i].studentFName;
		inData >> sData[i].studentLName;
		inData >> sData[i].sTest1;
		inData >> sData[i].sTest2;
		inData >> sData[i].sTest3;
		inData >> sData[i].sTest4;
		i++;
	}
}

void studentAverage(studentStats sData[], int SIZE)
{

	for (int i = 0; i < SIZE; i++)
	{
		if (sData[i].studentFName == "")
			return;
		sData[i].testSum = (sData[i].sTest1 + sData[i].sTest2 + sData[i].sTest3 + sData[i].sTest4);
		sData[i].studentAverage = ((sData[i].testSum) / 4);	// Sum of all tests divided by 4 for average.
	}
}

void setStudentGrade(studentStats sData[], int SIZE, double& aCount, double& bCount, double& cCount, double& dCount, double& fCount)
{
	for (int i = 0; i < SIZE; i++)
	{
		if (sData[i].studentFName == "")
			return;
		if (sData[i].studentAverage >= 90)									// Set's grade based on 4 test average.
		{
			sData[i].studentGrade = 'A';
			aCount++;
		}
		else if (sData[i].studentAverage >= 80)
		{
			sData[i].studentGrade = 'B';
			bCount++;
		}
		else if (sData[i].studentAverage >= 70)
		{
			sData[i].studentGrade = 'C';
			cCount++;
		}
		else if (sData[i].studentAverage >= 60)
		{
			sData[i].studentGrade = 'D';
			dCount++;
		}
		else
		{
			sData[i].studentGrade = 'F';
			fCount++;
		}
	}
}

void descendingSort(studentStats sData[], int SIZE)
{
	for (int i = 0; i < SIZE; i++)										//Selection sort to arrange the elements in descending order.
	{
		if (sData[i].studentFName == "")
			return;
		int minIndex = i;
		for (int j = i; j < SIZE; j++)
		{
			if (sData[minIndex].studentAverage < sData[j].studentAverage)
			{
				minIndex = j;
			}
		}
		studentStats temp = sData[i];
		sData[i] = sData[minIndex];
		sData[minIndex] = temp;
	}
}


void classAveMinMax(ofstream& outData, studentStats sData[], int SIZE)
{
	int max = 0, max1 = 0, max2 = 0, max3 = 0;
	int min = 101, min1 = 101, min2 = 101, min3 = 101;
	double ave = 0, ave1 = 0, ave2 = 0, ave3 = 0;
	double counter = 0;

	for (int i = 0; i < SIZE; i++)										//Find Maximum, minimum, and average score of each test.
	{
		if (sData[i].studentFName == "")
			break;
		if (sData[i].sTest1 > max)
			max = sData[i].sTest1;
		if (sData[i].sTest2 > max1)
			max1 = sData[i].sTest2;
		if (sData[i].sTest3 > max2)
			max2 = sData[i].sTest3;
		if (sData[i].sTest4 > max3)
			max3 = sData[i].sTest4;
		if (sData[i].sTest1 < min)
			min = sData[i].sTest1;
		if (sData[i].sTest2 < min1)
			min1 = sData[i].sTest2;
		if (sData[i].sTest3 < min2)
			min2 = sData[i].sTest3;
		if (sData[i].sTest4 < min3)
			min3 = sData[i].sTest4;
		ave = ave + sData[i].sTest1;
		ave1 = ave1 + sData[i].sTest2;
		ave2 = ave2 + sData[i].sTest3;
		ave3 = ave3 + sData[i].sTest4;
		counter++;
	}

	ave = ave / counter;
	ave1 = ave1 / counter;
	ave2 = ave2 / counter;
	ave3 = ave3 / counter;

	outData << fixed;
	outData << setprecision(2);
	outData << "================================================================================" << endl;
	outData << left <<setw(32) << "Class Average: " << left << setw(6) << ave << setw(6) << left << ave1 << setw(6) << left << ave2 << setw(6) << left << ave3 << endl;
	outData << left << setw(32) << "Class Max: " << left << setw(6) << max << setw(6) << left << max1 << setw(6) << left << max2 << setw(6) << left << max3 << endl;
	outData << left << setw(32) << "Class Min: " << left << setw(6) << min << setw(6) << left << min1 << setw(6) << left << min2 << setw(6) << left << min3 << endl;
	outData << "================================================================================" << endl;
}

void classTotals(ofstream& outData, double aCount, double bCount, double cCount, double dCount, double fCount)
{
	double total = (aCount + bCount + cCount + dCount + fCount);		// Set percentage of grades by dividing # of grade by count of grades.
	outData << "Total As: " << setw(5) << right << ((aCount / total)*100) << "%" << endl;
	outData << "Total Bs: " << setw(5) << right << ((bCount / total)*100) << "%" << endl;
	outData << "Total Cs: " << setw(5) << right << ((cCount / total)*100) << "%" << endl;
	outData << "Total Ds: " << setw(5) << right << ((dCount / total)*100) << "%" << endl;
	outData << "Total Fs: " << setw(5) << right << ((fCount / total)*100) << "%" << endl;
	outData << "================================================================================" << endl;

	outData.close();
}

void outputData(ofstream& outData, studentStats sData[], int SIZE)
{

	outData << "================================================================================" << endl
		<< left << setw(15) << "First Name" << left << setw(15) << "Last Name" << left << setw(7) << "Test1" 
		<< left << setw(7) << "Test2" << left << setw(7) << "Test3" << left << setw(7) << "Test4" << left 
		<< setw(9) << "Average" << right << setw(6) << "Grade" << endl
			<< "================================================================================" << endl;
	for (int i = 0; i < SIZE; i++)
	{
		if (sData[i].studentFName == "")
			return;
		outData << fixed;
		outData << setprecision(2);
		outData << left << setw(15) << sData[i].studentFName << left << setw(13) << sData[i].studentLName
			<< right << setw(6) << sData[i].sTest1 << right << setw(6) << sData[i].sTest2 << right << setw(6)
			<< sData[i].sTest3 << right << setw(6) << sData[i].sTest4 << right << setw(12) << sData[i].studentAverage 
			<< right << setw(8) << sData[i].studentGrade << endl;
	}

}