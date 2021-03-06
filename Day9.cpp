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


int main(int argc, char * argv[]) {

	long long Preamble[1000];
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		int k = 0;
		while (infile >> Preamble[k]) {
			k++;
		}
		k = 25;
		while (true) {
			bool b = false;
			for (int i = k - 25; i < k - 1; i++) {
				for (int j = i + 1; j < k; j++) {
					if (Preamble[i] + Preamble[j] == Preamble[k]) {
						b = true;
					}
				}
			}
			if (!b) {
				cout << "The first number to fail is " << Preamble[k] << endl;
				//now for part 2
				long long target = Preamble[k];
				for (int i = 0; i < k; i++) {
					int j = i + 1;
					long long sum = Preamble[i] + Preamble[j];
					while (sum < target) {
						j++;
						sum += Preamble[j];
					}
					if (sum == target) {//found it
						long long high = -1;
						long long low = 9999999999999;
						for (int n = i; n <= j; n++) {
							low = min(low, Preamble[n]);
							high = max(high, Preamble[n]);
						}
						cout << "The answer for part 2 is " << low + high << endl;
						return 0;
					}
				}



			}
			k++;
		}
	}
	return 0;
}