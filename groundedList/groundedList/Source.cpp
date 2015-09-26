#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

struct listType{
	string last;
	string first;
	int id;
	listType* link;
};

void createList(listType *&head, listType *&tail)
{
	head = new listType;
	tail = new listType;

	head->last = ' AAA';
	tail->last = 'zzz';

	head->link = tail;
	tail->link = NULL;
}

bool emptyList(listType *head, listType *tail)
{
	return head->link == tail;
}

void printTitles(ofstream &outFile){
	for (int i = 0; i < 38; i++){
		outFile << "_";
	}
	outFile << endl;
	outFile << right << setw(5) << "ID" << setw(15) << " " << left << "Name" << endl;
	for (int i = 0; i < 38; i++){
		outFile << "_";
	}
	outFile << endl;
}

void printIt(ofstream &outFile, listType *head, listType *tail, listType *c){
	outFile << right << setw(5) << c->id << setw(15) << " " << left << c->first << " " << c->last << endl;
}

void traverseIt(ofstream &outFile, listType *head, listType *tail){

	bool isPrinted = false;
	listType *c;

	if (!isPrinted){
		printTitles(outFile);
		isPrinted = true;
	}
	c = head->link;
	if (!emptyList(head, tail)){
		while (c != tail){
			printIt(outFile, head, tail, c);
			c = c->link;
		}
		outFile << endl;
	}
	else cout << "This list is empty!" << endl;
}

void insertToList(listType *head, listType *tail, string last, string first, int id){
	listType *knew, *prior, *next;
	knew = new listType;
	knew->last = last;
	knew->first = first;
	knew->id = id;
	prior = head;
	next = head->link;
	while (next != tail && next->last < last){
		prior = next;
		next = next->link;
	}
	prior->link = knew;
	knew->link = next;
}

void readIt(listType *head, listType *tail)
{
	ifstream inFile("input.dat");
	string last, first;
	int id = 0;
	while (!inFile.eof()){
		inFile >> last >> first >> id;
		last[last.length() - 1] = ' ';
		insertToList(head, tail, last, first, id);
	}

}

void deleteIt(ofstream &outFile, listType *head, listType *tail, string last){
	listType *prior, *next, *c;
	prior = head;
	c = head->link;
	last += " ";
	while (c != tail && c->last < last){
		prior = c;
		c = c->link;
	}
	if (c->last == last){
		next = c->link;
		prior->link = next;
		cout << c->first << " " << c->last << "has been deleted from this list." << endl;
		outFile << c->first << " " << c->last << "has been deleted from this list." << endl;
		delete c;
	}
	else cout << "That item is not in the list!" << endl;

}

void main(){
	ofstream outFile("output.txt");
	listType *head, *tail;

	createList(head, tail);
	readIt(head, tail);
	traverseIt(outFile, head, tail);
	deleteIt(outFile, head, tail, "Solo");
	traverseIt(outFile, head, tail);
	insertToList(head, tail, "Skywalker", "Luke", 333);
	traverseIt(outFile, head, tail);
}
