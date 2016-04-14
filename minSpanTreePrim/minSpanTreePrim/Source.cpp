#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

const int matrixSize = 'M' + 1;

enum colors {white, gray, black};

struct queue {
	char vSource, vDest;
	int weight;
	queue* link;
};

struct edge {
	char vSource, vDest;
	int weight;
};

void createQueue(queue *&head, queue *&tail) {
	head = new queue;
	tail = new queue;

	head->weight = -1;

	tail->weight = 9999;

	head->link = tail;
	tail->link = NULL;

}

bool emptyQ(queue *head, queue *tail) {
	return head->link == tail;
}

void enQ(queue *head, queue *tail, char source, char dest, int weight) {
	queue *knew, *prior, *next;
	knew = new queue;
	
	knew->vSource = source;
	knew->vDest = dest;
	knew->weight = weight;

	prior = head;
	next = prior->link;

	while (next->weight <= weight && next != tail) {
		prior = prior->link;
		next = next->link;
	}

	prior->link = knew;
	knew->link = next;
}

edge deQ(queue *head, queue *tail) {
	queue *c;
	edge ans;
	
	if (!emptyQ(head, tail)) {
		c = head->link;

		ans.vDest = c->vDest;
		ans.vSource = c->vSource;
		ans.weight = c->weight;

		head->link = c->link;

		delete c;
		return ans;
	}
	else {
		cout << "The queue is empty" << endl;
		ans.vDest = '$';
		ans.vSource = '$';
		ans.weight = -1;
	}
	
}

void traverseQ(queue *head, queue *tail, ofstream &outFile, int step) {
	queue *c;
	
	c = head->link;
	if (!emptyQ(head, tail)) {

		outFile << "Step: " << step << endl;
		for (int i = 0; i < 10; i++) outFile << "-";
		outFile << endl;
		while (c != tail) {
			outFile << c->vDest << " <= " << c->vSource << " : " << c->weight - 48;
			c = c->link;
			outFile << endl;
		}
		for (int i = 0; i < 10; i++) outFile << "-";
		outFile << endl;
	}
	outFile << endl << endl;
}

void initColorArray(colors color[]) {
	for (int i = 'A'; i < matrixSize; i++) color[i] = white;
}

bool checkQueue(queue *head, queue *tail, edge target) {
	queue *prior, *c;
	bool isQueueable = false;
	
	prior = head;
	c = head->link;

	while (c->vDest != target.vDest && c != tail) {
		prior = c;
		c = c->link;
	}
	if (target.vDest == c->vDest){
		if (target.weight < c->weight) {
			prior->link = c->link;
			delete c;
			isQueueable = true;
		}
	}
	return isQueueable;
}

void printColors(queue *head, queue *tail, colors color[], ofstream &outFile) {
	if (!emptyQ(head, tail)) {
		for (int i = 'A'; i < matrixSize; i++)
			outFile << (char)i << " ";
		outFile << endl;
		for (int i = 'A'; i < matrixSize; i++) {
			colors currentColor = color[i];
			switch (currentColor) {
			case white:
				outFile << 'W' << " ";
				break;
			case gray:
				outFile << 'G' << " ";
				break;
			case black:
				outFile << 'B' << " ";
				break;
			}
		}
		outFile << endl << endl;
	}
}


void prims(queue *head, queue *tail, char adjArray[][matrixSize], colors color[], ofstream &outFile, char start) {
	edge edgeList[matrixSize - 66];
	int k = 0, MST = 0, step = 1;
	

	initColorArray(color);

	//EnQ start
	enQ(head, tail, 'X', start, 0);
	//color start -> gray
	color[start] = gray;
	//while not emptyQ
	while (!emptyQ(head, tail)) {
		//DeQ
		edge e = deQ(head, tail);
		color[e.vDest] = black;
		if (k < (matrixSize - 66) && e.vSource != 'X'){
			edgeList[k] = e;
			k++;
		}
		//Consider edges
		for (int i = 'A'; i < matrixSize; i++){
			if ((color[i] != black) && (adjArray[e.vDest][i] != '0') && (i != e.vDest)) {
				//EnQ valid edges
				edge checkE;
				checkE.vSource = e.vDest;
				checkE.vDest = (char)i;
				checkE.weight = adjArray[e.vDest][i];
				if (color[checkE.vDest] == gray) {
					if (checkQueue(head, tail, checkE))
						enQ(head, tail, e.vDest, (char)i, adjArray[e.vDest][i]);
				}
				else if (color[checkE.vDest] == white)
					enQ(head, tail, e.vDest, (char)i, adjArray[e.vDest][i]);
				//update colors
				color[i] = gray;
			}
		}
		traverseQ(head, tail, outFile, step);
		printColors(head, tail, color, outFile);
		step++;
	}//end loop

	outFile << "The minimum spanning tree for this graph starting from 'A' is: " << endl;

	for (int i = 0; i < (matrixSize - 66); i++) {
		MST += edgeList[i].weight - 48;
		outFile << edgeList[i].vDest << " <= " << edgeList[i].vSource << " : " << edgeList[i].weight - 48 << endl;
	}
	outFile << "Total: " << MST << endl;

}

void readEdgeList(char adjArray[][matrixSize]) {
	ifstream inFile("edgeList.dat");
	char i, j;
	int weight;

	while (!inFile.eof()) {
		inFile >> i >> j >> weight;
		adjArray[i][j] = weight + 48;
		adjArray[j][i] = weight + 48;
	}
}

void printAdjMatrix(char adjArray[][matrixSize], ofstream &outFile) {
	outFile << "   ";
	for (int i = 'A'; i < matrixSize; i++)
		outFile << left << setw(5) << (char)i;
	outFile << endl;
	for (int i = 0; i <= 65; i++) outFile << '=';
	outFile << endl;
	for (int i = 'A'; i < matrixSize; i++) {
		outFile << left << (char)i << " " << '|';
		for (int j = 'A'; j < matrixSize; j++) {
			outFile << setw(5) << adjArray[i][j];
		}
		outFile << endl;
	}
	outFile << endl << endl;
}

void printem() {

}

void initAdjArray(char adjArray[][matrixSize]) {
	for (int i = 'A'; i < matrixSize; i++) {
		for (int j = 'A'; j < matrixSize; j++) {
			if (i == j) adjArray[i][j] = 'X';
			else adjArray[i][j] = '0';
		}
	}
}

int main(int argc, char** argv) {
	char adjArray[matrixSize][matrixSize];
	ofstream outFile("output.ot");
	colors color[matrixSize];
	queue *head, *tail;

	createQueue(head, tail);

	initAdjArray(adjArray);
	printAdjMatrix(adjArray, outFile);
	readEdgeList(adjArray);
	printAdjMatrix(adjArray, outFile);

	prims(head, tail, adjArray, color, outFile, 'A');

	return 0;
}