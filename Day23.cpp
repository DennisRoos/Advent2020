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

struct cup {
	cup* right;
	cup* prev;
	int num;
	cup(int n) : num(n) {}
};

int main(int argc, char * argv[]) {
	string input = "792845136";
	int k = input[0] - '0';
	cup* current = new cup(k);
	cup* last = current;
	for (int i = 1; i < input.size(); i++) {
		k = input[i] - '0';
		cup *next = new cup(k);
		last->right = next;
		last = next;
	}
	cup* dest;
	for (int i = 2; i <= 9; i++) {
		dest = current;
		while (dest->num != i) {
			dest = dest->right;
		}
		int label = i - 1;
		cup* dest2 = current;
		while (dest2->num != label) {
			dest2 = dest2->right;
		}
		dest->prev = dest2;//find all the prev pointers for the first cups
	}



	cup* next = new cup(10);//link 10 to 9
	next->prev = dest;
	last->right = next;
	last = next;
	for (int i = 11; i <= 1000000; i++) {//part 2 additional cups
		cup *next = new cup(i);
		next->prev = last;
		last->right = next;
		last = next;
	}
	last->right = current;

	dest = current;
	while (dest->num != 1) {
		dest = dest->right;
	}
	dest->prev = last;//link 1 back to 1000000

	dest = current;

	cout << "Setup done" << endl;


	for (int i = 0; i < 10000000; i++) {
		cup* grab = current->right;
		cup* dest = current->prev;
		current->right = grab->right->right->right;
		while (dest == grab || dest == grab->right || dest == grab->right->right) {
			dest = dest->prev;
		}
		grab->right->right->right = dest->right;
		dest->right = grab;
		current = current->right;
	}
	

	cup *findone = current;
	while (findone->num != 1) {
		findone = findone->right;
	}

	//part2
	long long m1 = findone->right->num;
	long long m2 = findone->right->right->num;
	long long mult = m1 * m2;
	cout << "The product of those two cups is " << mult << endl;

	/*do {//part1
		findone = findone->right;
		cout << findone->num << endl;
	} while (findone->right->num != 1);
	cout << endl;
	*/



	return 0;
}