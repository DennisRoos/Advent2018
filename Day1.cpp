#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <list>

using namespace std;

int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");
	
	int A[1000];
	int frequency = 0;
	list<int> l;
	auto it = 0;
	l.push_front(frequency);
	if (infile.is_open())
	{
		int num;
		int answer = 0;
		int i = 0;
		while (infile >> num)
		{
			A[i] = num;
			i++;
		}

		while (true) {
			for (int j = 0; j < i; j++) {
				frequency = frequency + A[j];
				auto it = std::find(l.begin(), l.end(), frequency);
				if (it == l.end()) {
					l.push_back(frequency);
					cout << frequency << "\n";
				}
				else {
					//found the frequency!
					
					//calculate final answer
					cout << "Final answer is " << frequency << "\n";
					return 0;
				}
			}
		}


	}
	else {

		cout << "can't find file?\n";
	}



}