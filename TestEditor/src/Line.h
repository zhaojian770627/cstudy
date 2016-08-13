/*
 * Line.h
 *
 *  Created on: 2016年8月13日
 *      Author: Administrator
 */

#ifndef LINE_H_
#define LINE_H_

#include "Consts.h"
#include <ctype.h>
#include <string.h>
#include <iostream>

using namespace std;

class Line {
	int MinSize;	// 数据空间的最小尺寸
	char *data;		// 行数据
	short size;		// data大小
	short used;		// data中已用字符数
	short WordPos;	// 当前字位置
public:
	Line(const char *str="");
	void Insert(short from,short to,const char *str="");
	bool Empty();
	bool GetWord(char *word);
	friend istream & operator>>(istream &in,Line &line);
	friend ostream & operator<<(ostream &in,Line &line);
	~Line(){
		delete data;
	}
};

#endif /* LINE_H_ */
