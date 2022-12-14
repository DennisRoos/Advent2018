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

string s;
int cur;
int A[300][300];

void traverse(int x, int y) {
	while(!(s[cur] == ')' || s[cur] == '|' || s[cur] == '$')) {
		char c = s[cur];
		if (c == 'N') {
			A[x][y - 1] = -2;
			A[x][y - 2] = 999999;
			y = y - 2;
		}
		else if (c == 'S') {
			A[x][y + 1] = -2;
			A[x][y + 2] = 999999;
			y = y + 2;
		}
		else if (c == 'E') {
			A[x + 1][y] = -1;
			A[x + 2][y] = 999999;
			x = x + 2;
		}
		else if (c == 'W') {
			A[x - 1][y] = -1;
			A[x - 2][y] = 999999;
			x = x - 2;
		}
		else if (c == '(') {
			while (s[cur] != ')') {
				cur++;
				traverse(x, y);
			}
		}
		cur++;
	}
	return;
}

void findPath(int x, int y, int d) {
	if (A[x][y] <= d) {
		return;
	}
	A[x][y] = d;
	if (A[x - 1][y] == -1) {
		findPath(x - 2, y, d + 1);
	}
	if (A[x + 1][y] == -1) {
		findPath(x + 2, y, d + 1);
	}
	if (A[x][y-1] == -2) {
		findPath(x, y-2, d + 1);
	}
	if (A[x][y+1] == -2) {
		findPath(x, y+2, d + 1);
	}
	return;
}

int main(int argc, char * argv[])
{


	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		cur = 1;
		A[150][150] = 999999;
		infile >> s;
		traverse(150, 150);
		cout << "regex read and map created" << endl;
		for (int j = 40; j < 260; j++) {
			for (int i = 50; i < 246; i++) {
				int k = A[i][j];
				if (k == 0) {
					cout << '#';
				}
				else if (k == -1) {
					cout << '|';
				}
				else if (k == -2) {
					cout << '-';
				}
				else {
					cout << '.';
				}
			}
			cout << endl;
		}
		findPath(150, 150, 1);
		int largest = 1;
		int count = 0;
		for (int j = 0; j < 300; j++) {
			for (int i = 0; i < 300; i++) {
				if (A[i][j] > 1000) {
					count++;
				}
				if (A[i][j] > largest) {
					largest = A[i][j];
				}
			}
		}
		cout << "Longest shortest path has " << (largest - 1)  << " doors." << endl;
		cout << "There are " << count << " rooms with paths of 1000 doors or longer" << endl;

	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}