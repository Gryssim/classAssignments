#include <iostream>

using namespace std;

int smallestIndex(int numList[], int SIZE);
void initialize(int numList[], int SIZE);

int main()
{
	const int SIZE = 10;
	int numbers;
	int numList[SIZE];
	int result; 
	
	initialize(numList, SIZE);
	
	cout << "Please enter 10 integers: " << endl;
	
	for (int i = 0; i < SIZE; i++)
	{
		cin >> numbers;
		numList[i] = numbers;
	}
		
	cout << "The position of the smallest index is: " << smallestIndex(numList, SIZE) << " and is " << numList[smallestIndex(numList, SIZE)] << "." << endl;
}

int smallestIndex(int numList[], int SIZE)
{
	int smallest = 100;
	int index; 
	for (int i = 0; i < SIZE; i++)
		if (numList[i] < smallest)
		{
			smallest = numList[i];
			index = i;
		}
	return index; 
}

void initialize(int numList[], int SIZE)
{
	for (int i = 0; i < SIZE; i++)
		numList[i] = 0;
}