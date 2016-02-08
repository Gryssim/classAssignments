#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

const int pantrySize = 50;
const int recipeSize = 100;

enum mealType { breakfast, lunch, dinner, snack, invalid };
enum dayOfWeek { monday, tuesday, wednesday, thursday, friday, saturday, sunday, NaD };


//Structure to include pantry items
          
struct pantryItem{
	string ingredient = "zzNaN";
	double quant = -1, weight = -1;
	int perItemQuant = -1;
	bool isScalable = true;
};

struct recipeItem{
	mealType meal = invalid;
	string recipeName = "zzNaN";
	pantryItem ingredient[10];
};

struct dayWithMeals{
	dayOfWeek day;
	recipeItem b;
	recipeItem l;
	recipeItem d;
};

string dayOfWeekToString(dayOfWeek day){
	string ans;

	if (day == monday)
		ans = "Monday";
	else if (day == tuesday)
		ans = "Tuesday";
	else if (day == wednesday)
		ans = "Wednesday";
	else if (day == thursday)
		ans = "Thursday";
	else if (day == friday)
		ans = "Friday";
	else if (day == saturday)
		ans = "Saturday";
	else if (day == sunday)
		ans = "Sunday";
	else
		ans = "NaD";

	return ans;
}

dayOfWeek stringToDayOfWeek(string day){
	dayOfWeek ans;

	if (day == "Monday")
		ans = monday;
	else if (day == "Tuesday")
		ans = tuesday;
	else if (day == "Wednesday")
		ans = wednesday;
	else if (day == "Thursday")
		ans = thursday;
	else if (day == "Friday")
		ans = friday;
	else if (day == "Saturday")
		ans = saturday;
	else if (day == "Sunday")
		ans = sunday;
	else
		ans = NaD;

	return ans;
}

string mealTypeToString(mealType meal){
	string ans;

	if (meal == breakfast)
		ans = "breakfast";
	else if (meal == lunch)
		ans = "lunch";
	else if (meal == dinner)
		ans = "dinner";
	else if (meal == snack)
		ans = "snack";
	else
		ans = "invalid";

	return ans;
}

mealType stringToMealType(string str){
	mealType ans;

	if (str == "breakfast")
		ans = breakfast;
	else if (str == "lunch")
		ans = lunch;
	else if (str == "dinner")
		ans = dinner;
	else if (str == "snack")
		ans = snack;
	else
		ans = invalid;

	return ans;
}

// swap template.

template <class type>
void swapIt(type &a, type &b){
	type temp;
	temp = b;
	b = a;
	a = temp;
}

// Sort Pantry inventory alphabetically. 

void pantryBubSort(pantryItem a[]){
	for (int i = 0; i < pantrySize - 1; i++){
		for (int j = 0; j < pantrySize - i - 1; j++){
			if (a[j].ingredient > a[j + 1].ingredient) swapIt<pantryItem>(a[j], a[j + 1]);
		}
	}
	

}

// Sort recipes by mealType, leaving breakfast or 0 as top element. 

void recipeBubSort(recipeItem a[]){
	for (int i = 0; i < recipeSize - 1; i++){
		for (int j = 0; j < recipeSize - i - 1; j++)
			if (a[j].meal > a[j + 1].meal) swapIt<recipeItem>(a[j], a[j + 1]);
	}
}

// Replace underscore spacing from string with blank.

void replaceUnderscore(string &str){
	char ch;

	for (int i = 0; i < str.length(); i++){
		ch = str[i];
		if (ch == '_'){
			str = str.substr(0, i) + " " + str.substr(i + 1, str.length());
		}
	}
}

// Convert string to Title Case. First character is capatalized,
// and any character after a blank.

void titleCase(string &str){
	char ch;

	str[0] -= 32;
	for (int i = 0; i < str.length(); i++){
		ch = str[i];
		if (ch == ' '){
			str[i + 1] -= 32;
		}
	}
}

//Read in inventory from file. 

void readPantryInventory(pantryItem pantry[]){
	ifstream inFile("pantryInventory.dat");
	int i = 0;

	while (!inFile.eof()){
		inFile >> pantry[i].ingredient >> pantry[i].quant;
		if (pantry[i].ingredient == "butter")
			pantry[i].isScalable = false;
		replaceUnderscore(pantry[i].ingredient);
		titleCase(pantry[i].ingredient);
		i++;
		pantryBubSort(pantry);

	}
	inFile.close();
}


void displayPantryInventory(pantryItem pantry[]){
	bool endOfPantry = false;
	int i = 0;

	while (endOfPantry == false){
		if (pantry[i].ingredient != "zzNaN"){
			cout << left << setw(20) << pantry[i].ingredient << " " << pantry[i].quant << endl;
			i++;
		}
		else
			endOfPantry = true;
		
	}
}
//print updated or altered inventory to source.

void updatePantryInventory(){

}

void readRecipe(recipeItem recipes[]){
	ifstream inFile;
	inFile.open("recipeMaster.dat");
	int i = 0, j = 0;
	string m, name;
	double qua;

	
	while (inFile){
		inFile >> m;
		inFile >> name;
		recipes[i].meal = stringToMealType(m);
		recipes[i].recipeName = name;
		replaceUnderscore(recipes[i].recipeName);
		m = "";
		name = "";
		for (int j = 0; j < 10; j++){
			inFile >> qua >> ws;
			if (qua != -1){
				recipes[i].ingredient[j].quant = qua;
				inFile >> recipes[i].ingredient[j].ingredient >> ws;
				replaceUnderscore(recipes[i].ingredient[j].ingredient);
				titleCase(recipes[i].ingredient[j].ingredient);
			}
			else
				j = 10;
		}

		i++;
	}

	recipeBubSort(recipes);
}

void displayRecipe(recipeItem recipes[]){
	bool endOfRecipes = false;
	int i = 0;

	while (endOfRecipes == false){
		if (recipes[i].meal != invalid){
			cout << left << recipes[i].recipeName << endl << endl;
			for (int j = 0; j < 10; j++){
				if (recipes[i].ingredient[j].quant != -1){
					cout << left << setw(15) << recipes[i].ingredient[j].quant
						<< recipes[i].ingredient[j].ingredient << endl;
				}
				else
					j = 10;
			}
			cout << endl << endl;
		}
		else
			endOfRecipes = true;
		i++;
	}
}

//Set a recipe to each meal of the day. Count ingredients and output to file. 

void planMeals(recipeItem recipes[], pantryItem pantry[]){
	ofstream outFile("shopList.txt");
	dayWithMeals week[sunday + 1];
	recipeItem recipePerMealType[5]; 
	pantryItem shoppingNeed[pantrySize];
	char confirm;

	cout << "\n\nLet's plan your week. We will step through each day and each meal where you can select a meal from your recipe list based on its meal type." << endl;

	// Move from monday to sunday and determine enum type mealType
	// to determine meal and recipe attached. 
	for (int i = monday; i <= sunday; i++){
		week[i].day = (dayOfWeek)i;
		week[i].b.meal = breakfast;
		week[i].l.meal = lunch;
		week[i].d.meal = dinner;
		cout << "\n\n" << dayOfWeekToString(week[i].day);
		for (int j = 0; j < 3; j++){
			int k = 0;
			int count = 1;
			int userChoice;
			recipeItem recipeChoice[6];

			cout << "\n\nMake a selection for " << mealTypeToString((mealType)j) << endl;
			while (recipes[k].recipeName != "zzNaN"){
				

				if (recipes[k].meal == (mealType)j){
					cout << count << " " << recipes[k].recipeName << endl;
					recipeChoice[count] = recipes[k];
					count++;
				}
				k++;

			}
			cin >> userChoice;

			switch (userChoice){
			case 1:
				if ((mealType)j == breakfast)
					week[i].b = recipeChoice[userChoice];
				else if ((mealType)j == lunch)
					week[i].l = recipeChoice[userChoice];
				else
					week[i].d = recipeChoice[userChoice];
				break;
			case 2:
				if ((mealType)j == breakfast)
					week[i].b = recipeChoice[userChoice];
				else if ((mealType)j == lunch)
					week[i].l = recipeChoice[userChoice];
				else
					week[i].d = recipeChoice[userChoice];
				break;
			case 4:
				if ((mealType)j == breakfast)
					week[i].b = recipeChoice[userChoice];
				else if ((mealType)j == lunch)
					week[i].l = recipeChoice[userChoice];
				else
					week[i].d = recipeChoice[userChoice];
				break;
			case 5:
				if ((mealType)j == breakfast)
					week[i].b = recipeChoice[userChoice];
				else if ((mealType)j == lunch)
					week[i].l = recipeChoice[userChoice];
				else
					week[i].d = recipeChoice[userChoice];
				break;
			case 6:
				if ((mealType)j == breakfast)
					week[i].b = recipeChoice[userChoice];
				else if ((mealType)j == lunch)
					week[i].l = recipeChoice[userChoice];
				else
					week[i].d = recipeChoice[userChoice];
				break;
			default:
				cout << "Invalid choice" << endl;
				break;
			}
		}

	}


	do{
		cout << "Your weeks selections is as follows: " << endl;
		for (int i = monday; i < NaD; i++){
			cout << dayOfWeekToString(week[i].day) << endl << endl << mealTypeToString(week[i].b.meal) << endl << week[i].b.recipeName
				<< endl << endl << mealTypeToString(week[i].l.meal) << endl << week[i].l.recipeName << endl << endl <<
				mealTypeToString(week[i].d.meal) << endl << week[i].d.recipeName << endl << endl;
			
			//Compare recipe ingredient week[i].b/l/d.ingredient against pantry name, if found get difference.
			for (int j = 0; j < pantrySize; j++){
				for (int k = 0; k < pantrySize; k++){
					if (week[i].b.ingredient[k].ingredient == pantry[j].ingredient)
						shoppingNeed[j].ingredient = pantry[j];
					if (week[i].l.ingredient[k].ingredient == pantry[j].ingredient)
						shoppingNeed[j] = pantry[j];
					if (week[i].d.ingredient[k].ingredient == pantry[j].ingredient)
						shoppingNeed[j] = pantry[j];
				}
			}
			//if difference is >= 0, continue;

			//if difference < 0 shoppingNeed[i].ingredient/quant = ingredient/quant as absolute value of difference.

		}
		cout << "\n\nIs this correct? (y/n)";

		cin >> confirm;
		tolower(confirm);
		if (confirm != 'y' && confirm != 'n'){
			cout << "Please enter either 'y' for yes, or 'n' for no." << endl;
			system("pause");
		}
		
	} while (confirm != 'y');
}


//display main menu

void mainMenu(pantryItem pantry[], recipeItem recipes[]){
	int userChoice = 0;

	do{
		cout << endl;
		cout << "*==============================================================================*" << endl;
		cout << "*                         Digital Pantry Prototype 0.01                        *" << endl;
		cout << "* Display Pantry     1                                                         *" << endl;
		cout << "* Display Recipes    2                                                         *" << endl;
		cout << "* Plan Weeks Meals   3                                                         *" << endl;
		cout << "* Not Available      4                                                         *" << endl;
		cout << "* Quit               5                                                         *" << endl;
		cout << "*==============================================================================*" << endl;

		cout << "Please choose an option above: " << endl;
		cin >> userChoice;

		switch (userChoice){
		case 1:
			displayPantryInventory(pantry);
			system("pause");
			break;
		case 2:
			displayRecipe(recipes);
			system("pause");
			break;
		case 3:
			planMeals(recipes, pantry);
			system("pause");
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			cout << "Invalid selection, please choose an option above: ";
		}
	} while (userChoice != 5);


}


void main(){
	pantryItem pantry[pantrySize];
	recipeItem recipes[recipeSize];

	readPantryInventory(pantry);
	readRecipe(recipes);

	mainMenu(pantry, recipes);

}