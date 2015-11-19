#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int reserveSize = 14;
const int progSize = 16;
const int explainSize = 13;

enum stateType {newTkn, resWrd, var, integer, real, delim, lastState};
enum charType {letter, digit, period, delimiter, blank, pod, eoln, illegal, lastCharType};


stateType stringToState(string str){
	stateType ans;
	if (str == "newTkn")
		ans = newTkn;
	else if (str == "resWrd")
		ans = resWrd;
	else if (str == "var")
		ans = var;
	else if (str == "integer")
		ans = integer;
	else if (str == "real")
		ans = real;
	else if (str == "delim")
		ans = delim;
	else
		ans = lastState;

	return ans;
}

string stateToString(stateType state){
	string ans;
	if (state == newTkn)
		ans = "newTkn";
	else if (state == resWrd)
		ans = "resWrd";
	else if (state == var)
		ans = "var";
	else if (state == integer)
		ans = "integer";
	else if (state == real)
		ans = "real";
	else if (state == delim)
		ans = "delim";
	else
		ans = "lastState";

	return ans;
}

charType stringToCharType(string str){
	charType ans;
	if (str == "letter")
		ans = letter;
	else if (str == "digit")
		ans = digit;
	else if (str == "period")
		ans = period;
	else if (str == "delimiter")
		ans = delimiter;
	else if (str == "blank")
		ans = blank;
	else if (str == "pod")
		ans = pod;
	else if (str == "eoln")
		ans = eoln;
	else if (str == "illegal")
		ans = illegal;
	else
		ans = lastCharType;

	return ans;
}

string charTypeToString(charType ct){
	string ans;
	if (ct == letter)
		ans = "letter";
	else if (ct == digit)
		ans = "digit";
	else if (ct == period)
		ans = "period";
	else if (ct == delimiter)
		ans = "delimiter";
	else if (ct == blank)
		ans = "blank";
	else if (ct == pod)
		ans = "pod";
	else if (ct == eoln)
		ans = "eoln";
	else if (ct == illegal)
		ans = "illegal";
	else
		ans = "lastCharType";

	return ans;
}

istream& operator >>(istream &inFile, stateType& one){
	inFile >> one;

	return inFile;
}


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

	for (int i = 0; i < progSize; i++) getline(inFile, prog[i]);

}

void printProg(string prog[], ofstream &outFile){
	outFile << endl << "Program 1" << endl;

	for (int i = 0; i < progSize; i++){
		outFile << prog[i] << endl;
	}
}

void readExplain(string exp[]){
	ifstream inFile("explain.dat");

	for (int i = 0; i < explainSize; i++) getline(inFile, exp[i]);
}

void printExplain(string exp[], ofstream &outFile){

	outFile << endl << "Explanations of Action Table Entries" << endl;

	for (int i = 0; i < explainSize; i++){
		outFile << exp[i] << endl;
	}
}

void readActionTable(int actionT[lastState][lastCharType]){
	ifstream inFile("action.dat");
	
	for (int i = newTkn; i < lastState; i++){
		for (int j = letter; j < lastCharType; j++){
			inFile >> actionT[i][j];
		}
	}
}

void printActionTable(int actionT[lastState][lastCharType], ofstream &outFile){
	stateType collumn;

	outFile << "Action Table" << endl;
	outFile << left << "\n" << "              " << setw(15) << "letter" << setw(15) << "digit" << 
		setw(15) << "period" << setw(15) << "delimiter" << setw(15) <<  "blank"
		<< setw(15) << "pod" << setw(15) << "eoln" << setw(15) <<"illegal"  << endl;
	for (int i = 0; i < 126; i++){
		outFile << "=";
	}
	outFile << endl;

	for (int i = newTkn; i < lastState; i++){
		collumn = (stateType)i;
		outFile << setw(15) << left << stateToString(collumn) << "|";
		for (int j = letter; j < lastCharType; j++){
			outFile << setw(15) << actionT[i][j];
		}
		outFile << endl << left <<  setw(17);
	}
	outFile << endl << endl  << setw(16);
}

void readStateTable(stateType FSM[lastState][lastCharType]){
	ifstream inFile("state.dat");
	string stateIn;

	for (int i = newTkn; i < lastState; i++){
		for (int j = letter; j < lastCharType; j++){
			inFile >> stateIn;
			FSM[i][j] = stringToState(stateIn);
		}
	}
}

void printStateTable(stateType FSM[lastState][lastCharType], ofstream &outFile){
	stateType collumnTitle;
	string stateOut;
	
	outFile << "State Table" << endl;
	outFile  << "\n       "  << setw(15) << "letter" << setw(15) << "digit" <<
		setw(15) << "period" << setw(15) << "delimiter" << setw(15) << "blank"
		<< setw(15) << "pod" << setw(15) << "eoln" << setw(15) << "illegal" << endl;

	for (int i = 0; i < 127; i++){
		outFile << "=";
	}
	outFile << endl;


	for (int i = newTkn; i < lastState; i++){
		collumnTitle = (stateType)i;
		outFile << setw(15) << left << stateToString(collumnTitle) << "|";
		for (int j = letter; j < lastCharType; j++){
			stateOut = stateToString(FSM[i][j]);
			outFile << setw(15) << stateOut;
		}
		outFile << endl  << left << setw(17);
	}
	outFile << endl;
}


void main(){
	ofstream outFile("output.out");
	string reserve[reserveSize];
	string exp[explainSize];
	string prog[progSize];

	int actionT[lastState][lastCharType];
	stateType FSM[lastState][lastCharType];

	readReserveList(reserve);
	printReserveList(reserve, outFile);
	readStateTable(FSM);
	printStateTable(FSM, outFile);
	readActionTable(actionT);
	printActionTable(actionT, outFile);
	readExplain(exp);
	printExplain(exp, outFile);
	readProg(prog);
	printProg(prog, outFile);

}