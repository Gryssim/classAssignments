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

	outFile << "Action Table" << endl<< left << "\n" << "                ";
	for (int j = 0; j < lastCharType; j++){
		outFile << left << setw(15) << charTypeToString((charType)j);
	}
	outFile << endl;
	
	/*outFile << left << "\n" << "              " << setw(15) << "letter" << setw(15) << "digit" << 
		setw(15) << "period" << setw(15) << "delimiter" << setw(15) <<  "blank"
		<< setw(15) << "pod" << setw(15) << "eoln" << setw(15) <<"illegal"  << endl;
		*/
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
	
	outFile << "State Table" << endl;

	outFile << "Action Table" << endl << left << "\n" << "                ";
	for (int j = 0; j < lastCharType; j++){
		outFile << left << setw(15) << charTypeToString((charType)j);
	}

	outFile << endl;
	/*
	outFile  << "\n       "  << setw(15) << "letter" << setw(15) << "digit" <<
		setw(15) << "period" << setw(15) << "delimiter" << setw(15) << "blank"
		<< setw(15) << "pod" << setw(15) << "eoln" << setw(15) << "illegal" << endl;

		*/
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
	charType ans;
	
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		ans = letter;
	else if (ch >= '0' && ch <= '9')
		ans = digit;
	else if (ch == '.')
		ans = period;
	else if (ch == '"' || ch == ',' || ch == '+' || ch == '-' || ch == '/'
		|| ch == '*' || ch == '>' || ch == '<' || ch == '#' || ch == '^'
		|| ch == '=')
		ans = delimiter;
	else if (ch == ' ')
		ans = blank;
	else if (ch == '$' || ch == '%')
		ans = pod;
	else if (ch == '\n')
		ans = eoln;
	else
		ans = illegal;
	
	return ans;
}

void doAction(int act, string &tkn, char ch, stateType &state, string reserve[], ofstream &outFile){
	switch (act){
	case 1:
		tkn += ch;
	case 2:
		for (int i = 0; i < reserveSize; i++){
			if (tkn == reserve[i]){
				state = resWrd;
				outFile << tkn << setw(10) << stateToString(state) << endl;
				tkn = "";
			}
			else{
				state = var;
				outFile << tkn << setw(10) << stateToString(state) << endl;
				tkn = "";
			}
		}
	case 3:
		outFile << tkn << endl;
		tkn = "";
	case 4:
		outFile << tkn << setw(10) << "Improper usage." << setw(10) << ch << endl;
		tkn = "";
	case 5:
		outFile << "Improper usage." << setw(10) << ch << endl;
	case 6:

	case 7:
		outFile << "Illegal character." << setw(10) << ch << endl;
	case 8:
		for (int i = 0; i < reserveSize; i++){
			if (tkn == reserve[i]){
				state = resWrd;
				outFile << tkn << setw(10) << stateToString(state) << endl;
				tkn = "";
				tkn += ch;
			}
			else{
				state = var;
				outFile << tkn << setw(10) << stateToString(state) << endl;
				tkn = "";
				tkn += ch;
			}
		}
	case 9:
		outFile << tkn << endl;
		tkn = "";
		tkn += ch;
	case 10:
		tkn += ch;
		state = var;
		outFile << tkn << endl;
		tkn = "";
	case 11:
		for (int i = 0; i < reserveSize; i++){
			if (tkn == reserve[i]){
				state = resWrd;
				outFile << tkn << setw(10) << stateToString(state) << endl;
				tkn = "";
			}
			else{
				state = var;
				outFile << tkn << setw(10) << stateToString(state) << endl;
				tkn = "";
			}
		}
	case 12:
		tkn += ch;
		outFile << tkn << endl;
		tkn = "";
	case 13:
		outFile << tkn << setw(10) << "Illegal character" << setw(10) << ch << endl;
		tkn = "";
	}
}

void scanner(int actionT[lastState][lastCharType], stateType FSM[lastState][lastCharType], string reserve[], ofstream &outFile){
	ifstream inFile("prog1.bas");
	stateType state = newTkn;
	charType cct;
	string tkn;
	char ch;
	int act;
	
	while (!inFile.eof()){

		//Read in for each char in a row - read ch
		inFile >> ch;

		// char charType (cct) new function getCharType(ch)

		cct = getCharType(ch);

		//set action (act) based on state and cct act = actionT[state][cct]

		act = actionT[state][cct];

		//new function doAction(some parameters here, should know more after writing)

		doAction(act, tkn, ch, state, reserve, outFile);

		//set state after action based on state table. state = FSM[state][cct]
		
		state = FSM[state][cct];

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

	//scanner(actionT, FSM, reserve, outFile);

}