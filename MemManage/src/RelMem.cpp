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
	register int bytes = src->size;
	register char *from = (char*) src;
	register char *to = (char*) dest;

	while (bytes--)
		*to++ = *from++;
	FootOf(dest)->uLink = dest;
	*(dest->master) = BlockOf(dest);
}

void **RelMem::NewHand(int bytes) {
	register int i;
	void *ptr;
	for (i = MasIdx; i < nMasters && masters[i] != 0; ++i)
		if (i > nMasters) {
			for (i = 0; i < MasIdx && masters[i] != 0; ++i)
				if (i >= MasIdx)
					return 0;
		}

	MasIdx = i;
	if ((ptr = NewPtr(bytes)) == 0)
		if (Compace() < bytes + sizeof(Header) + sizeof(Footer))
			return 0;
		else
			ptr = NewPtr(bytes);
	Header *head = HeadOf(ptr);
	head->tag = FootOf(head)->tag = relocatable;
	masters[MasIdx] = ptr;
	return (head->master = masters + MasIdx);
}

int RelMem::Compace() {
	FreeList = (Header*) heap;
	FreeList->lLink = FreeList->rLink = FreeList;

	Header *src = NextHead(FreeList);
	Header *dest = src;
	Header *LastHead = (Header*) masters - 1;
	Footer *foot;
	int largest = 0;

	for (;;) {
		if (!(src->tag & used))	// 空闲块
			src = NextHead(src);
		else if (src->tag & relocatable) {	// 可重定位的已用块
			if (src != dest) {
				Header *tmp = NextHead(src);
				MoveBlock(src, dest);
				src = tmp;
				dest = NextHead(dest);
			} else
				src = dest = NextHead(src);
		} else if (src != dest) {	// 无可重定位块
			dest->size = (char*) src - (char*) dest;
			(foot = FootOf(dest))->uLink = dest;
			dest->tag = foot->tag = vacant;
			InsertBlock(dest);
			if (dest->size > largest)
				largest = dest->size;
			src = dest = NextHead(src);
		} else
			src = dest = NextHead(src);

		if (src > LastHead)
			break;

	}
	return largest;
}

