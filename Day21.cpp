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

enum op
{
	MULI,
	BORR,
	GTRI,
	EQRI,
	GTRR,
	EQIR,
	ADDI,
	SETR,
	MULR,
	ADDR,
	BORI,
	BANI,
	SETI,
	EQRR,
	BANR,
	GTIR,
	last
};

long long reg[6];
op ops[200];
int A[200];
int B[200];
int C[200];
int ip;


void run(op o, int a, int b, int c) {
	switch (o)
	{
	case ADDR: reg[c] = reg[a] + reg[b]; break;
	case ADDI: reg[c] = reg[a] + b; break;
	case MULR: reg[c] = reg[a] * reg[b]; break;
	case MULI: reg[c] = reg[a] * b; break;
	case BANR: reg[c] = reg[a] & reg[b]; break;
	case BANI: reg[c] = reg[a] & b; break;
	case BORR: reg[c] = reg[a] | reg[b]; break;
	case BORI: reg[c] = reg[a] | b; break;
	case SETR: reg[c] = reg[a]; break;
	case SETI: reg[c] = a; break;
	case GTIR:
		if (a > reg[b]) {
			reg[c] = 1;
		}
		else {
			reg[c] = 0;
		}
		break;
	case GTRI:
		if (reg[a] > b) {
			reg[c] = 1;
		}
		else {
			reg[c] = 0;
		}
		break;
	case GTRR:
		if (reg[a] > reg[b]) {
			reg[c] = 1;
		}
		else {
			reg[c] = 0;
		}
		break;
	case EQIR:
		if (a == reg[b]) {
			reg[c] = 1;
		}
		else {
			reg[c] = 0;
		}
		break;
	case EQRI:
		if (reg[a] == b) {
			reg[c] = 1;
		}
		else {
			reg[c] = 0;
		}
		break;
	case EQRR:
		if (reg[a] == reg[b]) {
			reg[c] = 1;
		}
		else {
			reg[c] = 0;
		}
		break;
	}
	reg[ip]++;
	return;
}

int main(int argc, char * argv[]) {

	regex re("([a-z]+) ([\\d]+) ([\\d]+) ([\\d]+)");
	string s;
	smatch match;
	ifstream f("data.txt");
	int a;
	int b;
	int c;
	int LOC = 0;
	op o;
	getline(f, s);
	ip = s[4] - '0';
	cout << "IP is " << ip << endl;
	while (getline(f, s)) {
		if (regex_search(s, match, re) == true) {
			string str = match.str(1);
			A[LOC] = stoi(match.str(2));
			B[LOC] = stoi(match.str(3));
			C[LOC] = stoi(match.str(4));
			if (str.compare("addi") == 0) {
				o = ADDI;
			}
			else if (str.compare("addr") == 0) {
				o = ADDR;
			}
			else if (str.compare("addr") == 0) {
				o = ADDR;
			}
			else if (str.compare("muli") == 0) {
				o = MULI;
			}
			else if (str.compare("mulr") == 0) {
				o = MULR;
			}
			else if (str.compare("banr") == 0) {
				o = BANR;
			}
			else if (str.compare("bani") == 0) {
				o = BANI;
			}
			else if (str.compare("bori") == 0) {
				o = BORI;
			}
			else if (str.compare("borr") == 0) {
				o = BORR;
			}
			else if (str.compare("seti") == 0) {
				o = SETI;
			}
			else if (str.compare("setr") == 0) {
				o = SETR;
			}
			else if (str.compare("gtri") == 0) {
				o = GTRI;
			}
			else if (str.compare("gtir") == 0) {
				o = GTIR;
			}
			else if (str.compare("gtrr") == 0) {
				o = GTRR;
			}
			else if (str.compare("eqri") == 0) {
				o = EQRI;
			}
			else if (str.compare("eqir") == 0) {
				o = EQIR;
			}
			else if (str.compare("eqrr") == 0) {
				o = EQRR;
			}
			ops[LOC] = o;
			LOC++;
		}


	}
	vector<int> v;
	cout << "Number of lines " << LOC << endl;
	int value = 0;
	while (true) {
		int its = 0;
		for (int i = 1; i < 6; i++) {
			reg[i] = 0;
		}
		reg[0] = value;
		while (reg[ip] >= 0 && reg[ip] < LOC) {
			int i = reg[ip];
			if (i == 28) {
				int d = reg[3];
				for (int j = 0; j < v.size(); j++) {
					if (v[j] == d) {//found a repeated value!
						int sol = v[v.size() - 1];
						cout << "Solution is " << sol << endl;
						return 0;
					}
				}
				cout << "added " << d << endl;
				v.push_back(d);
			}
			run(ops[i], A[i], B[i], C[i]);
			its++;
		}
		cout << its << endl;
		if (its < 1000000) {//terminated before 10000 instructions
			cout << "The program terminated early with initial value " << value << endl;
			return 0;
		}
		value++;
	}

	cout << reg[0] << endl;
	return 0;
}