#include <iostream>

using namespace std;

int main()
{
	int a;
	int b; 
	int c;
	char Cont = 'y';

	
	while (Cont == 'y' || Cont == 'Y')
	{
		cout << "Please enter three numbers to be sorted: ";
		cin >> a >> b >> c;
		if (a > b && a > c) //Compare if a is greater than b and c to leave as largest integer. 
		{
			if (b > c)
			{
				cout << c << " " << b << " " << a << endl;
			}
			else  
			{
				cout << b << " " << c << " " << a << endl;
			}
		}
		else if (b > c && b > a) // If a is not largest, compare b to a and c. 
		{

			if (a > c) 
			{
				cout << c << " " << a << " " << b << endl;
			}
			else
			{
				cout << a << " " << c << " " << b << endl;
			}

			}
		else if (c > a && c > b) // if b and a are not largest compare c. 
		{
			
			if (a > b)
			{
				cout << b << " " << a << " " << c << endl;
			}
			else
			{
				cout << a << " " << b << " " << c << endl;
			}
		}
		else // If non-numbers are input, end program.
		{
			cout << "These are not valid integers.";
			cin.clear();
			return 0;
		}
		cout << "Try another set? (Y/N): ";
		cin >> Cont;
		
	}
	return 0; 
}