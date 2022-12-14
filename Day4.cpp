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


struct entry
{
	int month;
	int day;
	int hour;
	int minute;
	int g;

	entry(int m, int d, int h, int min, int s) : month(m),day(d),hour(h),minute(min),g(s) {}
};

struct less_than_angle
{
	inline bool operator() (const entry& a1, const entry& a2)
	{
		if (a1.month != a2.month) {
			return (a1.month < a2.month);
		}
		else if (a1.day != a2.day) {
			return (a1.day < a2.day);
		}
		else if (a1.hour != a2.hour) {
			return (a1.hour < a2.hour);
		}
		else {
			return (a1.minute < a2.minute);
		}
	}
};


struct guard
{
	int number;
	int S[60];
	int total;
	guard(int id, int t): number(id), total(t) {}
};


vector<entry> v;
vector<guard> G;

int findGuard(int id) {
	for(int i = 0; i < G.size(); i++){
		if (G[i].number == id) {//found it in the list already
			return i;
		}
	}
	guard newguard = guard(id,0);
	for (int i = 0; i < 60; i++) {
		newguard.S[i] = 0;

	}
	G.push_back(newguard);
	return G.size() - 1;
}

int main(int argc, char * argv[]) {

	regex re("([\\d][\\d])-([\\d][\\d]) ([\\d][\\d]):([\\d][\\d]). (Guard #([\\d]+)|falls|wakes)");
	string s;
	smatch match;
	ifstream f("data.txt");
	int k = 0;
	while (getline(f, s)) {
		k++;
		if (regex_search(s, match, re) == true) {
			int month = stoi(match.str(1));
			int day = stoi(match.str(2));
			int hour = stoi(match.str(3));
			int minute = stoi(match.str(4));
			int g;
			if (match.str(5) == "falls") {
				g = -1;
			}
			else if (match.str(5) == "wakes") {
				g = -2;
			}
			else {
				g = stoi(match.str(6));
			}
			entry e = entry(month, day, hour, minute, g);
			v.push_back(e);
		}
	}
	sort(v.begin(), v.end(), less_than_angle());
	int i = 0;
	int current = 0;
	while (i < v.size()) {
		entry e = v[i];
		if (e.g >= 0) {//new day, new guard
			current = findGuard(e.g);
			i++;
		}
		else {
			int start = e.minute;
			e = v[i + 1];
			int end = e.minute;
			for (int k = start; k < end; k++) {
				G[current].S[k]++;
			}
			G[current].total = G[current].total + end - start;
			i += 2;
		}
	}
	int largest = -1;
	guard best = guard(-1,0);
	for (auto & g : G) {
		if (g.total > largest) {//find the sleepiest guard
			largest = g.total;
			best = g;
		}
	}

	largest = -1;
	int id = -1;
	int min = -1;

	for (int i = 0; i < 60; i++) {
		if (best.S[i] > largest) {
			largest = best.S[i];
			min = i;
		}
	}

	cout << "The sleepiest guard for part 1 is #" << best.number << " at minute " << min << endl;
	largest = -1;

	for (auto & g : G) {
		for (int i = 0; i < 60; i++) {
			if (g.S[i] > largest) {
				largest = g.S[i];
				min = i;
				id = g.number;
			}
		}
	}
	cout << "The sleepiest guard for part 2 is #" << id << " at minute " << min << endl;

	return 0;
}