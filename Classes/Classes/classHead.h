#include <iostream>
#include <string>

using namespace std;

class studentStats
{
public:
	string getFName() const;

	string getLName() const;

	int getTScore() const;

	int getPScore() const;

	double getGPA() const;

	char getGrade() const;

	void setFName(string first = "");

	void setLName(string last = "");

	void setTScore(int);

	void setPScore(int);

	void setGPA(double);

	void setGrade(char);

private:
	string studentFName;
	string studentLName;
	int testScore;
	int programmingScore;
	double studentGPA;
	char grade;
};