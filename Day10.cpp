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

struct point {
	int x;
	int y;
	int xv;
	int yv;
	point(int xx, int yy, int xvv, int yvv) :x(xx),y(yy),xv(xvv),yv(yvv)  {}
};

vector<point> points;
char A[200][200];

int main(int argc, char * argv[]) {

	regex re("position=< *(-?[\\d]+), *(-?[\\d]+)> velocity=< *(-?[\\d]+), *(-?[\\d]+)>");
	string str;
	smatch match;
	int time = 10260;
	ifstream f("data.txt");
	while (getline(f, str)) {
		if (regex_search(str, match, re) == true) {
			int x = stoi(match.str(1));
			int y = stoi(match.str(2));
			int xv = stoi(match.str(3));
			int yv = stoi(match.str(4));
			point po = point(x + time * xv, y + time * yv, xv, yv);
			points.push_back(po);
		}
	}

	string s = "p";
	while (true) {
		int b = 0;
		for (int i = 0; i < points.size(); i++) {
			points[i].x += points[i].xv;
			points[i].y += points[i].yv;
		}
		for (int i = 0; i < points.size(); i++) {
			point p = points[i];
			for (int j = 0; j < points.size(); j++) {
				point p2 = points[j];
				if (i != j && ((p.y == p2.y && (p.x == p2.x - 1 || p.x == p2.x + 1)) || (p.x == p2.x && (p.y == p2.y - 1 || p.y == p2.y + 1)))) {
					b++;
					break;
				}
			}
		}
		//cout << time << " " << b << endl;
		if (b > 300) {
			for (int i = 0; i < 200; i++) {
				for (int j = 0; j < 200; j++) {
					A[i][j] = '.';
				}
			}
			for (int i = 0; i < points.size(); i++) {
				if (points[i].x >= 0 && points[i].x < 200 && points[i].y >= 50 && points[i].y < 250) {
					A[points[i].x][points[i].y - 50] = '#';
				}
				else {
					cout << "out of bounds point at " << points[i].x << ", " << points[i].y << endl;
				}
			}

			for (int j = 0; j < 200; j++) {
				for (int i = 0; i < 196; i++) {
					cout << A[i][j];
				}
				cout << endl;
			}
			return 0;
		}
		time++;
	}




	return 0;
}