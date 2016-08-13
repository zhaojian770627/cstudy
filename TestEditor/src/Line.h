/*
 * Line.h
 *
 *  Created on: 2016��8��13��
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
	int MinSize;	// ���ݿռ����С�ߴ�
	char *data;		// ������
	short size;		// data��С
	short used;		// data�������ַ���
	short WordPos;	// ��ǰ��λ��
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
