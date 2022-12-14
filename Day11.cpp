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

int A[301][301];

int main(int argc, char * argv[]) {
	for (int y = 1; y <= 300; y++) {
		for (int x = 1; x <= 300; x++) {
			int rackID = x + 10;
			int p = rackID * y;
			p += 9798;//puzzle input
			p *= rackID;
			p = (p / 100) % 10;
			p -= 5;
			A[x][y] = p;
		}
	}
	int bestx;
	int besty;
	int bests;
	int h = 0;
	for (int size = 1; size <= 300; size++) {
		cout << size << endl;
		for (int y = 1; y <= 301-size; y++) {
			for (int x = 1; x <= 301-size; x++) {
				int c = 0;
				for (int i = 0; i < size; i++) {
					for (int j = 0; j < size; j++) {
						c += A[x + j][y + i];
					}
				}
				if (c > h) {
					bestx = x;
					besty = y;
					bests = size;
					h = c;

					cout << "Best coordinate so far is " << bestx << "," << besty << " of size " << bests << " with power " << h << endl;
				}
			}
		}
	}
	cout << "Best coordinate is " << bestx << "," << besty << " of size " << bests << " with power " << h << endl;

	return 0;
}