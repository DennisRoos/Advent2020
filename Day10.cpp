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
		int D[4];
		for (int i = 0; i < 4; i++) {
			D[i] = 0;
		}
		int n;
		while (infile >> n) {
			v.push_back(n);
		}
		sort(v.begin(), v.end());
		int cur = 0;
		for (int i = 0; i < v.size(); i++) {
			D[v[i] - cur]++;
			cur = v[i];
			cout << v[i] << endl;
		}
		int final = cur + 3;
		v.push_back(final);
		D[3]++;
		cout << "The answer for part 1 is " << D[1] * D[3] << endl;
		long long A[300];
		for (int i = 0; i < 300; i++) {
			A[i] = 0;
		}
		A[0] = 1;
		A[1] = 1;
		A[2] = 2;
		for (int i = 2; i < v.size(); i++) {
			int n = v[i];
			A[n] = A[n - 3] + A[n - 2] + A[n - 1];
		}

		cout << "The final device has " << A[final] << " paths to it\n";
 
	}
	return 0;
}