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



int main(int argc, char * argv[]) {
	int public1 = 5290733;
	int public2 = 15231938;
	int loop1 = 0;
	long long value = 1;
	while (value != public1) {
		value = (value * 7) % 20201227;
		loop1++;
	}
	value = 1;
	int loop2 = 0;
	while (value != public2) {//strictly speaking the second loop calculation isn't necessary, but we might as well
		value = (value * 7) % 20201227;
		loop2++;
	}
	cout << loop1 << "," << loop2 << endl;
	value = 1;
	for (int i = 0; i < loop1; i++) {
		value = (value * public2) % 20201227;
	}
	cout << "The encryption key is " << value << endl;
	return 0;
}