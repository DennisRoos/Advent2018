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

int A[1000][1000];
string B[1360];


int main(int argc, char * argv[]){

	regex re("#[\\d]+ @ ([\\d]+),([\\d]+): ([\\d]+)x([\\d]+)");
	string s; 
	smatch match;
	ifstream f("data.txt");
	int k = 0;
	while (getline(f, s)) {
		B[k] = s;
		k++;
		if (regex_search(s, match, re) == true) {
			int x = stoi(match.str(1));
			int y = stoi(match.str(2));
			int xSize = stoi(match.str(3));
			int ySize = stoi(match.str(4));

			for (int i = 0; i < ySize; i++) {
				for (int j = 0; j < xSize; j++) {
					A[x + j][y + i]++;
				}
			}
		}
	}
	int count = 0;

	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			if (A[i][j] > 1) {
				count++;
			}
		}
	}
	cout << "Count is " << count << endl;

	for (int k = 0; k < 1360; k++) {
		s = B[k];
		if (regex_search(s, match, re) == true) {
			int x = stoi(match.str(1));
			int y = stoi(match.str(2));
			int xSize = stoi(match.str(3));
			int ySize = stoi(match.str(4));
			bool b = true;
			for (int i = 0; i < ySize; i++) {
				for (int j = 0; j < xSize; j++) {
					if (A[x + j][y + i] > 1) {
						b = false;
					}
				}
			}
			if (b) {
				cout << "The correct ID is " << k + 1 << endl;
				return 0;
			}
		}
	}
}