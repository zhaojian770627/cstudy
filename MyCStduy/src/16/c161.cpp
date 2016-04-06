//============================================================================
// Name        : c161.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "compare.h"
#include "Queue.h"

#include "compare.cpp"
#include "Queue.cc"

using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	int r1 = compare(3, 4);
	cout << r1 << endl;

	int r2 = compare(33.6, 4.5);
	cout << r2 << endl;
	Queue<int> queue;
	queue.push(1);
	queue.push(2);
	queue.pop();
	cout<<queue.front()<<endl;
	return 0;
}
