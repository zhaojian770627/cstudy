//============================================================================
// Name        : c161.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "compare.h"

#include "compare.cpp";

using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	int r1 = compare(3, 4);
	cout << r1 << endl;

	int r2 = compare(33.6, 4.5);
	cout << r2 << endl;
	return 0;
}
