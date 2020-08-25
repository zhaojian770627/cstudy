/*
 * Buffer.h
 *
 *  Created on: 2016��8��13��
 *      Author: Administrator
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include "Consts.h"
#include "Ruler.h"
#include "string.h"

class Buffer : public virtual Ruler {
	struct BufLine{
		short len;					// �г�
		short nWords;				// һ���е�����
		char data[MaxRMargin+2];	// ������
	};

	static BufLine buf[BuffLines];	// ������
	static short line;				// ��ǰ��
	void IndentLine(short line);
public:
	Buffer();
	bool PutWord(char *word);
	void IndentText();
	int BufLines(){
		return line;
	}
	const char* operator[](short line);
	virtual ~Buffer();
};

#endif /* BUFFER_H_ */
