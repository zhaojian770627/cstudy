//============================================================================
// Name        : MemManage.cpp
// Author      : zhaojian
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "DynMem.h"
#include <iostream>
using namespace std;

int main() {
	DynMem dynMem;
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	void *p=dynMem.NewPtr(16);
	cout << p << endl; // prints !!!Hello World!!!
	cout << sizeof(Header) << endl;
	return 0;
}
