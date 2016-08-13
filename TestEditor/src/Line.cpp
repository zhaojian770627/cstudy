/*
 * Line.cpp
 *
 *  Created on: 2016年8月13日
 *      Author: Administrator
 */

#include "Line.h"

Line::Line(const char *str) {
	MinSize = 20;
	WordPos=0;
	used = strlen(str);
	size = used + 1 > MinSize ? used + MinSize : MinSize;
	data = new char[size];
	strcpy(data, str);
}

// 用str替换行中from到to(不包括to)的字符串
void Line::Insert(short from, short to, const char *str) {
	from = from < 0 ? 0 : from;
	to = to > used ? used : to;
	if (from > to)
		return;

	int lost = to - from;		// 被替换的长度
	int len = strlen(str);		// 要替换的长度
	char* old = 0;

	if (len + used - lost >= size - 1) {	// 扩大
		old = data;
		data = new char[size += MinSize];
	} else if (size - len - used + lost >= MinSize) {	// 缩小
		old = data;
		data = new char[size -= MinSize];
	}

	if (old != 0) {		// 重构行
		if (from > 0)		// 左部
			strncpy(data, old, from);
		if (len > 0)	// 中部
			strncpy(data + from, str, len);
		if (to < used)	// 右部
			strncpy(data + from + len, old + to, used - to);
		delete old;
	} else {
		int i;
		if (lost < len)
			for (i = used; i >= to; --i)
				data[i + len - lost] = data[i];
		else
			for (i = to; i < used; ++i)
				data[i + len - lost] = data[i];

		strncpy(data + from, str, len);
	}
	used += len - lost;
	data[used] = '\0';
} /* Insert */

bool Line::Empty() {
	for (char *str = data; *str != '\0'; ++str)
		if (!isspace(*str))
			return false;
	return true;
}

istream& operator>>(istream& in,Line& line){
	char buf[256];

	in>>buf;
	line.used=strlen(buf);
	line.WordPos=0;
	if(line.used==line.size){
		delete line.data;
		line.data=new char[line.size=line.used+line.MinSize];
	}

	strcpy(line.data,buf);
	return in;
}

ostream& operator<<(ostream& out,Line& line){
	out<<line.data;
	return out;
}	/* operator<< */

bool Line::GetWord(char *word)
{
	while(WordPos<used && isspace(data[WordPos]))
		++WordPos;

	int i;
	for(i=0;i<MaxWordSize && WordPos<used && !isspace(data[WordPos]);++i)
		word[i]=data[WordPos++];
	word[i]='\0';
	if(i==0)
		WordPos=0;
	return (i>0);
}	/* GetWord */


