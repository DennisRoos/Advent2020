#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <chrono> 
#include <sstream>
using namespace std;
using namespace std::chrono;

struct rule {
	int content;
	vector<int> amount;
	vector<int> contains;
	bool hasgold;
	rule() :  hasgold(false), content(-1) {}
};

vector<rule> rules;
vector<string> names;

int getnumber(string s) {
	int i;
	for (i = 0; i < names.size(); i++) {
		if (names[i].compare(s) == 0) {
			return i;
		}
	}
	names.push_back(s);
	rule r = rule();
	rules.push_back(r);
	return i;
}

void findgold(int n) {
	for (int i = 0; i < rules.size(); i++) {//find rules containing this color n
		if (rules[i].hasgold == false) {
			for (int j = 0; j < rules[i].contains.size(); j++) {
				if (rules[i].contains[j] == n) {//found a bag containing n!
					rules[i].hasgold = true;
					findgold(i);
				}
			}
		}
	}
	return;
}

int bagcontains(int i) {//returns how many bags the bag contains
	int total = 0;
	if (rules[i].content != -1) {//already counted how many bags are in here, just return that
		return rules[i].content;
	}
	for (int j = 0; j < rules[i].contains.size(); j++) {
		total += rules[i].amount[j] * (bagcontains(rules[i].contains[j]) + 1);
	}
	rules[i].content = total;
	return total;
}

int main()
{
	ifstream f("data.txt");
	string s;
	string in1;
	string in2;
	string temp;
	int am;
	getnumber("shiny gold");
	while (getline(f, s)) {
		istringstream iss(s);
		iss >> in1;
		iss >> in2;
		in1.append(" ");
		in1.append(in2);
		int number = getnumber(in1);
		iss >> temp;
		iss >> temp;
		iss >> temp;
		if (temp.compare("no") != 0) {
			am = stoi(temp);
			iss >> in1;
			iss >> in2;
			in1.append(" ");
			in1.append(in2);
			rules[number].amount.push_back(am);
			int n = getnumber(in1);
			rules[number].contains.push_back(n);
			iss >> temp;
			while (iss >> am) {
				iss >> in1;
				iss >> in2;
				in1.append(" ");
				in1.append(in2);
				rules[number].amount.push_back(am);
				int n = getnumber(in1);
				rules[number].contains.push_back(n);
				iss >> temp;
			}
		}
	}

	/*for (int i = 0; i < names.size(); i++) {
		cout << i << ": " << names[i] << endl;
	}
	for (int i = 0; i < rules.size(); i++) {
		cout << "rule " << i << ": ";
		for (int j = 0; j < rules[i].amount.size(); j++) {
			cout << rules[i].amount[j] << " of " << rules[i].contains[j] << " , ";
		}
		cout << endl;
	}*/



	findgold(0);

	int totalgold = 0;
	for (int i = 0; i < rules.size(); i++) {
		if (rules[i].hasgold) {
			totalgold++;
		}
	}
	cout << "The amount of bags containing shiny gold is " << totalgold << endl;
	cout << "The shiny gold bag contains " << bagcontains(0) << " other bags" << endl;

}
