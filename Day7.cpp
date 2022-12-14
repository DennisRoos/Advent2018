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

vector<int> s;
vector<int> t;

struct worker {
	int current;
	int time;
	worker():current(-1),time(0){}
};

worker elves[5];

int A[26];

int main(int argc, char * argv[]) {

	regex re("([A-Z]) must be finished before step ([A-Z]) can begin");
	string str;
	smatch match;
	ifstream f("data.txt");
	while (getline(f, str)) {
		if (regex_search(str, match, re) == true) {
			int a = match.str(1)[0] - 'A';
			s.push_back(a);
			a = match.str(2)[0] - 'A';
			t.push_back(a);
		}
	}
	for (int i = 0; i < 26; i++) {
		A[i] = 0;
	}
	int done = 0;
	int steps = 0;
	while (done < 26) {
		for (int w = 0; w < 5; w++) {
			int c = elves[w].current;
			if (elves[w].current != -1) {
				elves[w].time--;
				if (elves[w].time == 0) {
					A[c] = 2;
					elves[w].current = -1;
					done++;
					cout << "At the start of " << steps << " worker " << w << " finished " << char(c + 'A') << endl;
				}
			}
		}
		for (int w = 0; w < 5; w++) {
			if (elves[w].current == -1) {
				for (int i = 0; i < 26; i++) {
					bool b = true;
					for (int j = 0; j < s.size(); j++) {
						if (A[i] != 0 || (t[j] == i && A[s[j]] != 2)) {//can't do this step
							b = false;
						}
					}
					if (b) {
						cout << "During step " << steps << " worker " << w << " started task " << char(i + 'A') << endl;
						A[i] = 1;
						elves[w].current = i;
						elves[w].time = i + 61;
						break;
					}
				}
			}
		}
		steps++;
	}
	cout << endl << "steps: " << steps - 1 << endl;




	return 0;
}