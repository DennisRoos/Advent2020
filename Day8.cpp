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

vector<int> ops;
vector<int> args;
vector<bool> visited;


int acc;

bool runprogram(){
	int ip = 0;
	acc = 0;
	for (int i = 0; i < visited.size(); i++) {
		visited[i] = false;
	}
	while (ip < ops.size() && ip >= 0) {
		if (visited[ip]) {
			return false;
		}
		visited[ip] = true;
		if (ops[ip] == 0) {
			acc += args[ip];
			ip++;
		}
		else if (ops[ip] == 1) {
			ip += args[ip];
		}
		else {
			ip++;
		}
	}
	return true;
}

int main()
{
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		int n;
		while (infile >> s) {
			infile >> n;
			args.push_back(n);
			visited.push_back(false);
			if (s.compare("acc") == 0) {
				ops.push_back(0);
			}
			else if (s.compare("jmp") == 0) {
				ops.push_back(1);
			}
			else if (s.compare("nop") == 0) {
				ops.push_back(2);
			}
		}
		runprogram();
		cout << "The accumulator is at " << acc << " at the first repeat, for part 1.\n";
		for (int i = 0; i < ops.size(); i++) {
			bool b = false;
			if (ops[i] == 2) {
				ops[i] = 1;
				b = runprogram();
				ops[i] = 2;
			}
			else if (ops[i] == 1) {
				ops[i] = 2;
				b = runprogram();
				ops[i] = 1;
			}

			if (b) {
				cout << "The accumulator is at " << acc << " when the program breaks out of the loop, for part 2.\n";
				break;
			}
		}

	}
}
