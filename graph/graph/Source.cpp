#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int matrixSize = 'K' + 1;

enum color {white, gray, black};

struct queue
{
	char data;
	queue* link;
};

string colorToString(color clr) {
	string ans;

	if (clr == white)
		ans = "white";
	else if (clr == gray)
		ans = "gray";
	else if (clr == black)
		ans = "black";
	else
		ans = "white";

	return ans;
}

color stringToColor(string str) {
	color ans;

	if (str == "white")
		ans = white;
	else if (str == "gray")
		ans = gray;
	else if (str == "black")
		ans = black;
	else
		ans = white;

	return ans;
}

void createQueue(queue *&head, queue *&tail, queue *&qlast) {
	head = new queue;
	tail = new queue;
	
	head->link = tail;
	tail->link = NULL;

	qlast = head;
}

bool emptyQueue(queue *head, queue *tail) {
	return head->link == tail;
}

void enQueue(queue *head, queue *tail, queue *qlast, char ch) {
	queue *knew;
	knew = new queue;

	knew->data = ch;
	
	knew->link = tail;
	qlast->link = knew;
	qlast = knew;
}

char deQueue(queue *head, queue *tail, queue *qlast) {
	char ans;
	queue *c;
	c = new queue;
	
	if (!emptyQueue(head, tail)) {
		c = head->link;
		ans = c->data;
		head->link = c->link;
		if (c == qlast) qlast = head;
		delete c;
	}
	else
		cout << "The queue is empty" << endl;

	return ans;
}

void readEdgeList(char adjArray[][matrixSize]) {
	ifstream inFile("edge.dat");
	char junk, i, j;	

	while (!inFile.eof()) {
		inFile >> i >> junk >> j;
		adjArray[i][j] = '1';
	}
}

void initAdjArray(char adjArray[][matrixSize]) {
	for (int i = 'A'; i < matrixSize; i++) {
		for (int j = 'A'; j < matrixSize; j++) {
			if (i == j) adjArray[i][j] = 'X';
			else
				adjArray[i][j] = '0';
		}
	}
}

void printArray(char adjArray[][matrixSize], ofstream &outFile) {
	outFile << "   ";
	for (int i = 'A'; i < matrixSize; i++) {
		outFile << setw(5) << right << (char)i;
	}
	outFile << endl;

	for (int i = 0; i < 59; i++) {
		outFile << "=";
	}
	outFile << endl;

	for (int i = 'A'; i < matrixSize; i++) {
		outFile << left << char(i) << " " << '|';
		for (int j = 'A'; j < matrixSize; j++) {
			outFile << setw(5) << right << adjArray[i][j];
		}
		outFile << endl;
	}
	outFile << endl << endl;
}

void initVectColors(color colorArray[]) {
	for (int i = 'A'; i < matrixSize; i++) {
		colorArray[i] = white;
	}
}

void printSearchTitle(ofstream &outFile, string searchType, char start) {
	outFile << searchType << " starting from " << start << ":" << endl;
}

char queueTop(queue *head, queue *tail) {
	char ans;

	if (!emptyQueue(head, tail)) {
		ans = head->link->data;
	}
	else
		ans = '$';
	return ans;
}

void bfSearch(char adjArray[][matrixSize], color colorArray[], char start, queue *head, queue *tail, queue *qlast, ofstream &outFile) {
	initVectColors(colorArray);
	char vect;
	string searchType = "Breadth First Search";
	colorArray[start] = gray;

	printSearchTitle(outFile, searchType, start);

	outFile << left << start << " ";

	enQueue(head, tail, qlast, start);
	while (!emptyQueue(head, tail)) {
		vect = deQueue(head, tail, qlast);
		for (int i = 'A'; i < matrixSize; i++){
			//cout << "Adj Matrix[" << vect << "][" << (char)i << "]: " << adjArray[vect][i] << endl;
			//cout << colorToString(colorArray[i]) << endl;
			//cout << queueTop(head, tail) << endl;
			//system("pause");
			if ((adjArray[vect][i] != '0') && (i != vect) && (colorArray[i] == white)) {
				colorArray[i] = gray;
				outFile << char(i) << " ";
				enQueue(head, tail, qlast, char(i));
			}
			colorArray[vect] = black;
		}
		
	}
	outFile << endl << endl;

}

void dfSearch_visit(char adjArray[][matrixSize], color colorArray[], char vert, ofstream &outFile) {
	colorArray[vert] = gray;
	for (int i = 'A'; i < matrixSize; i++) {
		if (adjArray[vert][i] == '1') {
			if (colorArray[i] == white) {
				outFile << char(i) << " ";
				dfSearch_visit(adjArray, colorArray, char(i), outFile);
			}
		}
	}
	colorArray[vert] = black;

}

void dfSearch(char adjArray[][matrixSize], color colorArray[], char vert, ofstream &outFile) {
	string searchType = "Depth First Search";
	initVectColors(colorArray);
	printSearchTitle(outFile, searchType, vert);
	outFile << vert << " ";
	dfSearch_visit(adjArray, colorArray, vert, outFile);
	outFile << endl << endl;
}


void main() {
	queue *head, *tail, *qlast;
	ofstream outFile("output.ot");
	color colorArray[matrixSize];
	char adjArray[matrixSize][matrixSize];

	createQueue(head, tail, qlast);

	initAdjArray(adjArray);
	printArray(adjArray, outFile);
	readEdgeList(adjArray);
	printArray(adjArray, outFile);

	//BF Search starting from A.
	bfSearch(adjArray, colorArray, 'A', head, tail, qlast, outFile);

	//DF Search starting from A.
	dfSearch(adjArray, colorArray, 'A', outFile);

	//BF Search starting from F.
	bfSearch(adjArray, colorArray, 'F', head, tail, qlast, outFile);

	//DF Search starting at G.
	dfSearch(adjArray, colorArray, 'G', outFile);
}