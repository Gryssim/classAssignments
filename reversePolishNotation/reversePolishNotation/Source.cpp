/*
Douglas Plock
CSCI 112
Reverse Polish Notation
*/


#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

const int MAXSTACK = 100;
const char initVal = '$';

void createStack(char stack[], int &top){
	int i;
	top = -1;
	for (i = 0; i < MAXSTACK; i++){
		stack[i] = initVal;
	}
}

bool fullStack(int top){
	return top >= MAXSTACK - 1;
}

bool emptyStack(int top){
	return top < 0;
}

void push(char stack[], int &top, char ch){
	if (!fullStack(top)){
		top++;
		stack[top] = ch;
	}
	else cout << "The stack is full" << endl;
}

char pop(char stack[], int &top){
	char temp = initVal;
	if (!emptyStack(top)){
		temp = stack[top];
		stack[top] = initVal;
		top--;
	}
	return temp;
}

int priority(char ch){
	int weight;
	switch (ch){
	case '+':
	case '-':
		weight = 5;
		break;
	case '*':
	case '/':
		weight = 10;
		break;
	default:
		weight = 0;
	}
	return weight;
}

void readIt(char stack[], int &top){
	string inStr, outStr;
	ofstream outFile("output.txt");
	ifstream inFile("input.dat");
	int i, len;
	char ch;

	outFile << "Infix Notation" << setw(23) << "RPN Notation" << endl;
	for (i = 0; i < 37; i++){
		outFile << "=";
	}

	outFile << endl;

	while (!inFile.eof()){
		outStr = "";
		inFile >> inStr;
		len = inStr.length();
		for (i = 0; i < len; i++){
			ch = inStr[i];
			if (ch >= 'A' && ch <= 'Z'){
				outStr += ch;
			}
			else if (ch == '('){
				push(stack, top, ch);
			}
			else if (ch == ')'){
				while (!emptyStack(top) && ch != '('){
					ch = pop(stack, top);
					if (ch != '('){
						outStr += ch;
					}
				}
			}
			else if (emptyStack(top)){
				push(stack, top, ch);
			}
			else if (priority(ch) > priority(stack[top])){
				push(stack, top, ch);
			}
			else {
				while (!emptyStack(top) && priority(ch) <= priority(stack[top])){
					outStr += pop(stack, top);
				}
				push(stack, top, ch);
			}
		}

		while (!emptyStack(top)) outStr += pop(stack, top);

		outFile << left << setw(25) << inStr << setw(9) << outStr << endl;
	}
}

void main(){
	char stack[MAXSTACK];
	int top;

	createStack(stack, top);
	readIt(stack, top);
}