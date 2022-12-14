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

struct point {
	int w;
	int x;
	int y;
	int z;
	int c;
	point(int ww, int xx, int yy, int zz, int cc) : w(ww), x(xx), y(yy), z(zz), c(cc) {}
};

vector<point> v;

int manhattan(point p1, point p2) {
	return abs(p1.x - p2.x) + abs(p1.w - p2.w) + abs(p1.y - p2.y) + abs(p1.z - p2.z);
}

int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		int w;
		int x;
		int y;
		int z;
		int num = 0;
		int merges = 0;
		while (infile >> w) {
			infile >> x;
			infile >> y;
			infile >> z;
			point p = point(w, x, y, z, num);
			for (int i = 0; i < v.size(); i++) {
				if (manhattan(p, v[i]) <= 3 && num != v[i].c) {
					merges++;
					int c = v[i].c;
					for (int j = 0; j < v.size(); j++) {
						if (v[j].c == c) {
							v[j].c = num;
						}
					}
				}
			}
			v.push_back(p);
			num++;
		}
		cout << "there were " << num << " points with " << num - merges << " constellations" << endl;

	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}