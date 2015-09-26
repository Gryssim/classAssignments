#include <iostream>
#include <string>
#include "classHead.h"

using namespace std;

void studentStats::setFName(string first)
{
	studentFName = first;
}

void studentStats::setLName(string last)
{
	studentLName = last;
}

void studentStats::setTScore(int tScore)
{
	testScore = tScore;
}

void studentStats::setPScore(int ProgScore)
{
	programmingScore = ProgScore;
}

void studentStats::setGPA(double gpa)
{
	studentGPA = gpa;
}

void studentStats::setGrade(char gr)
{
	grade = gr;
}

string studentStats::getFName() const
{
	return studentFName;
}

string studentStats::getLName() const
{
	return studentLName;
}

int studentStats::getTScore() const
{
	return testScore;
}

int studentStats::getPScore() const
{
	return programmingScore;
}

double studentStats::getGPA() const
{
	return studentGPA;
}

char studentStats::getGrade() const
{
	return grade;
}
