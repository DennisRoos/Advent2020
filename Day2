#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;


int main(int argc, char * argv[]) {

	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		int min;
		int max;
		char c;
		string pass;

		int valid = 0;
		int valid2 = 0;
		while (infile >> min) {
			infile >> max;
			infile >> c;
			infile >> pass;
			int count = 0;
			for (int i = 0; i < pass.size(); i++) {
				if (pass[i] == c) {
					count++;
				}
			}
			if (count >= min && count <= max) {
				valid++;
			}
			if ((pass[min - 1] == c && pass[max - 1] != c) ||
				(pass[min - 1] != c && pass[max - 1] == c)) {
				valid2++;
			}
		}
		cout << "There are " << valid << " valid passwords for part 1\n";
		cout << "There are " << valid2 << " valid passwords for part 2\n";
	}
	return 0;
}
