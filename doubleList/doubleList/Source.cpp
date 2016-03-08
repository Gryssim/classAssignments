#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct doubly {
	int id;
	string firstName, lastName;
	doubly *linkName;
	doubly *linkId;
};

void createList(doubly *head, doubly *tail){
	
	head->id = -1;
	head->lastName = " AA";
	tail->id = 99999;
	tail->lastName = "zzz";

	head->linkName = tail;
	head->linkId = tail;

	tail->linkName = NULL;
	tail->linkId = NULL;

}

string removeComma(string str) {
	return str.substr(0, str.length() - 1);
}

// Insert to list, search ID position first, then name.

void insertList(doubly *head, doubly *tail, int id, string lastName, string firstName) {
	doubly *knew, *priorId, *cId;
	doubly *priorName, *cName;
	
	knew = new doubly;
	knew->id = id;
	knew->lastName = lastName;
	knew->firstName = firstName;

	priorId = head;
	cId = head->linkId;
	while (cId != tail && knew->id > cId->id) {
		priorId = priorId->linkId;
		cId = cId->linkId;
	}
	priorId->linkId = knew;
	knew->linkId = cId;

	priorName = head;
	cName = head->linkName;
	while (cName != tail && knew->lastName > cName->lastName) {
		priorName = priorName->linkName;
		cName = cName->linkName;
	}
	priorName->linkName = knew;
	knew->linkName = cName;
}

// Overloaded insert to account for manual input with message.

void insertList(doubly *head, doubly *tail, int id, string lastName, string firstName, int manual, ofstream &outFile) {
	
	if (manual >= 1) {
		doubly *knew, *priorId, *cId;
		doubly *priorName, *cName;

		knew = new doubly;
		knew->id = id;
		knew->lastName = lastName;
		knew->firstName = firstName;

		priorId = head;
		cId = head->linkId;
		while (cId != tail && knew->id > cId->id) {
			priorId = priorId->linkId;
			cId = cId->linkId;
		}
		priorId->linkId = knew;
		knew->linkId = cId;

		priorName = head;
		cName = head->linkName;
		while (cName != tail && knew->lastName > cName->lastName) {
			priorName = priorName->linkName;
			cName = cName->linkName;
		}
		priorName->linkName = knew;
		knew->linkName = cName;

		outFile << firstName << " " << lastName << " has been added to the list." << endl << endl;
	}
}

void readList(doubly *head, doubly *tail) {
	ifstream inFile("input.dat");
	string lastName, firstName;
	int id;

	while (!inFile.eof()) {
		inFile >> id;
		inFile >> lastName >> firstName;
		

		insertList(head, tail, id, removeComma(lastName), firstName);
	}
}


void deleteList(doubly *head, doubly *tail, string lastName, int id, ofstream &outFile) {
	doubly *prior, *c;
	
	prior = head;
	c = prior->linkName;

	while (c->lastName != lastName && c != tail) {
		prior = c;
		c = c->linkName;
	}

	if (c->id == id && c->lastName == lastName) {
		prior->linkName = c->linkName;

		prior = head;
		c = prior->linkId;

		while (c->id != id || c->lastName != lastName) {
			prior = c;
			c = c->linkId;
		}
		if (c->id == id && c->lastName == lastName)
			prior->linkId = c->linkId;

		outFile << c->firstName << " " << c->lastName << " has been deleted from the list." << endl << endl;

		delete c;
	}
	else
		outFile << "No such item in list" << endl << endl;

}

void printTitles(ofstream &outFile) {
	
	outFile << left << setw(10) << "F.Name" << setw(10) << "L.Name" << setw(6) << "ID" << endl;

	for (int i = 0; i < 24; i++) {
		outFile << '=';
	}

	outFile << endl;
}

void travAlpha(doubly *head, doubly *tail, ofstream &outFile) {
	doubly *c;

	printTitles(outFile);

	c = head->linkName;
	while (c != tail) {
		outFile << setw(10) << left << c->lastName << setw(10) << c->firstName << setw(6) << c->id << endl;
		c = c->linkName;
	}
	outFile << endl << endl;
}

void travNum(doubly *head, doubly *tail, ofstream &outFile) {
	doubly *c;

	printTitles(outFile);

	c = head->linkId;
	while (c != tail) {
		outFile << setw(10) << left << c->lastName << setw(10) << c->firstName << setw(6) << c->id << endl;
		c = c->linkId;
	}
	outFile << endl << endl;
}

// Returns true if list is empty (Either of head's link point to tail.)

bool emptyList(doubly *head, doubly *tail) {
	
	return (head->linkName == tail);
}


void main() {
	doubly *head, *tail;
	ofstream outFile("output.ot");

	head = new doubly;
	tail = new doubly;

	createList(head, tail);
	readList(head, tail);

	travAlpha(head, tail, outFile);
	travNum(head, tail, outFile);

	deleteList(head, tail, "Solo", 7234, outFile);

	deleteList(head, tail, "Sl", 722, outFile);
	travAlpha(head, tail, outFile);
	
	insertList(head, tail, 8888, "Payne", "L.", 1, outFile);
	travAlpha(head, tail, outFile);

}