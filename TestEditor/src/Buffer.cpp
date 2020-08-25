/*
 * Buffer.cpp
 *
 *  Created on: 2016��8��13��
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
	if (buf[line].len > rMargin) {	// �ռ乻��
		if (line < BuffLines - 1) {
			++line;
			buf[line].nWords = buf[line].len = 0;
		} else
			return false;		//����������
	}
	if (buf[line].nWords == 0 && lMargin > 0) {	// ������߿�
		for (int i = 0; i < lMargin; ++i)
			buf[line].data[i] = ' ';
		buf[line].len = lMargin;
	}
	if (len > rMargin - lMargin) {	// �ֳ������г�����������
		int part = rMargin - buf[len].len;
		char save = word[part];
		word[part] = '\0';
		PutWord(word);			//��һ����
		word[part] = save;
		return PutWord(word + part);	//�ڶ�����
	}
	strncpy(buf[line].data + buf[line].len, word, len);
	buf[line].len += len;
	if (buf[line].len < rMargin)	// �ÿո񽫵��ʷֿ�
		buf[line].data[buf[line].len++] = ' ';
	buf[line].data[len=buf[line].len]='\0';
	buf[line].nWords++;
	return true;
}

Buffer::~Buffer() {
	// TODO Auto-generated destructor stub
}

