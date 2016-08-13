/*
 * Ruler.cpp
 *
 *  Created on: 2016Äê8ÔÂ13ÈÕ
 *      Author: Administrator
 */

#include "Ruler.h"

Ruler::Ruler() {
	lMargin = 0;
	rMargin = MaxRMargin;
	for (int i = 0; i < 10; ++i)
		tabs[i] = (i + 1) * 8;
	indent = leftInd;
}

void
Ruler::Margins(short lMarg,short rMarg){
lMargin=lMarg;
rMargin=rMarg;
}

void
Ruler::Tabs(short tabl ...){
	va_list args;
	short tab=tabl;
	int i=0;
	va_start(args,tabl);
	do{
		tabs[i++]=tab;
	}while((tab=va_arg(args,short))!=0 && i<10);
	va_end(args);
}

Ruler::~Ruler() {
	// TODO Auto-generated destructor stub
}

