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

bool A[200][200];//false = white, true = black
bool B[200][200];

int main(int argc, char * argv[]) {
	ifstream infile;
	infile.open("data.txt");
	string s;
	if (infile.is_open())
	{
		for (int i = 0; i < 200; i++) {
			for (int j = 0; j < 200; j++) {
				A[i][j] = false;
			}
		}
		int q;
		int r;
		while (infile >> s) {
			q = 100;
			r = 100;
			for (int i = 0; i < s.size(); i++) {
				if (s[i] == 'e') {
					q++;
				}
				else if (s[i] == 'w') {
					q--;
				}
				else if (s[i] == 'n') {
					i++;
					r--;
					if (s[i] == 'e') {
						q++;
					}
				}
				else if (s[i] == 's') {
					i++;
					r++;
					if (s[i] == 'w') {
						q--;
					}
				}
			}
			A[q][r] = !A[q][r];
		}
		int counttiles = 0;
		for (int i = 0; i < 200; i++) {
			for (int j = 0; j < 200; j++) {
				B[i][j] = A[i][j];
				if (A[i][j]) {
					counttiles++;
				}
			}
		}
		cout << "There are " << counttiles << " black tiles at the start.\n";

		for (int steps = 0; steps < 100; steps++) {
			for (int i = 1; i < 199; i++) {
				for (int j = 1; j < 199; j++) {
					int n = 0;//number of black neighbors
					if (A[i][j - 1]) {
						n++;
					}
					if (A[i + 1][j - 1]) {
						n++;
					}
					if (A[i + 1][j]) {
						n++;
					}
					if (A[i - 1][j]) {
						n++;
					}
					if (A[i - 1][j + 1]) {
						n++;
					}
					if (A[i][j + 1]) {
						n++;
					}
					if (A[i][j] && (n == 0 || n > 2)) {
						B[i][j] = false;
					}
					else if (!A[i][j] && n == 2) {
						B[i][j] = true;
					}
				}
			}
			for (int i = 1; i < 199; i++) {
				for (int j = 1; j < 199; j++) {
					A[i][j] = B[i][j];
				}
			}
		}
		counttiles = 0;
		for (int i = 0; i < 200; i++) {
			for (int j = 0; j < 200; j++) {
				if (A[i][j]) {
					counttiles++;
				}
			}
		}
		cout << "There are " << counttiles << " black tiles after 100 steps.\n";
	}
	return 0;
}