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

int main(int argc, char * argv[])
{
	/*

		     -lat
		  	   1
		   	   ^
			   |
	-lon 2 <---o---> 0 +lon
			   |
			   v
			   3
			 +lat
	*/ 

	int lat = 0;
	int lon = 0;
	int dir = 0;

	int wlat = -1;
	int wlon = 10;

	ifstream infile;						
	infile.open("data.txt");
	string s;

	if (infile.is_open())
	{
		while (infile >> s) {
			char c = s[0];
			s = s.erase(0, 1);
			int n = stoi(s);

			if (c == 'N') {//part 2
			wlat -= n;
			}
			else if (c == 'S') {
			wlat += n;
			}
			else if (c == 'E') {
			wlon += n;
			}
			else if (c == 'W') {
			wlon -= n;
			}
			else if (c == 'F') {
				lat += wlat * n;
				lon += wlon * n;
			}
			else {
				if (n == 180) {
					wlat = -1 * wlat;
					wlon = -1 * wlon;
				}
				else if ((c == 'L' && n == 90) || (c == 'R' && n == 270)) {
					int t1 = wlat;
					wlat = -1 * wlon;
					wlon = t1;
				}
				else {
					int t1 = wlon;
					wlon = -1 * wlat;
					wlat = t1;
				}
			}
			

			cout << lat << "," << lon << " . " << wlat << "," << wlon << endl; 
			
			//part 1
			/*if (c == 'N') {
				lat -= n;
			}
			else if (c == 'S') {
				lat += n;
			}
			else if (c == 'E') {
				lon += n;
			}
			else if (c == 'W') {
				lon -= n;
			}
			else if (c == 'F') {
				if (dir == 0) {
					lon += n;
				}
				else if (dir == 1) {
					lat -= n;
				}
				else if (dir == 2) {
					lon -= n;
				}
				else if (dir == 3) {
					lat += n;
				}
			}

			else{
				n /= 90;
				if (c == 'L') {
					dir = (dir + n) % 4;
				}
				else {
					dir -= n;
					if (dir < 0) {
						dir += 4;
					}

				}
			}
			cout << lat << "," << lon << " , " << dir << endl;*/

		}

		int dist = abs(lat) + abs(lon);
		cout << "The distance is " << dist << endl;
	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}