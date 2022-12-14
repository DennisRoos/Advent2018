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

struct node {
	int data;
	node *prev;
	node *next;
	node(int d, node *p, node *n): data(d), prev(p), next(n){}
};

const int players = 430;
const int marbles = 7158800;
long long score[players];

int main(int argc, char * argv[])
{
	node *current = new node(0, NULL, NULL);
	current->prev = current;
	current->next = current;//initialize circular list
	int player = 0;

	for (int m = 1; m <= marbles; m++) {
		if (m % 23 == 0) {//scoring
			for (int i = 0; i < 7; i++) {
				current = current->prev;
			}
			score[player] += current->data;
			score[player] += m;
			//remove current
			current = current->next;
			node *t = current->prev;
			current->prev = t->prev;
			t->prev->next = current;
			delete t;
		}
		else {//place new marble
			current = current->next;
			node *t = current->next;
			node *n = new node(m, current, t);
			t->prev = n;
			current->next = n;
			current = n;
		}
		player = (player + 1) % players;
	}
	long long s = -1;
	int best = -1;
	for (int i = 0; i < players; i++)
	{
		if (score[i] > s) {
			s = score[i];
			best = i;
		}
	}

	cout << "Best player was " << best + 1 << " with score " << s << endl;
	return 0;
}