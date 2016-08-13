/*
 * Buffer.h
 *
 *  Created on: 2016年8月13日
 *      Author: Administrator
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include "Consts.h"
#include "Ruler.h"
#include "string.h"

class Buffer : public virtual Ruler {
	struct BufLine{
		short len;					// 行长
		short nWords;				// 一行中的字数
		char data[MaxRMargin+2];	// 行数据
	};

	static BufLine buf[BuffLines];	// 缓冲区
	static short line;				// 当前行
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
