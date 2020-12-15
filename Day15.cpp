#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <iterator>         // std::(istream_iterator, back_inserter)
#include <sstream>          // std::(istringstream)
#include <list>
#include <map>

using namespace std;

int main(int argc, char * argv[])
{
	//map<int, int> A;
	static int A[30000000];
	ifstream infile;
	infile.open("data.txt");
	int n;
	for (int i = 0; i < 30000000; i++) {
		A[i] = 0;
	}
	if (infile.is_open())
	{
		int turn = 1;
		int nextn;
		while (infile >> n) {
			A[n] = turn;
			turn++;
		}
		n = 0;
		int amount = 30000000;
		while (turn < amount) {
			if (A[n] == 0) {//first time we see this number
				nextn = 0;
			}
			else {
				nextn = turn - A[n];
			}
			A[n] = turn;
			//cout << turn << ": " << n << " , " << nextn << endl;
			n = nextn;
			turn++;
		}
		cout << "The " << amount << "th number is " << n << endl;



	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}