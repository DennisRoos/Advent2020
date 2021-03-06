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

struct rule1 {
	int num;
	char b;
	rule1(int n, char a) : num(n), b(a) {}
};

vector<rule1> T;

struct rule2 {
	int num;
	int tar1;
	int tar2;
	rule2(int n, int t1, int t2) : num(n), tar1(t1), tar2(t2) {}
};

vector<rule2> R;

bool P[100][100][140];

//CYK algorithm
bool CYK(string s) {
	int n = s.size();
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			for (int k = 0; k < R.size(); k++) {
				P[i][j][k] = false;
			}
		}
	}

	for (int k = 0; k < T.size(); k++) {
		for (int i = 0; i < n; i++) {
			if (T[k].b == s[i]) {
				P[1][i+1][T[k].num] = true;
			}
		}
	}
	for (int l = 2; l <= n; l++) {
		for (int ss = 1; ss <= n - l + 1; ss++) {
			for (int p = 1; p <= l-1; p++) {
				for (int k = 0; k < R.size(); k++) {
					if (P[p][ss][R[k].tar1] && P[l - p][ss + p][R[k].tar2]) {
						P[l][ss][R[k].num] = true;
					}
				}
			}
		}
	}
	return P[n][1][0];
}


int main(int argc, char * argv[]) {

	ifstream f("data.txt");
	string s;
	getline(f, s);
	vector<string> v;
	while (!s.empty()) {
		int num;
		v.clear();
		string inp;
		istringstream iss(s);
		while (iss >> inp) {
			v.push_back(inp);
		}
		num = stoi(v[0]);
		if (v[1][0] == '"') {
			rule1 r1 = rule1(num, v[1][1]);
			T.push_back(r1);
		}
		else {
			int n1 = stoi(v[1]);
			if (v.size() > 2) {
				if (v[2].compare("|") == 0) {

				}
				else {
					int n2 = stoi(v[2]);
					rule2 r2 = rule2(num, n1, n2);
					R.push_back(r2);
					if (v.size() > 3) {

						int n3 = stoi(v[4]);
						if (v.size() > 5) {
							int n4 = stoi(v[5]);
							rule2 r3 = rule2(num, n3, n4);
							R.push_back(r3);
						}
					}
				}
			}
		}
		getline(f, s);
	}
	
	rule1 t95 = rule1(95, 'a');//manually adding the one friggin annoying rule that goes "95 -> 20 | 30" where 20 and 30 are the terminals
	T.push_back(t95);
	rule1 t96 = rule1(95, 'b');
	T.push_back(t96);

	int count = 0;
	int c2 = 0;
	while (getline(f, s)) {
		c2++;
		if (CYK(s)) {
			count++;
		}
		cout << s << " Word done, count at " << count << " / " << c2 << endl;
	}
	
	cout << "There were " << count << " valid messages!" << endl;

	return 0;
}