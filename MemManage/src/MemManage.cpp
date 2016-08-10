//============================================================================
// Name        : MemManage.cpp
// Author      : zhaojian
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
//#include "DynMem.h"

#include <iostream>
#include "RelMem.h"

using namespace std;

int main() {
	/*
	 DynMem dynMem;
	 void *p1=dynMem.NewPtr(16);
	 cout <<"p1:"<< p1 << endl;
	 void *p2=dynMem.NewPtr(16);
	 cout <<"p2:"<< p2 << endl;
	 void *p3=dynMem.NewPtr(16);
	 cout <<"p3:"<< p3 << endl;
	 dynMem.FreePtr(p1);
	 dynMem.FreePtr(p3);
	 dynMem.FreePtr(p2);
	 */
	// 测试可重定位的内存管理类
	RelMem relMem;
	relMem.NewHand(30);
	return 0;
}
