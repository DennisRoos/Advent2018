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

int A[1700][1700];
int ymax;
int ymin;
int countwater;
int countstill;

bool traverse(int x, int y) {
	if (A[x][y] == 1 || A[x][y] == 4) {
		return true;
	}
	if (A[x][y] == 2) {
		return false;
	}
	if (y > ymax) {
		return false;
	}
	A[x][y] = 2;
	countwater++;
	bool b = traverse(x, y + 1);
	if (b) {
		bool bl = true;
		bool br = true;
		int newx = x - 1;
		while (A[newx][y] == 0) {
			A[newx][y] = 2;
			countwater++;
			if (A[newx][y + 1] == 0) {
				bl = traverse(newx, y + 1);
				if (bl == false) {
					break;
				}
			}
			newx--;
		}
		newx = x + 1;
		while (A[newx][y] == 0) {
			A[newx][y] = 2;
			countwater++;
			if (A[newx][y + 1] == 0) {
				br = traverse(newx, y + 1);
				if (br == false) {
					break;
				}
			}
			newx++;
		}
		if (bl && br) {
		    newx = x - 1;
			while (A[newx][y] == 2) {
				A[newx][y] = 4;
				countstill++;
				newx--;
			}
			newx = x + 1;
			while (A[newx][y] == 2) {
				A[newx][y] = 4;
				countstill++;
				newx++;
			}
			A[x][y] = 4;
			countstill++;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

int main(int argc, char * argv[]) {

	regex re("([xy])=([\\d]+), [xy]=([\\d]+)..([\\d]+)");
	string s;
	ymax = 0;
	ymin = 99999;
	smatch match;
	ifstream f("data.txt");
	while (getline(f, s)) {
		if (regex_search(s, match, re) == true) {
			string str = match.str(1);
			char axis = str[0];
			int i1 = stoi(match.str(2));
			int i2 = stoi(match.str(3));
			int i3 = stoi(match.str(4));
			if (axis == 'x') {
				if (ymax < i3) {
					ymax = i3;
				}
				if (ymin > i2) {
					ymin = i2;
				}
				for (int i = i2; i <= i3; i++) {
					A[i1][i] = 1;
				}
			}
			else {
				if (ymax < i1) {
					ymax = i1;
				}
				if (ymin > i1) {
					ymin = i1;
				}
				for (int i = i2; i <= i3; i++) {
					A[i][i1] = 1;
				}
			}
		}
	}
	cout << ymin << "," << ymax << endl;

	countwater = 0;
	countstill = 0;
	cout << endl;
	traverse(500, 0);

	/*for (int j = ymin; j < ymax+1; j++) {
		for (int i = 450; i < 640; i++) {
			cout << A[i][j];
		}
		cout << endl;
	}*/
	cout << "The number of water tiles is " << countwater << endl;
	cout << "The number of still water is " << countstill << endl;

	return 0;
}