#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int maxClass = 30;

struct classes{
	int crn;
	string course;
	int crHrs;
	int numStu;
	int stuCrHrs;
	string prof;
};

struct courseCount{
	string course;
	int numStuCourse = 0;
};

const classes initrec = { -1, "none", 0, 0, 0, "none" };

void initIt(classes cl[], double &numClass){
	int i;

	for (i = 0; i < maxClass; i++) cl[i] = initrec;
	numClass = 0;
}

void readIt(classes cl[], double &numClass){
	int i = 0;
	ifstream inFile("inFile.dat");

	while (!inFile.eof()){
		inFile >> cl[i].crn >> cl[i].course >> cl[i].crHrs >> cl[i].numStu >> cl[i].prof;
		i++;
	}
	numClass = i;
};

void printIt(classes cl[], double numClass, ofstream &outFile, double totStu, double totStuCrHrs){
	int i;

	for (i = 0; i < 87; i++){
		outFile << "=";
	}
	outFile << endl;
	outFile << left << "| " << setw(12) << " " << setw(18) << "Course" << setw(10) << "Credit" <<
		setw(16) << "Number of" << setw(18) << "Student Credit" << setw(8) << "" << "  |" << endl;
	outFile << left << "| " << setw(10) << "CRN" << setw(20) << "Description" << setw(10) << "Hours" <<
		setw(20) << "Students" << setw(15) << "Hours" << setw(8) << "Professor" << "|" << endl;
	for (i = 0; i < 87; i++){
		outFile << "=";
	}
	outFile << endl;
	for (i = 0; i < numClass; i++){
		outFile << left << "| " << setw(10) << cl[i].crn << setw(20) << cl[i].course << setw(3) << right << cl[i].crHrs << setw(12)
			<< cl[i].numStu << setw(19) << cl[i].stuCrHrs << setw(11) << " " << setw(9) << left << cl[i].prof << "|" << endl;
	}
	for (i = 0; i < 87; i++){
		outFile << "=";
	}

	outFile << endl << right << setw(47) << totStu << setw(19) << totStuCrHrs << endl << endl;
};

void swapIt(classes &a, classes &b){
	classes temp;
	temp = a;

	a = b;
	b = temp;
}

void sortIt(classes cl[], double numClass, ofstream &outFile, double totStu, double totStuCrHrs){
	int i, j;

	for (j = 0; j < numClass - 1; j++){
		for (i = 0; i < numClass - 1; i++)
			if (cl[i].stuCrHrs < cl[i + 1].stuCrHrs) swapIt(cl[i], cl[i + 1]);
	}
	printIt(cl, numClass, outFile, totStu, totStuCrHrs);
}

void averageIt(ofstream &outFile, double numClass, double totStu, double &aveStu){
	aveStu = totStu / numClass;

	outFile << setprecision(4) << "There are, on average, " << aveStu << " students per class." << endl << endl;
}

void totalIt(classes cl[], double numClass, double &totStu, double &totStuCrHrs){
	totStu = 0;
	totStuCrHrs = 0;
	int i;

	for (i = 0; i < numClass; i++){
		cl[i].stuCrHrs = cl[i].crHrs * cl[i].numStu;
		totStu += cl[i].numStu;
		totStuCrHrs += cl[i].stuCrHrs;
	}
}

void alphabetSort(ofstream &outFile, classes cl[], double numClass){
	int i, j;

	for (j = 0; j < numClass - 1; j++){
		for (i = 0; i < numClass - 1; i++)
			if (cl[i].course > cl[i + 1].course) swapIt(cl[i], cl[i + 1]);
	}
}

void printCourseCount(ofstream &outFile, courseCount cc[], int uniqCourse){
	int i;
	for (i = 0; i < 32; i++){
		outFile << "=";
	}
	outFile << endl;
	outFile << left << "| " << setw(15) << "Course" << setw(14) << "Students" << setw(3) << "|" << endl;;
	for (i = 0; i < 32; i++){
		outFile << "=";
	}
	outFile << endl;
	for (i = 0; i < uniqCourse - 1; i++){
		outFile << left << "| " << setw(15) << cc[i].course << setw(7) << right << cc[i].numStuCourse << setw(8) << "|" << endl;
	}
	for (i = 0; i < 32; i++){
		outFile << "=";
	}
}

void countUniq(classes cl[], double numClass, int &uniqCourse){
	int i;
	for (i = 1; i < numClass; i++){
		if (cl[i - 1].course == cl[i].course){
			uniqCourse++;
		}
	}
}

void countCourseStu(ofstream &outFile, classes cl[], courseCount cc[], int uniqCourse){
	int i = 1;
	int j;
	for (j = 0; j < uniqCourse - 1; j++){
		cc[j].numStuCourse += cl[i - 1].numStu;
		cc[j].course = cl[i - 1].course;
		while (cl[i - 1].course == cl[i].course){
			cc[j].numStuCourse += cl[i].numStu;
			i++;
		}
		i++;
	}
}

void getCourseTotStu(ofstream &outFile, classes cl[], double numClass){
	courseCount cc[maxClass];
	int uniqCourse = 0;
	
	alphabetSort(outFile, cl, numClass);
	countUniq(cl, numClass, uniqCourse);
	countCourseStu(outFile, cl, cc, uniqCourse);
	printCourseCount(outFile, cc, uniqCourse);
}




void main(){
	classes cl[maxClass];
	ifstream inFile;
	ofstream outFile("outFile.txt");
	double numClass, totStu, totStuCrHrs, aveStu;

	initIt(cl, numClass);
	readIt(cl, numClass);
	totalIt(cl, numClass, totStu, totStuCrHrs);
	printIt(cl, numClass, outFile, totStu, totStuCrHrs);
	sortIt(cl, numClass, outFile, totStu, totStuCrHrs);	
	averageIt(outFile, numClass, totStu, aveStu);
	getCourseTotStu(outFile, cl, numClass);
};