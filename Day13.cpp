#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <algorithm>  
#include <limits>


using namespace std;


struct minecart
{
	int x;
	int y;
	int d;
	int phase;
	bool C;

	minecart(int xx, int yy, int dd) : x(xx), y(yy), d(dd), phase(0), C(true) {}
};


struct less_than_angle
{
	inline bool operator() (const minecart& a1, const minecart& a2)
	{
		if (a1.y == a2.y) {
			return a1.x < a2.x;
		}
		return a1.y < a2.y;
	}
};

char A[150][150];
char B[150][150];
vector<minecart> m;


void move(int c) {
	if (m[c].d == 0) {//up
		m[c].y--;
	}
	if (m[c].d == 1) {//right
		m[c].x++;
	}
	if (m[c].d == 2) {//down
		m[c].y++;
	}
	if (m[c].d == 3) {//left
		m[c].x--;
	}
	int x = m[c].x;
	int y = m[c].y;
	char a = A[x][y];
	if (a == '\\') {
		if (m[c].d == 0) {//up
			m[c].d = 3;
		}
		else if (m[c].d == 1) {//right
			m[c].d = 2;
		}
		else if (m[c].d == 2) {//down
			m[c].d = 1;
		}
		else if (m[c].d == 3) {//left
			m[c].d = 0;
		}
	}
	else if (a == '/') {
		if (m[c].d == 0) {//up
			m[c].d = 1;
		}
		else if (m[c].d == 1) {//right
			m[c].d = 0;
		}
		else if (m[c].d == 2) {//down
			m[c].d = 3;
		}
		else if (m[c].d == 3) {//left
			m[c].d = 2;
		}
	}
	else if (a == '+') {
		if (m[c].phase == 0) {
			m[c].d = (m[c].d + 3) % 4;
		}
		else if (m[c].phase == 2) {
			m[c].d = (m[c].d + 1) % 4;
		}
		m[c].phase = (m[c].phase + 1) % 3;
	}
	return;
}



int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");


	string s;
	int xmax = 0;
	int ymax = 0;
	if (infile.is_open())
	{
		int h = 0;
		while (getline(infile, s)) {
			for (int i = 0; i < s.size(); i++) {
				char c = s[i];
				A[i][h] = c;
				if (c == 'v') {
					A[i][h] = '|';
					minecart cart = minecart(i, h, 2);
					m.push_back(cart);
				}
				else if (c == '^') {
					A[i][h] = '|';
					minecart cart = minecart(i, h, 0);
					m.push_back(cart);
				}
				else if (c == '>') {
					A[i][h] = '-';
					minecart cart = minecart(i, h, 1);
					m.push_back(cart);
				}
				else if (c == '<') {
					A[i][h] = '-';
					minecart cart = minecart(i, h, 3);
					m.push_back(cart);
				}
			}
			h++;
		}
		int steps = 0;
		bool n = true;
		int size = m.size();
		while (size > 1) {
			steps++;
			//cout << steps << ": " << m.size() << endl;
			/*for (int j = 0; j < 150; j++) {
				for (int i = 0; i < 150; i++) {
					B[i][j] = A[i][j];
				}
			}*/
			for (int a = 0; a < m.size(); a++) {
				if (m[a].C) {
					move(a);
					//B[m[a].x][m[a].y] = 'X';
					for (int b = 0; b < m.size(); b++) {
						if (a != b && m[a].x == m[b].x && m[a].y == m[b].y && m[b].C) {
							cout << "Collision after " << steps << " steps at " << m[a].x << "," << m[a].y << " between " << a << " and " << b << endl;
							m[a].C = false;
							m[b].C = false;
							size -= 2;
							break;
						}
					}
				}
			}

			sort(m.begin(), m.end(), less_than_angle());

			/*for (int j = 0; j < 150; j++) {
				for (int i = 0; i < 150; i++) {
					cout << B[i][j];
				}
				cout << endl;
			}*/

		}
		for (int i = 0; i < m.size(); i++) {
			if (m[i].C) {
				cout << "remaining cart is cart " << i << " at " << m[i].x << "," << m[i].y << endl;
			}
		}

	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}