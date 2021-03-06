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


char A[100][100];
char B[100][100];

int findseat(int x, int y, int deltax, int deltay) {
	do {
		x += deltax;
		y += deltay;
	} while (A[x][y] == '.');
	if (A[x][y] == '#') {
		return 1;
	}
	else {
		return 0;
	}
}

int main(int argc, char * argv[]) {

	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		int rows = 1;
		int columns;

		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 100; j++) {
				A[i][j] = 'L';
				B[i][j] = 'L';
			}
		}
		while (infile >> s){
			for (int j = 0; j < s.size(); j++) {
				A[rows][j + 1] = s[j];
				B[rows][j + 1] = s[j];
			}
			columns = s.size() + 1;
			rows++;
		}
		cout << rows << "," << columns << endl;

		bool b = true;
		while (b) {
			b = false;
			for (int i = 1; i < rows; i++) {
				for (int j = 1; j < columns; j++) {
					if (A[i][j] != '.') {
						int seats = 0;
						seats += findseat(i, j, 1, 0);//part 2
						seats += findseat(i, j, 1, 1);
						seats += findseat(i, j, 1, -1);
						seats += findseat(i, j, 0, 1);
						seats += findseat(i, j, 0, -1);
						seats += findseat(i, j, -1, 0);
						seats += findseat(i, j, -1, 1);
						seats += findseat(i, j, -1, -1);


						/*if (A[i - 1][j] == '#') {part 1
							seats++;
						}
						if (A[i - 1][j - 1] == '#') {
							seats++;
						}
						if (A[i - 1][j + 1] == '#') {
							seats++;
						}
						if (A[i][j - 1] == '#') {
							seats++;
						}
						if (A[i][j + 1] == '#') {
							seats++;
						}
						if (A[i + 1][j - 1] == '#') {
							seats++;
						}
						if (A[i + 1][j] == '#') {
							seats++;
						}
						if (A[i + 1][j + 1] == '#') {
							seats++;
						}*/
						if (A[i][j] == '#') {
							if (seats >= 5) {//5 for part 2, 4 for part 1
								B[i][j] = 'L';
								b = true;
							}
						}
						else {
							if (seats == 0) {
								B[i][j] = '#';
								b = true;
							}
						}

					}
				}
			}
			for (int i = 1; i < rows; i++) {
				for (int j = 1; j < columns; j++) {
					A[i][j] = B[i][j];
				}
			}
		}
		int count = 0;
		for (int i = 1; i < rows; i++) {
			for (int j = 1; j < columns; j++) {
				if (A[i][j] == '#') {
					count++;
				}
			}
		}

		cout << "There are " << count << " occupied seats in equilibrium" << endl;



	}
	return 0;
}