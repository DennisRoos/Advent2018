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

vector<int> v;

int main(int argc, char * argv[])
{
	v.push_back(3);
	v.push_back(7);
	int elf1 = 0;
	int elf2 = 1;
	int size = 702831;
	while (true){
		int n = v[elf1] + v[elf2];
		if (n >= 10) {
			v.push_back(1);
			int s = v.size();
			if ( v[s - 2] == 3 && v[s - 3] == 8 && v[s - 4] == 2 && v[s - 5] == 0 && v[s - 6] == 7) {
				cout << "First appeared after " << s - 6 << " recipes" << endl;
				break;
			}
			v.push_back(n - 10);
		}
		else {
			v.push_back(n);
			int s = v.size();
			if (n == 1 && v[s - 2] == 3 && v[s - 3] == 8 && v[s - 4] == 2 && v[s - 5] == 0 && v[s - 6] == 7) {
				cout << "First appeared after " << s - 6 << " recipes" << endl;
				break;
			}
		}
		elf1 = (elf1 + 1 + v[elf1]) % v.size();
		elf2 = (elf2 + 1 + v[elf2]) % v.size();
	}
	for (int i = 0; i < 10; i++) {
		cout << v[size + i];
	}
	cout << endl;



	return 0;
}