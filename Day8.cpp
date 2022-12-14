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


int A[20000];
int total;
int l;

int traverse(int index, int &value) {
	int length = index;
	int children = A[index];
	int metadata = A[index + 1];//save header info
	index += 2;
	value = 0;
	if (children == 0) {//no child nodes
		for (int i = 0; i < metadata; i++) {
			int t = A[index];
			value += t;
			total += t;
			index++;
		}
	}
	else {//there are child nodes
		int V[20];
		for (int i = 1; i <= children; i++) {
			int v = 0;
			index += traverse(index, v);
			V[i] = v;
		}
		for (int i = 0; i < metadata; i++) {
			int m = A[index];
			total += m;
			index++;
			if (m != 0 && m <= children) {//valid metadata
				value += V[m];
			}
		}
	}
	return index - length;
}


int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");
	total = 0;
	l = 0;
	if (infile.is_open())
	{
		int num;
		while (infile >> num)
		{
			A[l] = num;
			l++;
		}
		cout << l << endl;
		int v = 0;
		int c = traverse(0, v);
		cout << "Total is " << total << endl;
		cout << "Value of root is " << v << endl;



	}
	else {

		cout << "can't find file?\n";
	}



}