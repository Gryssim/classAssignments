#include <iostream>
#include <cmath>
#include <math.h>	

using namespace std;

void initialize(double numberArray[]);

int main()
{
	const int SIZE = 50;
	double numberArray[SIZE];
	int index; 

	initialize(numberArray);

	for (index = 0; index < 50; index++)
		if (index < 25)
			numberArray[index] = pow((index + 1), 2);
		else
			numberArray[index] = index * 3;

	for (int j = 0; j < 5; j++)
	{ 
		cout << endl;
		for (int i = 0; i < 10; i++)
		{
			cout.width(5);
			cout << numberArray[i + (j * 10)] << " ";
		}
	}
	cout << endl;
	return 0;
}

void initialize(double numberArray[])
{
	int index;

	for (index = 0; index < 50; index++)
		numberArray[index] = index + 1;
		
}