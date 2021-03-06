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

bool A[1024];

int main(int argc, char * argv[]) {

	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		for (int i = 0; i < 1024; i++) {
			A[i] = false;
		}
		string s;
		int highest = -1;
		while (infile >> s) {
			int row = 0;
			int column = 0;
			unsigned int d = 64;
			for (int i = 0; i < 7; i++) {
				if (s[i] == 'B') {
					row += d;
				}
				d = d / 2;
			}
			d = 4;
			for (int i = 7; i < 10; i++) {
				if (s[i] == 'R') {
					column += d;
				}
				d = d / 2;
			}
			int seatnumber = (row * 8) + column;
			highest = max(seatnumber, highest);
			A[seatnumber] = true;
		}
		cout << "The highest number was " << highest << endl;
		for (int i = 1; i < 1023; i++) {
			if (A[i - 1] && A[i + 1] && !A[i]) {
				cout << "My seat number is " << i << endl;
			}
		}
	}
	return 0;
}