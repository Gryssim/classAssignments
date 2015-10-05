#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int INITVAL = 1;

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
	return root->count < INITVAL;
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
	else
		root->word = word;
}

void readIn(treeType *root){
	ifstream inFile("input.dat");
	string word;

	while (!inFile.eof()){
		inFile >> word;
		toLower(word);
		cleanup(word);
		if (word.length() >= 1) insertTree(root, word);

	}
}


void preOrderTrav(treeType *c){
	cout << c->word;
	if (c->left != NULL) preOrderTrav(c->left);
	if (c->right != NULL) preOrderTrav(c->right);
}

void inOrderTrav(treeType *c){
	if (c->left != NULL) inOrderTrav(c->left);
	cout << c->word << " " << c->count << endl;
	if (c->right != NULL) inOrderTrav(c->right);
}

void postOrderTrav(treeType *c){
	if (c->left != NULL) postOrderTrav(c->left);
	if (c->right != NULL) postOrderTrav(c->right);
	cout << c->word;
}

void main(){
	treeType *root;

	createTree(root);
	readIn(root);

	inOrderTrav(root);
}