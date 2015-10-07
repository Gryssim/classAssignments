#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int INITVAL = 0;
const int ITEMPERLINE = 4;
int itemCount = 0;

struct treeType {
	string word;
	int count;
	treeType *left, *right;
};

void toLower(string &word){
	int i, ch;
	for (i = 0; i < word.length(); i++){
		if (word[i] >= 'A' && word[i] <= 'Z'){
			ch = word[i];
			ch += 32;
			word[i] = ch;
		}
	}
}

void createTree(treeType *&root){
	root = new treeType;
	
	root->word = "";
	root->count = INITVAL;
	
	root->left = NULL;
	root->right = NULL;
	
}

bool emptyTree(treeType *root){
	return root->count < 1;
}

void cleanup(string &word){
	string dummy;
	int i = 0;
	dummy = "";
	while (i < word.length()){
		if (word[i] >= 'a' && word[i] <= 'z'){
			dummy += word[i];
		}
		i++;
	}
	word = dummy;
}

void printIt(treeType *c, ofstream &outFile){

	int i;
	bool isFirst = false;
	if (itemCount == 0) isFirst = true;

	if (isFirst){
		for (i = 0; i < ITEMPERLINE; i++){
			outFile << left << setw(14) << "Word" << setw(12) << "Count";
		}
		outFile << endl;
		for (i = 0; i < 98; i++){
			outFile << "=";
		}
		outFile << endl;
		isFirst = false;
	}

	if (itemCount < 3){
		outFile << left << setw(14) << c->word << setw(12) << c->count;
		itemCount++;
	}
	else {
		outFile << left << setw(14) << c->word << setw(12) << c->count;
		itemCount = 0;
		outFile << endl << endl;
	}

}

void insertTree(treeType *root, string word){
	treeType *knew, *parent, *c;
	parent = NULL;
	c = root;
	if (!emptyTree(root)){
		while (c != NULL && c->word != word){
			parent = c;
			if (word < c->word){
				c = c->left;
			}
			else
				c = c->right;
		}
		if (c != NULL)
			c->count++;
		else{
			knew = new treeType;
			knew->word = word;
			knew->count = 1;
			knew->left = NULL;
			knew->right = NULL;


			if (word < parent->word)
				parent->left = knew;
			else
				parent->right = knew;
		}
	}
	else{
		root->word = word;
		root->count++;
	}
}	

void readIn(treeType *root){
	ifstream inFile("input.dat");
	string word;

	while (!inFile.eof()){
		inFile >> word;
		toLower(word);
		cleanup(word);
		if (word.length() > 0) insertTree(root, word);

	}
}


void preOrderTrav(treeType *c, ofstream &outFile){
	cout << c->word;
	printIt(c, outFile);
	if (c->left != NULL) preOrderTrav(c->left, outFile);
	if (c->right != NULL) preOrderTrav(c->right, outFile);
}

void inOrderTrav(treeType *c, ofstream &outFile){
	if (c->left != NULL) inOrderTrav(c->left, outFile);
	cout << c->word << " " << c->count << endl;
	printIt(c, outFile);
	if (c->right != NULL) inOrderTrav(c->right, outFile);
}

void postOrderTrav(treeType *c, ofstream &outFile){
	if (c->left != NULL) postOrderTrav(c->left, outFile);
	if (c->right != NULL) postOrderTrav(c->right, outFile);
	cout << c->word;
	printIt(c, outFile);
}

void main(){
	ofstream outFile("output.txt");
	treeType *root;

	createTree(root);
	readIn(root);

	inOrderTrav(root, outFile);
}