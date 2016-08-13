/*
 * Text.h
 *
 *  Created on: 2016��8��13��
 *      Author: Administrator
 */

#ifndef TEXT_H_
#define TEXT_H_

#include "Line.h"
#include <iostream>
typedef Line *LinPtr;

class Text {
	int MinSize;
	LinPtr *LinesPtr;	// ������
	short size;			// LinesPtr�е�����
	short used;			// �����е���Ŀ
	short WordLine;		// ��ǰ��
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
