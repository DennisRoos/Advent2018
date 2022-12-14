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

		for (int j = 0; j < 360; j++) {
			for (int i = 0; i < 360; i++) {
				int small = 9999999;
				int best;
				for (int k = 0; k < l.size(); k++) {
					location loc = l[k];
					int dist = abs(i - loc.x) + abs(j - loc.y);
					if (dist < small) {
						small = dist;
						best = k;
					}
				}
				for (int k = 0; k < l.size(); k++) {
					location loc = l[k];
					int dist = abs(i - loc.x) + abs(j - loc.y);
					if (dist == small && k != best) {
						best = -1;
						break;
					}
				}
				if (best != -1) {
					l[best].total++;
				}
				A[i][j] = best;
			}
		}
		for (int i = 1; i < 359; i++) {
			if (A[i][0] != -1) {
				l[A[i][0]].infinite = true;
			}
			if (A[i][359] != -1) {
				l[A[i][359]].infinite = true;
			}
		}
		for (int i = 0; i < 360; i++) {
			if (A[0][i] != -1) {
				l[A[0][i]].infinite = true;
			}
			if (A[359][i] != -1) {
				l[A[359][i]].infinite = true;
			}
		}

		int smallest = 0;
		for (int k = 0; k < l.size(); k++) {
			cout << l[k].total << endl;
			if (l[k].infinite == false && l[k].total > smallest) {
				smallest = l[k].total;
			}
		}


		for (int j = 0; j < 20; j++) {
			for (int i = 0; i < 20; i++) {
				cout << char(A[i][j] + 'A');
			}
			cout << endl;
		}

		cout << "area is size " << smallest << endl;


	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}