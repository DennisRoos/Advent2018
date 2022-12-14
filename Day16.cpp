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

int save[4];
int m[4];
int reg[4];

bool code[16][16];

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
	return;
}

int main(int argc, char * argv[]) {

	regex re("([\\d]+), ([\\d]+), ([\\d]+), ([\\d]+)");
	string s;
	smatch match;
	ifstream f("data.txt");
	int a;
	int b;
	int c;
	int o;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			code[i][j] = true;
		}
	}
	int count = 0;
	while (getline(f, s)) {
		if (s.compare("") == 0) {
			cout << "Done with part 1\n";
			break;
		}
		if (regex_search(s, match, re) == true) {
			save[0] = stoi(match.str(1));
			save[1] = stoi(match.str(2));
			save[2] = stoi(match.str(3));
			save[3] = stoi(match.str(4));
		}
		f >> o;
		f >> a;
		f >> b;
		f >> c;
		getline(f, s);
		getline(f, s);
		if (regex_search(s, match, re) == true) {
			m[0] = stoi(match.str(1));
			m[1] = stoi(match.str(2));
			m[2] = stoi(match.str(3));
			m[3] = stoi(match.str(4));
		}
		getline(f, s);
		int matches = 0;
		for (int i = 0; i < last; i++) {
			op oper = static_cast<op>(i);
			for (int j = 0; j < 4; j++) {
				reg[j] = save[j];
			}
			run(oper, a, b, c);
			bool b = true;
			for (int j = 0; j < 4; j++) {
				if (reg[j] != m[j]) {
					b = false;
					code[o][i] = false;//rule out this combination for the opcodes
					break;
				}
			}
			if (b) {
				matches++;
			}
		}
		if (matches >= 3) {
			count++;
		}


	}

	cout << "Final count of tests with 3 or more results is " << count << endl;

	count = 0;

	while (count < 16) {
		for (int i = 0; i < 16; i++) {
			int c = 0;
			int k;
			for (int j = 0; j < 16; j++) {
				if (code[i][j]) {
					c++;
					k = j;
				}
			}
			if (c == 1) {//figured out one op
				cout << "Opcode " << i << " is number " << k << endl;
				count++;
				for (int l = 0; l < 16; l++) {
					code[l][k] = false;
				}
			}
		}
	}

	for (int j = 0; j < 4; j++) {
		reg[j] = 0;
	}
	while (f >> o) {
		f >> a;
		f >> b;
		f >> c;
		op operation = static_cast<op>(o);
		run(operation, a, b, c);
	}

	cout << reg[0] << endl;
	return 0;
}