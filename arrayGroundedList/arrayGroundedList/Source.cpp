#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

const int maxList = 50;

struct listType{
	string last;
	string first;
	int id;
};

const listType initrec = { "n/a", "n/a", -1 };

void createList(listType list[], int &numList){
	int i;
	for (i = 0; i < maxList; i++) list[i] = initrec;
		numList = 0;
}

bool emptyList(int numList){
	return numList <= 0;
}

bool fullList(int numList){
	return numList >= maxList;
}

void printTitles(ofstream &outFile){
	for (int i = 0; i < 27; i++){
		outFile << "=";
	}
	outFile << endl;
	outFile << right << setw(5) << "ID" << setw(5) << " " << left << "Name" << endl;
	for (int i = 0; i < 27; i++){
		outFile << "=";
	}
	outFile << endl;
}

void printIt(ofstream &outFile, listType list[], int i){
	outFile << right << setw(5) << list[i].id << setw(5) << " " << left << list[i].first << " " << list[i].last << endl;
}

void traverseIt(ofstream &outFile, listType list[], int numList){
	int i;
	bool isPrinted = false;

	if (!emptyList(numList)){
		if (!isPrinted){
			printTitles(outFile);
			isPrinted = true;
		}
		for (i = 0; i < numList; i++){
			printIt(outFile, list, i);
		}
		outFile << endl;
	}

	else cout << "This list is empty!" << endl;
}

void insertToList(listType list[], int &numList, string last, string first, int id){
	int i, where;

	if (!fullList(numList)){
		where = 0;
		while (where < numList && list[where].last < last) where++;
		for (i = numList; i > where; i--){
			list[i] = list[i-1];
		}
		list[where].last = last;
		list[where].first = first;
		list[where].id = id;
		numList++;
	}
	else cout << "This list is full." << endl;

}

void readIt(listType list[], int &numList)
{
	ifstream inFile("input.dat");
	string last, first;
	int id = 0;
	while (!inFile.eof()){
		inFile >> last >> first >> id;
		last.erase(last.length() - 1, 1);
		insertToList(list, numList, last, first, id);
	}

}


void deleteIt(ofstream &outFile, listType list[], int &numList, string last){
	int i, where;
	where = 0;
	if (!fullList(numList)){
		while (where < numList && list[where].last < last) where++;
		if (list[where].last == last){
			cout << list[where].first << " " << list[where].last << " has been deleted from this list." << endl;
			outFile << list[where].first << " " << list[where].last << " has been deleted from this list." << endl;
			for (i = where; i <= numList; i++){
				list[i] = list[i + 1];
			}
			numList--;
		}
		else cout << "That item is not in the list!" << endl;
	}
	else cout << "This list is empty!" << endl;
}

void main(){
	ofstream outFile("output.txt");
	int numList;
	listType list[maxList];



	createList(list, numList);
	readIt(list, numList);
	traverseIt(outFile, list, numList);
	deleteIt(outFile, list, numList, "Solo");
	traverseIt(outFile, list, numList);
	insertToList(list, numList, "Skywalker", "Luke", 333);
	traverseIt(outFile, list, numList);
}
