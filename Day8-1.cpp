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

int traverse(int index) {
	int length = index;
	int children = A[index];
	int metadata = A[index + 1];//save header info
	index += 2;
	for (int i = 0; i < children; i++) {//mine all children
		int j = traverse(index);
		index += j;
	}
	for (int i = 0; i < metadata; i++) {//add all metadata
		total += A[index];
		index++;
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
		for (int i = 0; i < 20; i++) {
			cout << i << ": " << A[i] << endl;
		}
		int c = traverse(0);
		cout << c << ": total metadata is " << total << endl;



	}
	else {

		cout << "can't find file?\n";
	}



}