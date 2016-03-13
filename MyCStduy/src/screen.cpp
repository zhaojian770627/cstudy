/*
 * screen.cpp
 *
 *  Created on: 2016Äê3ÔÂ12ÈÕ
 *      Author: zhaojian
 */

#include "screen.h"

int Screen::si=0;

char Screen::get(index r, index c) const {
	index row = r * width;
	return contents[row + c];
}

inline Screen::index Screen::get_cursor() const {
	return cursor;
}

Screen& Screen::set(char c)
{
	contents[cursor]=c;
	return *this;
}

Screen& Screen::move(index r,index c)
{
	index row=r*width;
	cursor=row+c;
	return *this;
}
