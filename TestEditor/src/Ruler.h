/*
 * Ruler.h
 *
 *  Created on: 2016年8月13日
 *      Author: Administrator
 */

#ifndef RULER_H_
#define RULER_H_

#include "Consts.h"
#include <stdarg.h>

class Ruler {
protected:
	short lMargin;
	short rMargin;
	short tabs[10];
	Indent indent;	// 缩进
public:
	Ruler();
	void Margins(short LMarg = 0, short rMarg = MaxRMargin);
	void Tabs(short tabl...);
	void indentation(Indent ind) {
		indent=ind;
	}
	virtual ~Ruler();
};

#endif /* RULER_H_ */
