/*
 * Buffer.cpp
 *
 *  Created on: 2016年8月13日
 *      Author: Administrator
 */

#include "Buffer.h"

Buffer::Buffer() {
	for (int i = 0; i < BuffLines; ++i) {
		buf[i].len = buf[i].nWords = 0;
		buf[i].data[0] = '\0';
	}
	line = 0;
}

bool Buffer::PutWord(char *word) {
	int len = strlen(word);
	if (buf[line].len > rMargin) {	// 空间够否
		if (line < BuffLines - 1) {
			++line;
			buf[line].nWords = buf[line].len = 0;
		} else
			return false;		//缓冲区已满
	}
	if (buf[line].nWords == 0 && lMargin > 0) {	// 构造左边空
		for (int i = 0; i < lMargin; ++i)
			buf[line].data[i] = ' ';
		buf[line].len = lMargin;
	}
	if (len > rMargin - lMargin) {	// 字长超过行长，将字折行
		int part = rMargin - buf[len].len;
		char save = word[part];
		word[part] = '\0';
		PutWord(word);			//第一部分
		word[part] = save;
		return PutWord(word + part);	//第二部分
	}
	strncpy(buf[line].data + buf[line].len, word, len);
	buf[line].len += len;
	if (buf[line].len < rMargin)	// 用空格将单词分开
		buf[line].data[buf[line].len++] = ' ';
	buf[line].data[len=buf[line].len]='\0';
	buf[line].nWords++;
	return true;
}

Buffer::~Buffer() {
	// TODO Auto-generated destructor stub
}

