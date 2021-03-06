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



int main(int argc, char * argv[]) {

	ifstream f("data.txt");
	string s;
	int yes[26];
	int anyone = 0;
	int everyone = 0;
	int groupsize;
	while (getline(f, s)) {
		for (int i = 0; i < 26; i++) {
			yes[i] = 0;
		}
		groupsize = 0;
		while (!s.empty()) {
			groupsize++;
			for (int i = 0; i < s.size(); i++) {
				yes[s[i] - 'a']++;
			}
			getline(f, s);
		}
		for (int i = 0; i < 26; i++) {
			if (yes[i] > 0) {
				anyone++;
			}
			if (yes[i] == groupsize) {
				everyone++;
			}
		}

	}
	cout << "There were " << anyone << " questions answered yes by someone.\n";
	cout << "There were " << everyone << " questions answered yes by everyone.\n";

	return 0;
}