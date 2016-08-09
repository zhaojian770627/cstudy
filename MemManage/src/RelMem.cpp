/*
 * RelMem.cpp
 *
 *  Created on: 2016��8��7��
 *      Author: Administrator
 */

#include "RelMem.h"

RelMem::RelMem(int nMax, int eps, int wSize) :
		DynMem(eps, wSize) {
	Header *head = FreeList;
	Footer *foot = FootOf(head);
	// nMax ̫���̫Сʱ�����е���
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
	// ��ʼʱ�����п���ָ�붼Ϊ����
	for (register int i = 0; i < nMasters; ++i)
		masters[i] = 0;
	MasIdx = 0;		// ��һ�����ɵ�masterָ��
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
	head->tag = FootOf(head)->tag |= relocatable;
	masters[MasIdx] = ptr;
	return (head->master = masters + MasIdx);
}
