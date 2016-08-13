//============================================================================
// Name        : TestEditor.cpp
// Author      : zhaojian
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Line.h"
using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	Line line("abc efgh");
	char s[30];
	line.GetWord(s);
	cout<<line<<endl;
	cout<<s<<endl;
	return 0;
}
