#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <math.h>

using namespace std;

#include "ratNum.h"

ratNum::ratNum(){
	nom = 0;
	denom = 1;
}

ratNum::ratNum(int inNom, int inDenom){
	if (inDenom == 0){
		nom = -9999;
		denom = 1;
	}
	else {
		nom = inNom;
		denom = inDenom;
	}
}

void ratNum::printIt(ofstream &outFile){
	outFile << "Nominator = " << nom << " Denominator = " << denom << endl << endl;
}

void ratNum::setNom(int inNom){
	nom = inNom;
}

void ratNum::setDenom(int inDenom){
	if (inDenom == 0){
		denom = -9999;
	}
	else{
		denom = inDenom;
	}
}

int ratNum::getNom(){
	return nom;
}

int ratNum::getDenom(){
	return denom;
}

ratNum ratNum::reduceIt(){
	ratNum ans;
	int min = getMin();
	
	if (denom < 0){
		nom *= -1;
		denom *= -1;
	}
	ans.nom = nom;
	ans.denom = denom;

	for (int i = abs(min); i > 1; i--){

		if ((abs(ans.nom) % i == 0) && (abs(ans.denom) % i == 0)){
			ans.nom /=  i;
			ans.denom /=  i;
		}

	}

	return ans;
}

int ratNum::getMin(){
	int ans;
	if (abs(nom) < abs(denom))
		ans = abs(nom);
	else
		ans = abs(denom);

	return ans;
}

ratNum operator *(ratNum one, ratNum two){
	ratNum ans;
	ans.nom = one.nom * two.nom;
	ans.denom = one.denom * two.denom;


	return ans.reduceIt();
}

ratNum operator /(ratNum one, ratNum two){
	ratNum ans;
	if (two.nom == 0){
		ans.nom = -9999;
		ans.denom = 1;
	}
	else {
		ans.nom = one.nom * two.denom;
		ans.denom = one.denom * two.nom;
	}

	return ans.reduceIt();
}

ratNum operator -(ratNum one, ratNum two){
	ratNum ans;
	
	ans.nom = (one.nom*two.denom) - (two.nom*one.denom);
	ans.denom = one.denom*two.denom;

	return ans.reduceIt();
}

ratNum operator +(ratNum one, ratNum two){
	ratNum ans;

	ans.nom = (one.nom*two.denom) + (two.nom*one.denom);
	ans.denom = one.denom*two.denom;
	
	return ans.reduceIt();
}

istream& operator >>(istream &inFile, ratNum& one){
	char ch;
	if (one.denom == 0){
		return inFile;
	}
	else{
		inFile >> one.nom >> ch >> one.denom;
		one.reduceIt();
	}
	
	return inFile;
}

ostream& operator <<(ostream &outFile, ratNum& one){
	if (abs(one.nom) == (one.denom)){
		if (one.nom < 0 && one.denom < 0){
			outFile << 1;
		}
		else if (one.nom < 0 || one.denom < 0){
			outFile << -1;
		}
		else{
			outFile << 1;
		}
	}
	
	else if (one.nom == 0){
		outFile << 0;
	}

	else if (one.denom > 1){
		outFile << one.nom << "/" << one.denom;
	}

	else{
		outFile << one.nom;
	}
	return outFile;
}