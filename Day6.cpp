#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <list>

using namespace std;

int A[360][360];

struct location {
	int x;
	int y;
	int total;
	bool infinite;
	location(int xx, int yy): x(xx),y(yy),total(0),infinite(false) {}
};

vector<location> l;

int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		int x;
		int y;
		while (infile >> x) {
			infile >> y;
			location loc = location(x, y);
			l.push_back(loc);
		}
		int total = 0;
		for (int j = 0; j < 360; j++) {
			for (int i = 0; i < 360; i++) {
				int dist = 0;
				for (int k = 0; k < l.size(); k++) {
					location loc = l[k];
					dist += abs(i - loc.x) + abs(j - loc.y);
				}
				if (dist < 10000) {
					total++;
				}
			}
		}
		

		cout << "area is size " << total << endl;


	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}