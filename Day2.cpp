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

int main(int argc, char * argv[])
{


	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string A[250];
		int i = 0;
		string s;
		while (infile >> s) {
			A[i] = s;
			i++;
		}
		int smallest = 9999;
		int e1;
		int e2;
		for (int i = 0; i < 249; i++) {
			string s1 = A[i];
			for (int j = i + 1; j < 250; j++) {
				string s2 = A[j];
				int diff = 0;
				for (int k = 0; k < s1.size(); k++) {
					if (s1[k] != s2[k]) {
						diff++;
					}
				}
				if (diff < smallest) {
					e1 = i;
					e2 = j;
					smallest = diff;
				}
			}
		}
		string s1 = A[e1];
		string s2 = A[e2];
		for (int k = 0; k < s1.size(); k++) {
			if (s1[k] == s2[k]) {
				cout << s1[k];
			}
		}
		cout << endl;
	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}