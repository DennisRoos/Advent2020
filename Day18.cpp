﻿#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

int i;
string s;


long long calculate();

long long calc2(){
	long long n;
	if (s[i] == '(') {
		i++;
		n = calculate();
	}
	else {
		n = s[i] - '0';
	}
	i++;
	while (i < s.size() && s[i] == '+') {
		i++;
		long long m;
		if (s[i] == '(') {
			i++;
			m = calculate();
		}
		else{
			m = s[i] - '0';
		}
		n += m;
		i++;
	}
	return n;

}

long long calculate() {
	long long n;
	
	if (s[i] == '(') {
		i++;
		n = calculate();
	}
	else {
		n = s[i] - '0';
	}
	
	i++;
	bool sum;
	while (i < s.size() && s[i] != ')') {
		
		if (s[i] == '+') {
			sum = true;
		}
		else if (s[i] == '*') {
			sum = false;
		}
		else {
			cout << s[i] << " ???" << endl;
		}
		i++;
		long long m;

		if (sum == false) {//put everything between lines 73-78 in commentary for part 1
			m = calc2();
			i--;

		}
		else 
			if (s[i] == '(') {
				i++;
				m = calculate();
			}
		else{
			m = s[i] - '0';
		}

		if (sum) {
			n += m;
		}
		else {
			n *= m;
		}
		i++;

	}
	return n;
}

int main(int argc, char * argv[]) {

	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		long long total = 0;
		while (infile >> s) {
			i = 0;
			long long exp = calculate();//part 1
			total += exp;
			//cout << exp << " , " << total << endl;
		}

		cout << "The total is " << total << endl;
	}
	return 0;
}
