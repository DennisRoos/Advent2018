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

int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");

	if (infile.is_open())
	{
		string s;
		string in;
		infile >> in;
		s = in;
		int i = 0;
		while (i < s.size() - 1) {
			if (abs(s[i] - s[i + 1]) == 'a' - 'A') {
				s.erase(i, 2);
				if (i > 0) {
					i--;
				}
			}
			else {
				i++;
			}
		}
		std::cout << "the answer for part 1 is size " << s.size() << endl;

		int shortest = 99999;
		in = s;

		for (int j = 0; j < 26; j++) {
			s = in;
			int i = 0;
			while (i < s.size()) {
				if (s[i] == 'a' + j || s[i] == 'A' + j) {
					s.erase(i, 1);
				}
				else {
					i++;
				}
			}
			i = 0;
			while (i < s.size() - 1) {
				if (abs(s[i] - s[i + 1]) == 'a' - 'A') {
					s.erase(i, 2);
					if (i > 0) {
						i--;
					}
				}
				else {
					i++;
				}
			}
			int size = s.size();
			if (size < shortest) {
				shortest = size;
			}
		}
		std::cout << "the answer for part 2 is " << shortest << endl;



	}
	return 0;
}