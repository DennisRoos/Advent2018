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


struct nanobot
{
	int x;
	int y;
	int z;
	int r;
	int min;
	int max;

	nanobot(int xx, int yy, int zz, int rr) : x(xx), y(yy), z(zz), r(rr) {}
};

vector<nanobot> bots;

int main(int argc, char * argv[]) {

	regex re("<(-?[\\d]+),(-?[\\d]+),(-?[\\d]+)>, r=([\\d]+)");
	string s;
	smatch match;
	ifstream f("data.txt");
	while (getline(f, s)) {
		if (regex_search(s, match, re) == true) {
			int x = stoi(match.str(1));
			int y = stoi(match.str(2));
			int z = stoi(match.str(3));
			int r = stoi(match.str(4));
			nanobot n = nanobot(x, y, z, r);
			bots.push_back(n);
		}
	}
	int bestR = 0;
	int bestBot;
	for (int i = 0; i < bots.size(); i++) {
		if (bots[i].r > bestR) {
			bestR = bots[i].r;
			bestBot = i;
		}
	}

	cout << bots.size() << endl;

	int x = bots[bestBot].x;
	int y = bots[bestBot].y;
	int z = bots[bestBot].z;
	int r = bots[bestBot].r;
	int count = 0;
	for (int i = 0; i < bots.size(); i++) {
		if (abs(bots[i].x - x) + abs(bots[i].y - y) + abs(bots[i].z - z) <= r) {
			count++;
		}
	}

	cout << "Number of bots in range of bot " << bestBot << " is " << count << endl;

	//60470000
	for (int i = 0; i < bots.size(); i++) {
		int c = bots[i].x + bots[i].y + bots[i].z;
		bots[i].min = c - bots[i].r;
		bots[i].max = c + bots[i].r;
	}

	int best = 0;
	int closest;
	for (int i = 60470000; i < 60480000; i++) {
		int b = 0;
		for (int j = 0; j < bots.size(); j++) {
			if (i >= bots[j].min && i <= bots[j].max) {
				b++;
			}
		}
		if (b > best) {
			best = b;
			closest = i;
		}
	}

	cout << "Best is " << closest << " in range of " << best << " bots" << endl;

	return 0;
}