#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>

#include <iterator>         // std::(istream_iterator, back_inserter)
#include <sstream>          // std::(istringstream)
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <iterator>

using namespace std;


map<unsigned long long, long long> mymap;
string bitmask;

void splitfloat(int j, unsigned long long address, long long current, unsigned long long input) {
	long long adder = pow(2, 35-j);
	for (int i = j; i >= 0; i--) {
		if (bitmask[i] == '1' || ((bitmask[i] == '0') && (address & 1 == 1))) {
			current += adder;
		}
		else if (bitmask[i] == 'X') {
			splitfloat(i - 1, address / 2, current + adder, input);//split off a branch that does add this bit to the current address, this iteration will continue without that bit
		}
		adder *= 2;
		address = address / 2;
	}
	mymap.insert_or_assign(current, input);
	//cout << "write value " << input << " to address " << current << endl;
}

int main(int argc, char * argv[]) {

	regex re1("mask = (.+)");
	regex re2("mem\\[([\\d]+)\\] = ([\\d]+)");
	string s;
	smatch match;
	ifstream f("data.txt");
	while (getline(f, s)) {
		if (regex_search(s, match, re1) == true) {
			bitmask = match.str(1);
		}
		else if(regex_search(s, match, re2) == true){

			unsigned long long address = stoll(match.str(1));
			unsigned long long n = stoll(match.str(2));
			//part 2
			splitfloat(35, address, 0, n);
			
			//part 1
			/*unsigned long long value = 0; 
			unsigned long long adder = 1;
			cout << "The input is " << n << " for address " << address << endl;
			for (int i = 35; i >= 0; i--) {
				if (bitmask[i] == '1' || ((bitmask[i] == 'X') && (n & 1 == 1))) {
					value += adder;
				}
				adder *= 2;
				n = n / 2;
			}
			mymap.insert_or_assign(address, value);
			//cout << "The final value is " << value << endl;*/
		}
	}

	long long total = 0;
	map<unsigned long long, long long>::iterator it = mymap.begin();
	while (it != mymap.end())
	{
		total += it->second;
		it++;
	}

	cout << "The total value in memory at the end is " << total << endl;

	return 0;
}