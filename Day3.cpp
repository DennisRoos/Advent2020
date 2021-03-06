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

bool A[350][50];
int height;
int width;

int traverse(int right, int down) {
	int trees = 0;
	int y = 0;
	for (int x = down; x < height; x = x + down) {
		y = (y + right) % width;
		if (A[x][y] == true) {
			trees++;
		}
	}
	cout << "There were " << trees << " trees on the slope with Right " << right << ", Down " << down << endl;
	return trees;
}

int main(int argc, char * argv[])
{


	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		height = 0;
		while (infile >> s) {
			for(int i = 0; i < s.size(); i++){
				if (s[i] == '#') {
					A[height][i] = true;
				}
				else {
					A[height][i] = false;
				}
			}
			width = s.size();
			height++;
		}
		long long total = 1;
		total *= traverse(1, 1);
		total *= traverse(3, 1);
		total *= traverse(5, 1);
		total *= traverse(7, 1);
		total *= traverse(1, 2);
		
		cout << "The product of the trees is " << total << endl;


	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}