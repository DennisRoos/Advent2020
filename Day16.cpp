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

struct field {
	string name;
	int min1;
	int max1;
	int min2;
	int max2;
	int col;
	int count;
	bool valid[20];
	field(string n, int a, int b, int c, int d) : name(n), min1(a), max1(b), min2(c), max2(d), col(-1) {}
};

vector<field> v;

struct ticket {
	int A[20];
	ticket()  {}
};

int myticket[20];
vector<ticket> tickets;

int main(int argc, char * argv[]) {

	regex re1("([a-z]+): ([\\d]+)-([\\d]+) or ([\\d]+)-([\\d]+)");
	string s;
	smatch match;
	ifstream f("data.txt");
	for(int i = 0; i < 20; i++){
		getline(f, s);
		if (regex_search(s, match, re1) == true) {
			string name = match.str(1);

			int a1 = stoi(match.str(2));
			int a2 = stoi(match.str(3));
			int b1 = stoi(match.str(4));
			int b2 = stoi(match.str(5));
			field f = field(name, a1, a2, b1, b2);
			for (int j = 0; j < 20; j++) {
				f.valid[j] = false;
			}
			f.count = 0;
			v.push_back(f);
		}
	}

	getline(f, s);
	getline(f, s);
	getline(f, s);//our ticket
	istringstream iss(s);
	for (int i = 0; i < 20; i++) {
		iss >> myticket[i];
	}

	getline(f, s);
	getline(f, s);

	int total = 0;
	int ticketnumber = 0;

	while (getline(f, s)) {
		ticket t = ticket();
		bool valid = true;
		istringstream iss(s);
		for (int i = 0; i < 20; i++) {
			int n;
			iss >> n;
			t.A[i] = n;
			bool b = false;
			for (int j = 0; j < 20; j++) {
				if ((n >= v[j].min1 && n <= v[j].max1) || (n >= v[j].min2 && n <= v[j].max2)) {
					b = true;
				}
			}
			if (!b) {//field doesn't match any entry
				total += n;
				valid = false;
			}
		}
		if (valid) {
			tickets.push_back(t);
		}
	}
	cout << "The ticket scanning error rate is " << total << endl;

	for (int i = 0; i < 20; i++) {//we check what columns are eligible for what fields
		for (int c = 0; c < 20; c++) {
			bool b = true;
			for (int t = 0; t < tickets.size(); t++) {
				int n = tickets[t].A[c];
				if ( !((n >= v[i].min1 && n <= v[i].max1) || (n >= v[i].min2 && n <= v[i].max2))) {
					b = false;
				}
			}
			if (b) {//every entry in this column matches the field, so it's possible that this matches it
				v[i].count++;
				v[i].valid[c] = true;
			}
		}
	}

	int left = 20;
	while (left > 0) {//the only remaining valid column for a field must be its match
		for (int i = 0; i < 20; i++) {
			if (v[i].count == 1) {//found a field with only one eligible column left
				int col;
				for (int j = 0; j < 20; j++) {
					if (v[i].valid[j]) {
						col = j;
					}
				}
				v[i].col = col;
				cout << "confirmed column " << col << " for field " << v[i].name << endl;
				left--;
				for (int j = 0; j < 20; j++) {
					if (v[j].valid[col]) {//remove this column from eligibility for all fields
						v[j].valid[col] = false;
						v[j].count--;
					}
				}
			}
		}
	}

	long long total2 = 1;
	for (int i = 0; i < 6; i++) {//the departure fields are the first 6 entries in v
		total2 *= myticket[v[i].col];
	}
	cout << "The answer to part 2 is " << total2 << endl;

	return 0;
}