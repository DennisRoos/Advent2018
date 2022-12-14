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


struct coordinate
{
	int x;
	int y;
	coordinate(int xx, int yy) : x(xx), y(yy) {}
};


struct less_than_coor
{
	inline bool operator() (const coordinate& a1, const coordinate& a2)
	{
		if (a1.y == a2.y) {
			return a1.x < a2.x;
		}
		return a1.y < a2.y;
	}
};

bool lessCoor(coordinate a1, coordinate a2) {
	if (a1.y == a2.y) {
		return a1.x < a2.x;
	}
	return a1.y < a2.y;
}


struct unit {
	coordinate c;
	bool side; //TRUE is ELF, FALSE is GOBLIN
	int attack;
	int hp;
	unit(coordinate cc, bool s) : c(cc), side(s), attack(3), hp(200) {}
};

struct less_than_unit
{
	inline bool operator() (const unit& a1, const unit& a2)
	{
		if (a1.c.y == a2.c.y) {
			return a1.c.x < a2.c.x;
		}
		return a1.c.y < a2.c.y;
	}
};


struct path {
	coordinate c;
	int depth;
	path(coordinate cc, int d) : c(cc), depth(d) {}
};

vector<unit> v;
int A[32][32];
int B[32][32];
int rounds;

bool nextToEnemy(bool side, int x, int y) {
	if (side) {//u is an Elf
		return (A[x - 1][y] == -3 || A[x + 1][y] == -3 || A[x][y - 1] == -3 || A[x][y + 1] == -3);
	}
	else {
		return (A[x - 1][y] == -2 || A[x + 1][y] == -2 || A[x][y - 1] == -2 || A[x][y + 1] == -2);
	}
}

int findUnit(int x, int y) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i].c.x == x && v[i].c.y == y) {
			return i;
		}
	}
	return -1;
}

bool Attack(int ui) {
	unit u = v[ui];
	int x = u.c.x;
	int y = u.c.y;
	int lowest = 9999;
	int index;
	int best;
	if (u.side) {//u is an Elf
		if (A[x][y - 1] == -3) {
			index = findUnit(x, y - 1);
			if (v[index].hp < lowest) {
				lowest = v[index].hp;
				best = index;
			}
		}
		if (A[x - 1][y] == -3) {
			index = findUnit(x - 1, y);
			if (v[index].hp < lowest) {
				lowest = v[index].hp;
				best = index;
			}
		}
		if (A[x + 1][y] == -3) {
			index = findUnit(x + 1, y);
			if (v[index].hp < lowest) {
				lowest = v[index].hp;
				best = index;
			}
		}
		if (A[x][y + 1] == -3) {
			index = findUnit(x, y + 1);
			if (v[index].hp < lowest) {
				lowest = v[index].hp;
				best = index;
			}
		}
	}
	else {//it's a goblin
		if (A[x][y - 1] == -2) {
			index = findUnit(x, y - 1);
			if (v[index].hp < lowest) {
				lowest = v[index].hp;
				best = index;
			}
		}
		if (A[x - 1][y] == -2) {
			index = findUnit(x - 1, y);
			if (v[index].hp < lowest) {
				lowest = v[index].hp;
				best = index;
			}
		}
		if (A[x + 1][y] == -2) {
			index = findUnit(x + 1, y);
			if (v[index].hp < lowest) {
				lowest = v[index].hp;
				best = index;
			}
		}
		if (A[x][y + 1] == -2) {
			index = findUnit(x, y + 1);
			if (v[index].hp < lowest) {
				lowest = v[index].hp;
				best = index;
			}
		}
	}	
	index = best;
	v[index].hp -= u.attack;
	//cout << "Unit at " << u.c.x << "," << u.c.y << " attacks unit at " << v[index].c.x << "," << v[index].c.y << " HP now at " << v[index].hp << endl;
	if (v[index].hp <= 0) {
		A[v[index].c.x][v[index].c.y] = 999999;
		v.erase(v.begin() + index);
		if (index < ui) {
			return true;
		}
	}
	return false;
}

bool battleWon(bool b) {
	if (b) {//are there goblins left?
		for (int i = 0; i < v.size(); i++) {
			if (v[i].side == false) {
				return false;
			}
		}
	}
	else {//are there elves left?
		for (int i = 0; i < v.size(); i++) {
			if (v[i].side == true) {
				return false;
			}
		}
	}
	return true;
}

path lessPath(path p1, path p2) {
	if (p1.depth != p2.depth) {
		if (p1.depth < p2.depth) {
			return p1;
		}
		else {
			return p2;
		}
	}
	else {
		if (lessCoor(p1.c, p2.c)) {
			return p1;
		}
		else {
			return p2;
		}
	}
}

bool lowerPath(path p1, path p2) {
	if (p1.depth != p2.depth) {
		return (p1.depth < p2.depth);
	}
	else {
		return lessCoor(p1.c, p2.c);
	}
}

path traverse(bool side, int x, int y, int d) {
	if (B[x][y] < 0) {//intraversable terrain
		return path(coordinate(x, y), 999999);
	}
	if (B[x][y] <= d) {//we previously found a shorter/equally distant path to this point, no need to keep searching
		return path(coordinate(x,y),999999);
	}
	B[x][y] = d;
	if (nextToEnemy(side,x,y)) {
		return path(coordinate(x, y), d);
	}
	path pn = traverse(side, x, y - 1, d + 1);
	path pw = traverse(side, x-1, y, d + 1);
	path pe = traverse(side, x + 1, y, d + 1);
	path ps = traverse(side, x, y + 1, d + 1);
	return lessPath(lessPath(pn, pw), lessPath(pe, ps));
}

void moveUnit(int i) {
	for (int k = 0; k < 32; k++) {
		for (int j = 0; j < 32; j++) {
			B[k][j] = A[k][j];
		}
	}
	bool side = v[i].side;
	int x = v[i].c.x;
	int y = v[i].c.y;
	path pn = traverse(side, x, y - 1, 1);
	path pw = traverse(side, x - 1, y, 1);
	path pe = traverse(side, x + 1, y, 1);
	path ps = traverse(side, x, y + 1, 1);
	path bp = lessPath(lessPath(pn, pw), lessPath(pe, ps));


	if (bp.depth > 9999) {//no enemy in range
		return;
	}
	else {
		if (pn.depth == bp.depth && pn.c.x == bp.c.x && bp.c.y == pn.c.y) {//best path is north
			//move north
			A[x][y] = 999999; 
			v[i].c.y--;
			if (side) {
				A[x][y - 1] = -2;
			}
			else {
				A[x][y - 1] = -3;
			}
		}
		else if(pw.depth == bp.depth && pw.c.x == bp.c.x && bp.c.y == pw.c.y) {//best path is west
			A[x][y] = 999999;
			v[i].c.x--;
			if (side) {
				A[x-1][y] = -2;
			}
			else {
				A[x-1][y] = -3;
			}
		}
		else if (pe.depth == bp.depth && pe.c.x == bp.c.x && bp.c.y == pe.c.y) {//best path is west
			A[x][y] = 999999;
			v[i].c.x++;
			if (side) {
				A[x + 1][y] = -2;
			}
			else {
				A[x + 1][y] = -3;
			}
		}
		else if (ps.depth == bp.depth && ps.c.x == bp.c.x && bp.c.y == ps.c.y) {//best path is west
			A[x][y] = 999999;
			v[i].c.y++;
			if (side) {
				A[x][y+1] = -2;
			}
			else {
				A[x][y+1] = -3;
			}
		}
	}
	return;


}

void Battle() {
	while (true) {
		cout << "round " << rounds << endl;
		/*for (int j = 0; j < 32; j++) {
			for (int i = 0; i < 32; i++) {
				int c = A[i][j];
				if (c == -1) {
					cout << '#';
				}
				else if (c == -2) {
					cout << 'E';
				}
				else if (c == -3) {
					cout << 'G';
				}
				else {
					cout << '.';
				}
			}
			cout << endl;
		}*/

		for (int i = 0; i < v.size(); i++) {
			if (battleWon(v[i].side)) {
				return;
			}
			bool b = false;;
			if (nextToEnemy(v[i].side, v[i].c.x, v[i].c.y)) {//no need to move, can just attack
				b = Attack(i);
			}
			else {
				moveUnit(i);
				if (nextToEnemy(v[i].side, v[i].c.x, v[i].c.y)) {//no need to move, can just attack
					b = Attack(i);
				}
			}
			if (b) {
				i--;
			}
		}
		sort(v.begin(), v.end(), less_than_unit());//resort the units to reading order
		rounds++;
	}
}


int main(int argc, char * argv[])
{


	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		rounds = 0;
		int j = 0;
		while (infile >> s) {
			int i = 0;
			while (i < s.size()) {
				char c = s[i];
				if (c == '#'){
					A[i][j] = -1;
				}
				else if (c == '.') {
					A[i][j] = 99999;
				}
				else if (c == 'E') {
					coordinate co = coordinate(i, j);
					unit u = unit(co, true);
					v.push_back(u);
					A[i][j] = -2;
				}
				else if (c == 'G') {
					coordinate co = coordinate(i, j);
					unit u = unit(co, false);
					v.push_back(u);
					A[i][j] = -3;
				}
				i++;
			}
			j++;
		}

		Battle();

		int totalHP = 0;
		for (int i = 0; i < v.size(); i++) {
			cout << v[i].hp << endl;
			totalHP += v[i].hp;
		}
		int outcome = totalHP * rounds;
		cout << "outcome was " << outcome << endl;



	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}