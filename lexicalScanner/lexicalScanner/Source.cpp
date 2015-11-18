#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int reserveSize = 14;

void swapIt(string &a, string &b){
	string temp;
	temp = b;
	b = a;
	a = temp;
}

void bubSort(string a[]){
	int i, j;

	for (i = 0; i < reserveSize - 1; i++){
		for (j = 0; j < reserveSize - 1; j++){
			if (a[j] > a[j + 1]) swapIt(a[j], a[j + 1]);
		}
	}
}

void readReserveList(string reserve[]){
	ifstream inFile("reserve.dat");

	for (int i = 0; i < reserveSize; i++) inFile >> reserve[i];

	bubSort(reserve);

}

void printReserveList(string reserve[], ofstream &outFile){
	outFile << endl << "Reserve List" << endl;
	
	for (int i = 0; i < reserveSize; i++){
		outFile << reserve[i] << endl;
	}

}

void readProg(string prog[]){
	ifstream inFile("prog1.bas");

	for (int i = 0; i < 16; i++) getline(inFile, prog[i]);

}

void printProg(string prog[], ofstream &outFile){
	outFile << endl << "Program 1" << endl;

	for (int i = 0; i < 16; i++){
		outFile << prog[i] << endl;
	}
}

void readExplain(string exp[]){
	ifstream inFile("explain.dat");

	for (int i = 0; i < 13; i++) getline(inFile, exp[i]);
}

void printExplain(string exp[], ofstream &outFile){

	outFile << endl << "Explanations of Action Table Entries" << endl;

	for (int i = 0; i < 13; i++){
		outFile << exp[i] << endl;
	}
}

void main(){
	ofstream outFile("output.out");
	string reserve[reserveSize];
	string exp[13];
	string prog[16];

	readReserveList(reserve);
	printReserveList(reserve, outFile);
	readExplain(exp);
	printExplain(exp, outFile);
	readProg(prog);
	printProg(prog, outFile);

}