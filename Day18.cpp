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

int A[52][52];
int B[52][52];

int countNeighbors(int x, int y, int t) {
	int count = 0;
	if (A[x - 1][y - 1] == t) {
		count++;
	}
	if (A[x - 1][y] == t) {
		count++;
	}
	if (A[x - 1][y + 1] == t) {
		count++;
	}
	if (A[x][y - 1] == t) {
		count++;
	}
	if (A[x][y + 1] == t) {
		count++;
	}
	if (A[x + 1][y - 1] == t) {
		count++;
	}
	if (A[x + 1][y] == t) {
		count++;
	}
	if (A[x + 1][y + 1] == t) {
		count++;
	}
	return count;
}

int main(int argc, char * argv[])
{


	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		long long total = 0;
		int j = 0;
		string s;
		while (infile >> s) {
			int i = 0;
			while (i < s.size()) {
				char c = s[i];
				if (c == '|') {
					A[i+1][j+1] = 1;
					B[i+1][j+1] = 1;
				}
				else if (c == '#') {
					A[i+1][j+1] = 2;
					B[i+1][j+1] = 2;
				}
				i++;
			}
			j++;
		}
		for (int j = 1; j <= 50; j++) {
			for (int i = 1; i <= 50; i++) {
				if (A[i][j] == 0) {//currently trees
					cout << '.';
				}
				else if (A[i][j] == 1) {//currently trees
					cout << '|';
				}
				else if (A[i][j] == 2) {//currently trees
					cout << '#';
				}
			}
			cout << endl;
		}
		for (int g = 0; g < 1000000000; g++) {
			for (int i = 1; i <= 50; i++) {
				for (int j = 1; j <= 50; j++) {
					if (A[i][j] == 0) {//currently empty
						if (countNeighbors(i, j, 1) >= 3) {
							B[i][j] = 1;
						}
						else {
							B[i][j] = 0;
						}
					}
					else if (A[i][j] == 1) {//currently trees
						if (countNeighbors(i, j, 2) >= 3) {
							B[i][j] = 2;
						}
						else {
							B[i][j] = 1;
						}
					}
					else {//currently lumberyard
						if (countNeighbors(i, j, 2) >= 1 && countNeighbors(i, j, 1) >= 1) {
							B[i][j] = 2;
						}
						else {
							B[i][j] = 0;
						}
					}
				}
			}
			int trees = 0;
			int lumber = 0;
			
			for (int j = 1; j <= 50; j++) {
				for (int i = 1; i <= 50; i++) {
					A[i][j] = B[i][j];
					if (A[i][j] == 1) {//currently trees
						trees++;
					}
					else if (A[i][j] == 2) {
						lumber++;
					}
				}
			}
			total = trees * lumber;
			

			cout << g << ": " << trees << " acres of trees, and " << lumber << " lumberyards, for a resource value of " << total << endl;

		}

		



	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}