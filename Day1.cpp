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

vector<int> v;

int main(int argc, char * argv[]) {

	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		int n;
		while (infile >> n) {
			v.push_back(n);
		}
		sort(v.begin(), v.end());

		for (int i = 0; i < v.size(); i++) {
			int j = i + 1;
			while (v[i] + v[j] < 2020) {
				j++;
			}
			if (v[i] + v[j] == 2020) {
				int answer = v[i] * v[j];
				cout << "The answer to part 1 is " << answer << endl;
				break;
			}
		}

		for (int i = 0; i < v.size(); i++) {
			for (int j = i + 1; v[i] + v[j] < 2020; j++) {
				int sum = v[i] + v[j];
				int k = j + 1;
				while (sum + v[k] < 2020) {
					k++;
				}
				if (sum + v[k] == 2020) {
					long long answer = v[i] * v[j] * v[k];
					cout << "The answer to part 2 is " << answer << endl;
					exit(0);
				}
			}
		}
	}
	return 0;
}
