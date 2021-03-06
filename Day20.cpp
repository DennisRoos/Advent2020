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

int rowsize;

struct tile {
	int ID;
	char A[10][10][8];
	int N[8];
	int W[8];
	int E[8];
	int S[8];
	tile(int i) : ID(i) {}
};

vector<tile> v;
bool used[144];
int cornernumber;
int cornerorientation;
int image[12][12];
int orientation[12][12];
char Final[96][96];

void makeImage(int x, int y) {//finds the tile for the x'th row, y'th column
	if (x == rowsize) {
		cout << "Completed the image!" << endl;
		long long c = v[image[0][0]].ID;
		c *= v[image[0][rowsize-1]].ID;
		c *= v[image[rowsize - 1][0]].ID;
		c *= v[image[rowsize - 1][rowsize - 1]].ID;
		cout << "The product of the corners is " << c << endl;
		return;
	}
	int t;
	int ori ;
	if (x == 0) {//upper row, no north neighbor
		int w = v[image[0][y - 1]].E[orientation[0][y - 1]];//we grab the east border of the western neighbor
		for (int i = 0; i < v.size(); i++) {//we go through all remaining tiles...
			if (used[i] == false) {
				for (int k = 0; k < 8; k++) {//and all their orientations
					if (v[i].W[k] == w) {//found a match!
						image[x][y] = i;
						orientation[x][y] = k;
						used[i] = true;
						t = i;
						ori = k;
					}
				}
			}
		}
	}
	else if (y == 0) {//left column, no west neighbor
		int n = v[image[x-1][0]].S[orientation[x-1][0]];//we grab the south border of the northern neighbor
		for (int i = 0; i < v.size(); i++) {//we go through all remaining tiles...
			if (used[i] == false) {
				for (int k = 0; k < 8; k++) {//and all their orientations
					if (v[i].N[k] == n) {//found a match!
						image[x][y] = i;
						orientation[x][y] = k;
						used[i] = true;
						t = i;
						ori = k;
					}
				}
			}
		}
	}
	else {
		int w = v[image[x][y - 1]].E[orientation[x][y - 1]];//we grab the east border of the western neighbor
		int n = v[image[x - 1][y]].S[orientation[x - 1][y]];//we grab the south border of the northern neighbor
		for (int i = 0; i < v.size(); i++) {//we go through all remaining tiles...
			if (used[i] == false) {
				for (int k = 0; k < 8; k++) {//and all their orientations
					if (v[i].N[k] == n && v[i].W[k] == w) {//found a match!
						image[x][y] = i;
						orientation[x][y] = k;
						used[i] = true;
						t = i;
						ori = k;
					}
				}
			}
		}

	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Final[8 * x + i][8 * y + j] = v[t].A[i + 1][j + 1][ori];
		}
	}

	if (y < rowsize - 1) {
		makeImage(x, y + 1);
	}
	else {
		makeImage(x + 1, 0);
	}
}

void rotateSmall(char B[10][10], int n, tile& t) {
	char C[10][10];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			C[9 - j][i] = B[i][j];
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			B[i][j] = C[i][j];
			t.A[i][j][n] = C[i][j];
		}
	}
}

void rotateBig() {
	char C[96][96];
	for (int i = 0; i < 96; i++) {
		for (int j = 0; j < 96; j++) {
			C[95 - j][i] = Final[i][j];
		}
	}
	for (int i = 0; i < 96; i++) {
		for (int j = 0; j < 96; j++) {
			Final[i][j] = C[i][j];
		}
	}
}

void flip(char B[10][10], tile& t) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			char temp = B[i][j];
			t.A[i][j][4] = B[9 - i][j];
			B[i][j] = B[9 - i][j];
			B[9 - i][j] = temp;
			t.A[9-i][j][4] = temp;
		}
	}
}

void flipBig() {
	for (int i = 0; i < 48; i++) {
		for (int j = 0; j < 96; j++) {
			char temp = Final[i][j];
			Final[i][j] = Final[95 - i][j];
			Final[95 - i][j] = temp;
		}
	}
}

void findMonsters() {//checks for sea monsters, reports answer to part 2 and exits if it detects any
	bool monster = false;
	//find monster
	for (int i = 0; i < 94; i++) {
		for (int j = 18; j < 95; j++) {
			if (Final[i][j] == '#' &&
				Final[i + 1][j] == '#' &&
				Final[i + 1][j + 1] == '#' &&
				Final[i + 1][j - 1] == '#' &&
				Final[i + 1][j - 6] == '#' &&
				Final[i + 1][j - 7] == '#' &&
				Final[i + 1][j - 12] == '#' &&
				Final[i + 1][j - 13] == '#' &&
				Final[i + 1][j - 18] == '#' &&
				Final[i + 2][j - 17] == '#' &&
				Final[i + 2][j - 14] == '#' &&
				Final[i + 2][j - 11] == '#' &&
				Final[i + 2][j - 8] == '#' &&
				Final[i + 2][j - 5] == '#' &&
				Final[i + 2][j - 2] == '#') {

				monster = true;
				Final[i][j] = 'O';
				Final[i + 1][j] = 'O';
				Final[i + 1][j + 1] = 'O';
				Final[i + 1][j - 1] = 'O';
				Final[i + 1][j - 6] = 'O';
				Final[i + 1][j - 7] = 'O';
				Final[i + 1][j - 12] = 'O';
				Final[i + 1][j - 13] = 'O';
				Final[i + 1][j - 18] = 'O';
				Final[i + 2][j - 17] = 'O';
				Final[i + 2][j - 14] = 'O';
				Final[i + 2][j - 11] = 'O';
				Final[i + 2][j - 8] = 'O';
				Final[i + 2][j - 5] = 'O';
				Final[i + 2][j - 2] = 'O';
			}
		}
	}

	if (monster == false) {
		return;
	}
	int count = 0;
	for (int i = 0; i < 96; i++) {
		for (int j = 0; j < 96; j++) {
			if (Final[i][j] == '.') {
				cout << ' ';
			}
			else {
				cout << Final[i][j];
			}
			if (Final[i][j] == '#') {
				count++;
			}
		}
		cout << endl;
	}
	cout << "There were " << count << " non-sea monster tiles." << endl;
	exit(0);
}

void findCorner() {
	for (int i = 0; i < v.size(); i++) {
		for (int k = 0; k < 4; k++) {
			bool n = true;
			bool w = true;
			for (int j = 0; j < v.size(); j++) {
				if (j != i) {
					for (int l = 0; l < 8; l++) {
						if (v[i].N[k] == v[j].S[l]) {//tile i's north edge matches j's south edge
							n = false;
						}
						if (v[i].W[k] == v[j].E[l]) {//tile i's west edge matches j's east edge
							w = false;
						}
					}
				}
			}
			if (n && w) {
				cout << "Found a corner piece! " << i << "," << k << endl;
				cornernumber = i;
				cornerorientation = k;
				return;
			}
		}
	}
}

int main(int argc, char * argv[]) {
	ifstream infile;
	infile.open("data.txt");
	string s;
	rowsize = 12;
	if (infile.is_open())
	{
		while (infile >> s) {
			int id;
			infile >> id;
			char B[10][10];
			tile t = tile(id);
			for (int i = 0; i < 10; i++) {
				infile >> s;
				for (int j = 0; j < 10; j++) {
					B[i][j] = s[j];
					t.A[i][j][0] = B[i][j];
				}
			}


			rotateSmall(B, 1, t);
			rotateSmall(B, 2, t);
			rotateSmall(B, 3, t);
			flip(B, t);

			rotateSmall(B, 5, t);
			rotateSmall(B, 6, t);
			rotateSmall(B, 7, t);

			for (int i = 0; i < 8; i++) {
				int north = 0;
				int east = 0;
				int west = 0;
				int south = 0;
				int d = 1;
				for (int k = 0; k < 10; k++) {
					if (t.A[0][k][i] == '#') {
						north += d;
					}
					if (t.A[k][0][i] == '#') {
						west += d;
					}
					if (t.A[9][k][i] == '#') {
						south += d;
					}
					if (t.A[k][9][i] == '#') {
						east += d;
					}
					d *= 2;
				}
				t.N[i] = north;
				t.E[i] = east;
				t.W[i] = west;
				t.S[i] = south;
			}
			//testing
			/*for (int k = 0; k < 8; k++) {
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						cout << t.A[i][j][k];
					}
					cout << endl;
				}
				cout << id << "," << k << ": " << t.N[k] << "," << t.W[k] << "," << t.E[k] << "," << t.S[k] << endl;
				cout << endl << "Next orientation" << endl;
			}*/
			v.push_back(t);
		}
	}
	cout << "There are " << v.size() << " tiles" << endl;
	findCorner();
	for (int i = 0; i < 144; i++) {
		used[i] = false;
	}
	used[cornernumber] = true;
	orientation[0][0] = cornerorientation;
	image[0][0] = cornernumber;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Final[i][j] = v[cornernumber].A[i + 1][j + 1][cornerorientation];
		}
	}
	makeImage(0, 1);

	findMonsters();
	rotateBig();
	findMonsters();
	rotateBig();
	findMonsters();
	rotateBig();
	findMonsters();

	flipBig();
	findMonsters();
	rotateBig();
	findMonsters();
	rotateBig();
	findMonsters();
	rotateBig();
	findMonsters();

	return 0;
}