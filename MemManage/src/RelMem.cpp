/*
 * RelMem.cpp
 *
 *  Created on: 2016年8月7日
 *      Author: Administrator
 */

#include "RelMem.h"

RelMem::RelMem(int nMax, int eps, int wSize) :
		DynMem(eps, wSize) {
	Header *head = FreeList;
	Footer *foot = FootOf(head);
	// nMax 太大或太小时，进行调整
	if (nMax < MinMasters || nMax > (head->size - MinEpsilon) / 4)
		nMax = MinMasters;
	nMasters = nMax;
	head->size -= nMasters * sizeof(void*);
	Footer *NewFoot = FootOf(head);
	Header *NewHead = (Header*) (NewFoot + 1);
	head = (Header*) (foot + 1);
	*NewFoot = *foot;
	*NewHead = *head;
	masters = (void**) (NewHead + 1);
	// 初始时，所有控制指针都为空闲
	for (register int i = 0; i < nMasters; ++i)
		masters[i] = 0;
	MasIdx = 0;		// 第一个自由的master指针
}

void RelMem::MoveBlock(Header* src, Header *dest) {
	register int bytes=src->size;
	register char *from=(char*)src;
	register char *to=(char*)dest;

	while(bytes--)
		*to++=*from++;
	FootOf(dest)->uLink=dest;
	*(dest->master)=BlockOf(dest);
}
