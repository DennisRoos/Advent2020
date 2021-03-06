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

using namespace std;

struct bus {
	int id;
	int offset;
	bus(int a, int b) : id(a), offset(b) {}
};

vector<bus> v;


struct less_than_angle
{
	inline bool operator() (const bus& a1, const bus& a2)
	{
		return a1.id < a2.id;
	}
};

int main(int argc, char * argv[])
{

	ifstream infile;
	infile.open("data.txt");
	
	int best = 99999999;
	int answer = -1;
	int earliest;
	string s;
	int offset = 0;

	if (infile.is_open())
	{
		infile >> earliest;
		while (infile >> s) {
			if (s.compare("x") != 0) {
				int id = stoi(s);
				int waittime = id - (earliest % id);
				if (waittime < best) {
					best = waittime;
					answer = waittime * id;
				}
				bus b = bus(id, offset);
				v.push_back(b);
				cout << id << "," << offset << endl;
			}
			offset++;
		}
		cout << "The answer to part 1 is " << answer << endl;

		//let's say we have some timestamp T, where two buses arrive correctly (with offset)
		//then the next timestamp U, U > T, where both buses arrive correctly, must be T + (b1.id*b2.id) (because all ids are mutually prime), so we can use that as our increment step
		//then we find the next point V, V = T + k(b1.id*b2.id) (for some positive integer k), where bus b3 arrives correctly, and 
		//increase the increment to (b1.id*b2.id*b3.id), until we've done this for all the buses

		sort(v.begin(), v.end(), less_than_angle());
		unsigned long long increment = 1;

		unsigned long long t = 3;



		while (true) {
			bool b = true;
			for (int i = 0; i < v.size(); i++) {
				if ((t + v[i].offset) % v[i].id == 0) {
					increment *= v[i].id;
					v.erase(v.begin() + i);
					i--;
				}
			}
			if (v.size() == 0) {
				cout << "The answer to part 2 is " << t << endl;
				exit(0);
			}
			t += increment;
		}

	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}