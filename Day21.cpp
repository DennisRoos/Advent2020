#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include <cmath>

using namespace std;

vector<string> ingredientnames;
vector<int> allInFood;
vector<string> namesofingredients;

struct food {
	vector<int> ing;
	vector<int> all;
	food() {};
};

struct allergen {
	vector<int> w;
	string name;
	string ingredient;
	allergen(string n) : name(n) {}
};

vector<food> F;
vector<allergen> v;

int addIngredient(string n) {
	for (int i = 0; i < ingredientnames.size(); i++) {
		if (n.compare(ingredientnames[i]) == 0) {
			return i;
		}
	}
	ingredientnames.push_back(n);
	allInFood.push_back(-1);
	namesofingredients.push_back(n);
	return ingredientnames.size() - 1;
}


int addAllergen(string n) {
	for (int i = 0; i < v.size(); i++) {
		if (n.compare(v[i].name) == 0) {
			return i;
		}
	}
	allergen a = allergen(n);
	v.push_back(a);
	return v.size() - 1;
}


struct less_than_angle
{
	inline bool operator() (const allergen& a1, const allergen& a2)
	{
		return a1.name < a2.name;
	}
};

int main(int argc, char * argv[]) {
	ifstream f("data.txt");
	string s;
	while(getline(f, s)){
		istringstream iss(s);
		string s2;
		iss >> s2;
		food newfood = food();
		while (s2.compare("(contains") != 0) {
			int num = addIngredient(s2);
			newfood.ing.push_back(num);
			iss >> s2;
		}
		while (iss >> s2) {
			int num = addAllergen(s2);
			newfood.all.push_back(num);
			if (v[num].w.size() == 0) {//new allergen
				for (int i = 0; i < newfood.ing.size(); i++) {
					v[num].w.push_back(newfood.ing[i]);
				}
			}
			else {//we intersect the already existing set of ingredients for this allergen with the ingredients in this food
				
				for (int j = 0; j < v[num].w.size(); j++) {
					bool b = true;
					for (int i = 0; i < newfood.ing.size(); i++) {
						if (v[num].w[j] == newfood.ing[i]) {//ingredient j is in both sets
							b = false;
						}
					}
					if (b) {
						v[num].w.erase(v[num].w.begin() + j);//this ingredient wasn't in this food, so it can't be the source of the allergen
						j--;
					}
				}
			}
		}
		F.push_back(newfood);
	}


	int count = v.size();
	while (count > 0) {
		for (int i = 0; i < v.size(); i++) {
			if (v[i].w.size() == 1) {//only one remaining candidate for the source of allergen i left
				int ing = v[i].w[0];
				allInFood[ing] = i;
				v[i].ingredient.assign(namesofingredients[ing]);
				count--;
				for (int j = 0; j < v.size(); j++) {
					for (int k = 0; k < v[j].w.size(); k++) {
						if (v[j].w[k] == ing) {
							v[j].w.erase(v[j].w.begin() + k);
						}
					}
				}
				cout << "Ingredient " << v[i].ingredient << " is the source of allergen " << v[i].name << endl;
			}
		}
	}

	//now to count all the ingredients that don't have allergens
	int total = 0;
	for (int i = 0; i < F.size(); i++) {
		for (int j = 0; j < F[i].ing.size(); j++) {
			if (allInFood[F[i].ing[j]] == -1) {
				total++;
			}
		}
	}

	cout << endl << "There were " << total << " ingredients without allergens in them\n\n";

	sort(v.begin(), v.end(), less_than_angle());
	string dangerlist;
	dangerlist.assign(v[0].ingredient);
	for (int i = 1; i < v.size(); i++) {
		dangerlist.append(",");
		dangerlist.append(v[i].ingredient);
	}
	cout << "The Canonical Dangerous Ingredient List is: " << endl << dangerlist << endl;
	return 0;
}