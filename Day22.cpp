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

int G[200][900];
int E[200][900];
int T[200][900];
int dist[200][900][3];

//type 0 is rocky, can have either, not neither
//type 1 is wet, can have neither or gear
//type 2 is narrow, can have neither or torch

//t = 0: neither
//t = 1: torch
//t = 2: climbing gear

void traverse(int x, int y, int t, int d) {
	if (x < 0 || y < 0 || x >= 200 || y >= 900) {// out of bounds
		return;
	}
	if (d > 1000) {
		return;
	}
	if (T[x][y] == t) {//using gear not suitable for this environment
		return;
	}
	if (dist[x][y][t] <= d) {//already found a better path to this point
		return;
	}
	//cout << x << "," << y << " " << t << " " << d << endl;
	dist[x][y][t] = d;
	traverse(x - 1, y, t, d + 1);
	traverse(x + 1, y, t, d + 1);
	traverse(x, y - 1, t, d + 1);
	traverse(x, y + 1, t, d + 1);
	int here = T[x][y];
	if (here == 0) {
		if (t == 1) {
			traverse(x, y, 2, d + 7);
		}
		else {
			traverse(x, y, 1, d + 7);
		}
	}
	else if (here == 1) {
		if (t == 0) {
			traverse(x, y, 2, d + 7);
		}
		else {
			traverse(x, y, 0, d + 7);
		}
	}
	else {
		if (t == 0) {
			traverse(x, y, 1, d + 7);
		}
		else {
			traverse(x, y, 0, d + 7);
		}
	}
	return;
}


int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");


	string s;
	int xmax = 13;
	int ymax = 704;
	int depth = 9465;
	for (int i = 1; i < 200; i++) {
		G[i][0] = (i * 16807) % 20183;
		E[i][0] = (G[i][0] + depth) % 20183;
	}

	for (int i = 1; i < 900; i++) {
		G[0][i] = (i * 48271) % 20183;
		E[0][i] = (G[0][i] + depth) % 20183;
	}

	for (int i = 1; i < 200; i++) {
		for (int j = 1; j < 900; j++) {
			G[i][j] = (E[i - 1][j] * E[i][j - 1]) % 20183;
			E[i][j] = (G[i][j] + depth) % 20183;
		}
	}
	E[0][0] = depth % 20183;
	G[xmax][ymax] = 0;
	E[xmax][ymax] = depth % 20183;

	int danger = 0;
	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 900; j++) {
			int d = E[i][j] % 3;
			T[i][j] = d;
			for (int k = 0; k < 3; k++) {
				dist[i][j][k] = 99999;
			}
		}
	}

	for (int i = 0; i <= xmax; i++) {
		for (int j = 0; j <= ymax; j++) {
			int d = E[i][j] % 3;
			danger += d;
		}
	}
	cout << "Total danger is " << danger << endl;
	traverse(0, 0, 1, 0);
	cout << "The time it takes to reach the reindeer is " << dist[xmax][ymax][1] << " minutes. " << endl;

	return 0;
}