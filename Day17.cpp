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

int A[25][25][17][17];
int B[25][25][17][17];

int main(int argc, char * argv[]) {

	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 25; j++) {
			for (int k = 0; k < 17; k++) {
				for (int l = 0; l < 17; l++) {
					A[i][j][k][l] = 0;
					B[i][j][k][l] = 0;
				}
			}
		}
	}

	ifstream f("data.txt");
	string s;
	int a = 8;
	while (getline(f, s)) {
		for (int b = 0; b < s.size(); b++) {
			if (s[b] == '#') {
				A[a][b + 8][8][8] = 1;
				B[a][b + 8][8][8] = 1;
			}
		}
		a++;
	}
	for (int steps = 1; steps < 7; steps++) {//update
		for (int k = 1; k < 16; k++) {
			for (int l = 1; l < 16; l++) {
				for (int i = 1; i < 24; i++) {
					for (int j = 1; j < 24; j++) {
						int total = 0;
						for (int a = -1; a < 2; a++) {
							for (int b = -1; b < 2; b++) {
								for (int c = -1; c < 2; c++) {
									for (int d = -1; d < 2; d++) {
										total += A[i + a][j + b][k + c][l + d];
									}
								}
							}
						}
						total -= A[i][j][k][l];//remove the center cube


						if (A[i][j][k][l] == 0 && total == 3) {
							B[i][j][k][l] = 1;
						}
						else if (A[i][j][k][l] == 1 && (total < 2 || total > 3)) {
							B[i][j][k][l] = 0;
						}
					}
				}
			}
		}
		for (int i = 1; i < 24; i++) {
			for (int j = 1; j < 24; j++) {
				for (int k = 1; k < 16; k++) {
					for (int l = 1; l < 16; l++) {
						A[i][j][k][l] = B[i][j][k][l];
					}
				}
			}
		}
	}
	int count = 0;
	for (int k = 1; k < 16; k++) {
		for (int i = 1; i < 24; i++) {
			for (int j = 1; j < 24; j++) {
				for (int l = 1; l < 16; l++) {
					count += A[i][j][k][l];
				}
			}
		}
	}

	cout << "There were " << count << " active cells after 6 cycles\n";
	return 0;
}