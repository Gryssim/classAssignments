#include <iostream>
#include <string>
#include <iomanip>
#include "classHead.h"

using namespace std;

int main()
{
	string first;
	string last;
	int test;
	int prog;
	double gpa;
	char grade;
	studentStats student1;

	cout << "What is the student's first and last name? " << endl;
	cin >> first >> last;
	student1.setFName(first);
	student1.setLName(last);
	
	cout << "What is the student's test score? " << endl;
	cin >> test;
	student1.setTScore(test);
	
	cout << "What is the student's programming score? " << endl;
	cin >> prog;
	student1.setPScore(prog);
	
	cout << "What is the student's GPA? " << endl;
	cin >> gpa;
	student1.setGPA(gpa);
	
	cout << "What is the student's grade? " << endl;
	cin >> grade;
	student1.setGrade(grade);


	cout << "Last Name" << "," << "First Name" << setw(20) << "Test Score" << setw(20) << "Programming Score" << setw(13) << "GPA" << setw(15) << "Grade" << endl;

	cout <<  student1.getLName() << "," << student1.getFName() << setw(20) << student1.getTScore() << setw(20) << student1.getPScore() << setw(20) << student1.getGPA() << setw(15)
		<< student1.getGrade() << endl;

}