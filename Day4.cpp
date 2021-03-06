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
	bool byr = false;
	bool iyr = false;
	bool eyr = false;
	bool hgt = false;
	bool hcl = false;
	bool ecl = false;
	bool pid = false;
	bool cid = false;
	int valid = 0;
	string field;
	string entry;
	int n;
	while (getline(f, s)) {
		while (!s.empty()) {
			istringstream iss(s);
			while (iss >> field) {
				if (field.compare("byr") == 0) {
					iss >> n;
					if (n >= 1920 && n <= 2002) {
						byr = true;
					}
				}
				else if (field.compare("iyr") == 0) {
					iss >> n;
					if (n >= 2010 && n <= 2020) {
						iyr = true;
					}
				}
				else if (field.compare("eyr") == 0) {
					iss >> n;
					if (n >= 2020 && n <= 2030) {
						eyr = true;
					}
				}
				else if (field.compare("hgt") == 0) {
					iss >> entry;
					string unit = entry.substr(entry.size() - 2, 2);
					string amount = entry.substr(0, entry.size() - 2);
					if (unit.compare("cm") == 0) {
						n = stoi(amount);
						if (n >= 150 && n <= 193) {
							hgt = true;
						}
					}
					else if (unit.compare("in") == 0) {
						n = stoi(amount);
						if (n >= 59 && n <= 76) {
							hgt = true;
						}
					}
				}
				else if (field.compare("hcl") == 0) {
					iss >> entry;
					if (entry.size() == 7) {
						if (entry[0] == '#') {
							hcl = true;
							for (int i = 1; i < 7; i++) {
								if (!((entry[i] >= '0' && entry[i] <= '9') || (entry[i] >= 'a' && entry[i] <= 'f'))) {
									hcl = false;
								}
							}
						}
					}
				}
				else if (field.compare("ecl") == 0) {
					iss >> entry;
					if (entry.compare("amb") == 0 ||
						entry.compare("blu") == 0 ||
						entry.compare("brn") == 0 ||
						entry.compare("gry") == 0 ||
						entry.compare("grn") == 0 ||
						entry.compare("oth") == 0 ||
						entry.compare("hzl") == 0) 
					{
						ecl = true;
					}
				}
				else if (field.compare("pid") == 0) {
					iss >> entry;
					if (entry.size() == 9) {
						pid = true;
						for (int i = 0; i < 9; i++) {
							if (entry[i] < '0' || entry[i] > '9') {
								pid = false;
							}
						}
					}
				}

				else if (field.compare("cid") == 0) {
					iss >> entry;
				}
			}
			getline(f, s);
		}
		if (byr && iyr && eyr && hgt && hcl && ecl && pid) {
			valid++;
		}
		byr = false;
		iyr = false;
		eyr = false;
		hgt = false;
		hcl = false;
		ecl = false;
		pid = false;
		cid = false;
	}
	cout << "There are " << valid << " valid IDs\n";
	return 0;
}