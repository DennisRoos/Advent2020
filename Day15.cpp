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
#include <chrono>


using namespace std;

int main(int argc, char * argv[])
{
	static int A[30000000];
	ifstream infile;
	infile.open("data.txt");
	auto start = std::chrono::steady_clock::now();
	int n;
	int amount = 30000000;//change to 2020 for part 1
	for (int i = 0; i < amount; i++) {
		A[i] = 0;
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "Initialization took " << elapsed_seconds.count() << "s\n";
	if (infile.is_open())
	{
		int turn = 1;
		int nextn;
		while (infile >> n) {
			A[n] = turn;
			turn++;
		}
		n = 0;
		while (turn < amount) {
			if (A[n] == 0) {//first time we see this number
				nextn = 0;
			}
			else {
				nextn = turn - A[n];
			}
			A[n] = turn;
			n = nextn;
			turn++;
		}
		auto end2 = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = end2 - start;
		std::cout << "Entire program took " << elapsed_seconds.count() << "s\n\n";
		cout << "The " << amount << "th number is " << n << endl;



	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}
