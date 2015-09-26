#include <iostream>

using namespace std;

int main()
{
	int even, odd, integer;
	
	even = 0;
	odd = 0;

	cout << "Enter a number: ";
	cin >> integer;
	
	for (int i = 0; i < 10; i++)
	{
		if ((integer % 2) == 0)
			even = even + integer;
		
		else if ((integer % 2) != 0)
			odd = odd + integer;
		
		else 
			cout << "That is not a valid number.";

		cout << "Please enter another number: ";
		cin >> integer;
	}

	cout << "The sum of the even numbers = " << even << endl;
	cout << "The sum of the odd numbers = " << odd << endl;

	return 0;
}