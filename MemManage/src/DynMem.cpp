/*
 * DynMem.cpp
 *
 *  Created on: 2016年7月28日
 *      Author: Administrator
 */

#include "DynMem.h"
#include <iostream>

/**
 * 将Head插入到FreeList的右边
 */
inline void DynMem::InsertBlock(Header *head) {
	head->tag = FootOf(head)->tag = vacant;
	head->lLink = FreeList;
	head->rLink = FreeList->rLink;
	head->rLink->lLink = head->lLink->rLink = head;

}

inline void DynMem::RemoveBlock(Header *head) {
	FreeList = head->lLink;
	head->rLink->lLink = head->lLink;
	head->lLink->rLink = head->rLink;
}
DynMem::DynMem(int eps, int wSize) {
	if (eps < MinEpsilon)
		eps = MinEpsilon;

	if (wSize < MinWordSize)
		wSize = MinWordSize;

	epsilon = eps;
	WordSize = wSize;

	Header *head1 = (Header*) heap;
	Footer *foot1 = (Footer*) (head1 + 1);
	Header *blkHead = (Header*) (foot1 + 1);
	Footer *blkFoot = (Footer*) (heap + MaxHeap - sizeof(Footer)
			- sizeof(Header));
	Header *headN = (Header*) (blkFoot + 1);

	// 初始化第一个块的头部和尾部
	head1->lLink = head1->rLink = blkHead;
	head1->tag = blkFoot->tag = used;
	head1->size = sizeof(Header) + sizeof(Footer);
	foot1->uLink = head1;

	// 初始化空闲块的头部和尾部
	blkHead->lLink = blkHead->rLink = head1;
	blkHead->tag = blkFoot->tag = vacant;
	blkHead->size = MaxHeap - sizeof(Header) * 2 - sizeof(Footer);
	blkFoot->uLink = blkHead;

	// 初始化末尾块的头部（没有尾部）
	headN->lLink = headN->rLink = 0;
	headN->tag = used;
	headN->size = sizeof(Header);

	// 初始化FreeList为指向第一个空闲块
	FreeList = blkHead;
}

void *DynMem::NewPtr(int bytes) {
	Header *head;	// 所分配块的头部
	Footer *foot;	// 块的尾部
	int diff;
	if (bytes <= 0)
		return 0;
	bytes += sizeof(Header) + sizeof(Footer);
	if (bytes % WordSize != 0)	// 如果不是字长的整数倍
		bytes = (bytes / WordSize + 1) * WordSize;	// ... 则进行对齐操作
	head = FreeList->rLink;
	do {
		if (!(head->tag & used) && head->size >= bytes) {
			if ((diff = head->size - bytes) <= epsilon) {
				RemoveBlock(head);	// 分配整块
				foot = FootOf(head);
			} else {
				head->size = diff;
				(foot = FootOf(head))->uLink = head;
				foot->tag = vacant;
				head = (Header*) (foot + 1);
				head->size = bytes;
				(foot = FootOf(head))->uLink = head;
			}
			head->master = 0;
			head->tag = foot->tag = used;
			return BlockOf(head);
		}
		head = head->rLink;
	} while (head != FreeList->rLink);
	return 0;
}

DynMem::~DynMem() {
	// TODO Auto-generated destructor stub
}

