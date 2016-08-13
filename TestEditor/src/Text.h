/*
 * Text.h
 *
 *  Created on: 2016年8月13日
 *      Author: Administrator
 */

#ifndef TEXT_H_
#define TEXT_H_

#include "Line.h"
#include <iostream>
typedef Line *LinPtr;

class Text {
	int MinSize;
	LinPtr *LinesPtr;	// 行向量
	short size;			// LinesPtr中的行数
	short used;			// 已用行的数目
	short WordLine;		// 当前行
public:
	Text();
	~Text();
	void NewLine(short pos, Line * line);
	void RmvLine(short pos);
	void Insert(short pos, short from, short to, const char* str = "");
	bool GetWord(char *word);
	friend istream& operator>>(istream& in, Text& text);
	friend ostream& operator<<(ostream& out, Text& text);
};

#endif /* TEXT_H_ */
