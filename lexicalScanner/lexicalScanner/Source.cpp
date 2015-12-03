/*
Douglas Plock
CSCI 112
Lexical Scanner Final Project
*/

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
	int i = 0;

	while (!inFile.eof()){
		inFile >> reserve[i];
		i++;
	}

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
	int i = 0;

	while (!inFile.eof()){
		getline(inFile, prog[i]);
		prog[i] += '|';
		i++;
	}
}

void printProg(string prog[], ofstream &outFile){
	outFile << endl << "Program 1" << endl;

	for (int i = 0; i < progSize; i++){
		outFile << prog[i] << endl;
	}
	outFile << endl << endl;
}

void readExplain(string exp[]){
	ifstream inFile("explain.dat");
	int i = 0;

	while (!inFile.eof()){
		getline(inFile, exp[i]);
		i++;
	}
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

	outFile << "Action Table" << endl<< left << "\n" << "                ";
	for (int j = 0; j < lastCharType; j++){
		outFile << left << setw(15) << charTypeToString((charType)j);
	}
	outFile << endl;
	
	for (int i = 0; i < 127; i++){
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
	

	outFile << "State Table" << endl << left << "\n" << "                ";
	for (int j = 0; j < lastCharType; j++){
		outFile << left << setw(15) << charTypeToString((charType)j);
	}

	outFile << endl;

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

charType getCharType(char ch){
	charType ans = illegal;
	
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		ans = letter;
	else if (ch >= '0' && ch <= '9')
		ans = digit;
	else if (ch == '.')
		ans = period;
	else if (ch == '"' || ch == ',' || ch == '+' || ch == '-' || ch == '/'
		|| ch == '*' || ch == '>' || ch == '<' || ch == '(' || ch == '^'
		|| ch == '=' || ch ==')' || ch == '&')
		ans = delimiter;
	else if (ch == ' ')
		ans = blank;
	else if (ch == '$' || ch == '%')
		ans = pod;
	else if (ch == '|')
		ans = eoln;
	else
		ans = illegal;
	
	return ans;
}

bool isReserved(string tkn, string reserve[]){
	bool isReserved = false;
	for (int i = 0; i < reserveSize; i++){
		if (tkn == reserve[i])
			isReserved = true;
	}
	return isReserved;
}

void doAction(int act, string &tkn, char ch, stateType &state, string reserve[], ofstream &outFile){
	switch (act){
	case 1:
		tkn += ch;
		break;
	case 2:
		if (isReserved(tkn, reserve))
			state = resWrd;
		
		else
			state = var;
		
		outFile << left << setw(10) << tkn << " " << stateToString(state) << endl;
		tkn = "";
		break;
	case 3:
		outFile << left << setw(10) << tkn << " " << stateToString(state) << endl;
		tkn = "";
		break;
	case 4:
		outFile << left << setw(10) << tkn << " " << stateToString(state) << endl;
		outFile << "Improper usage." << endl;
		outFile << ch << endl;
		tkn = "";
		break;
	case 5:
		outFile << "Improper usage." << endl;
		outFile << ch << endl;
		break;
	case 6:
		break;
	case 7:
		outFile << "Illegal character." << endl;
		outFile << ch << endl;
		break;
	case 8:
		if (isReserved(tkn, reserve))
			state = resWrd;
		else
			state = var;

		outFile << left << setw(10) << tkn << " " << stateToString(state) << endl;
		tkn = "";
		tkn += ch;
		break;
	case 9:
		outFile << left << setw(10) << tkn << " " << stateToString(state) << endl;
		tkn = "";
		tkn += ch;
		break;
	case 10:
		tkn += ch;
		state = var;
		outFile << left << setw(10) << tkn << " " << stateToString(state) << endl;
		tkn = "";
		break;
	case 11:
		if (isReserved(tkn, reserve))
			state = resWrd;
		else
			state = var;
		outFile << left << setw(10) << tkn << " " << stateToString(state) << endl;
		outFile << "Illegal character." << endl;
		outFile << ch << endl;
		tkn = "";
		break;
	case 12:
		tkn += ch;
		outFile << left << setw(10) << tkn << " " << stateToString(state) << endl;
		tkn = "";
		break;
	case 13:
		outFile << left << setw(10) << tkn << " " << stateToString(state) << endl;
		outFile << "Illegal character" << endl;
		outFile << ch << endl;
		tkn = "";
		break;
	}
}

void printTokenHead(ofstream &outFile){
	outFile << left << setw(10) << "Token" << " " << "Token Type" << endl;
	for (int i = 0; i < 22; i++){
		outFile << "=";
	}
	outFile << endl;
}

void scanner(int actionT[lastState][lastCharType], stateType FSM[lastState][lastCharType], string reserve[], string prog[], ofstream &outFile){
	stateType state;
	charType cct;
	string tkn, line;
	char ch;
	int act;
	int j = 0;

	printTokenHead(outFile);

	while (j < progSize){

		line = prog[j];
		state = newTkn;
		tkn = "";
		for (int i = 0; i < line.length(); i++){
			// set ch equal to line[i]
			ch = line[i];

			// char charType (cct) new function getCharType(ch)

			cct = getCharType(ch);

			//set action (act) based on state and cct act = actionT[state][cct]

			act = actionT[state][cct];

			//new function doAction(some parameters here, should know more after writing)

			doAction(act, tkn, ch, state, reserve, outFile);

			//set state after action based on state table. state = FSM[state][cct]

			state = FSM[state][cct];
		}
		j++;
	}

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

	scanner(actionT, FSM, reserve, prog, outFile);

}