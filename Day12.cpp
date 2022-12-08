#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <list>
#include <string>

using namespace std;

int A[500];
int B[500];
int R[32];

int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string str;
		infile >> str;
		infile >> str;
		infile >> str;
		int prev = 0;
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == '#') {
				A[i + 30] = 1;
			}
		}
		getline(infile, str);
		while (getline(infile,str))
		{
			int c = 0;
			int m = 1;
			for (int i = 0; i < 5; i++) {
				if (str[i] == '#') {
					c += m;
				}
				m *= 2;
			}
			if (str[9] == '#') {
				R[c] = 1;
			}
			else {
				R[c] = 0;
			}
		}
		for (int g = 0; g < 50000000000; g++) {
			for (int i = 0; i < 500; i++) {
				int c = 0;
				int m = 1;
				for (int j = i; j < 5 + i; j++) {
					if (A[j] == 1) {
						c += m;
					}
					m *= 2;
				}
				B[i + 2] = R[c];
			}
			int total = 0;
			for (int i = 0; i < 500; i++) {
				A[i] = B[i];
				if (A[i] == 1) {
					total += i - 30;
				}
			}
			cout << g << ": " << total << " difference " << total - prev << endl;
			prev = total;
		}
	}
	else {

		cout << "can't find file?\n";
	}



}