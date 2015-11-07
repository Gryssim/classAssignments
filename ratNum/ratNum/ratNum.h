class ratNum{
private:
	int nom, denom;
public:
	ratNum();
	ratNum(int inNom, int inDenom);
	void printIt(ofstream &outFile);
	void setNom(int inNom);
	void setDenom(int inDenom);
	int getNom();
	int getDenom();
	ratNum reduceIt();
	int getMin();

	friend ratNum operator *(ratNum one, ratNum two);
	friend ratNum operator /(ratNum one, ratNum two);
	friend istream& operator >>(istream &inFile, ratNum& one);
	friend ostream& operator <<(ostream &outFile, ratNum& one);
	friend ratNum operator -(ratNum one, ratNum two);
	friend ratNum operator +(ratNum one, ratNum two);

};

ratNum operator *(ratNum one, ratNum two);
ratNum operator /(ratNum one, ratNum two);

ratNum operator -(ratNum one, ratNum two);
ratNum operator +(ratNum one, ratNum two);

istream& operator >>(istream &inFile, ratNum& one);
ostream& operator <<(ostream &outFile, ratNum& one);