#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct studentType
{
	string studentFName;
	string studentLName;
	int testScore;
	char grade;
};

void readData(ifstream&, studentType sData[], int);
void getGrade(studentType sData[], int);
void highestScore(studentType sData[], int);
void outputData(ofstream&, studentType sData[], int);

int main()
{
	const int NUMSTUDENTS = 20;
	studentType sData[NUMSTUDENTS];
	ifstream inData;
	ofstream outData;
	string inFile;
	
	cout << "Please enter the filename: " << endl;
	cin >> inFile;

	inData.open(inFile.c_str());

	if (!inData)
	{
		cout << "Cannot open that file." << endl;
		return 1; 
	}

	readData(inData, sData, NUMSTUDENTS);

	getGrade(sData, NUMSTUDENTS);

	highestScore(sData, NUMSTUDENTS);

	outputData(outData, sData, NUMSTUDENTS);
}

void readData(ifstream& inData, studentType sData[], int SIZE)
{
	for (int i = 0; i < SIZE; i++) // input student data the i-th position. 
	{
		inData >> sData[i].studentFName;
		inData >> sData[i].studentLName;
		inData >> sData[i].testScore;
	}
}

void getGrade(studentType sData[], int SIZE)
{
	for (int i = 0; i < SIZE; i++) //read test score of i-th position, and set grade of struct. 
	{
		if (sData[i].testScore <= 100 && sData[i].testScore >= 90)
			sData[i].grade = 'A';
		else if (sData[i].testScore < 90 && sData[i].testScore >= 80)
			sData[i].grade = 'B';
		else if (sData[i].testScore < 80 && sData[i].testScore >= 70)
			sData[i].grade = 'C';
		else if (sData[i].testScore < 70 && sData[i].testScore >= 60)
			sData[i].grade = 'D';
		else
			sData[i].grade = 'F';
	}
}

void highestScore(studentType sData[], int SIZE)
{
	studentType highScore;

	for (int i = 0; i <= SIZE; i++)
	{
		
		for (int j = i + 1; j <= SIZE - 1; j++)
		{
			if (sData[i].testScore < sData[j].testScore)
					{
						highScore = sData[i]; 
						sData[i] = sData[j];
						sData[j] = highScore;

					}
			}
	}
	return;
}

void outputData(ofstream& outData, studentType sData[], int SIZE)
{
	outData.open("FinalData.txt");
	outData << "Last Name" << setw(17) << "First Name" << setw(15) << "Test Score" << setw(15) << "Grade" << "\n" << "\n";
	for (int i = 0; i < SIZE; i++)
	{
		outData << left << setw(15) << sData[i].studentLName+"," << " " << left << setw(15) << sData[i].studentFName << setw(20) << sData[i].testScore <<setw(20) << sData[i].grade << endl;
	}
}