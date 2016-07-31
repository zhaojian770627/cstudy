/*
 * DynMem.cpp
 *
 *  Created on: 2016��7��28��
 *      Author: Administrator
 */

#include "DynMem.h"
#include <iostream>

/**
 * ��Head���뵽FreeList���ұ�
 */
inline void DynMem::InsertBlock(Header *head){
	head->tag=FootOf(head)->tag=vacant;
	head->lLink=FreeList;
	head->rLink=FreeList->rLink;
	head->rLink->lLink=head->lLink->rLink=head;

}

inline void DynMem::RemoveBlock(Header *head){
	FreeList=head->lLink;
	head->rLink->lLink=head->lLink;
	head->lLink->rLink=head->rLink;
}
DynMem::DynMem(int eps,int wSize) {
	if(eps<MinEpsilon)
		eps=MinEpsilon;

	if(wSize<MinWordSize)
		wSize=MinWordSize;

	epsilon=eps;
	WordSize=wSize;

	Header *head1=(Header*)heap;
	Footer *foot1=(Footer*)(head1+1);
	Header *blkHead=(Header*)(foot1+1);
	Footer *blkFoot=(Footer*)(heap+MaxHeap-sizeof(Footer)-sizeof(Header));
	Header *headN=(Header*)(blkFoot+1);

	// ��ʼ����һ�����ͷ����β��
	head1->lLink=head1->rLink=blkHead;
	head1->tag=blkFoot->tag=used;
	head1->size=sizeof(Header)+sizeof(Footer);
	foot1->uLink=head1;

	// ��ʼ�����п��ͷ����β��
	blkHead->lLink=blkHead->rLink=head1;
	blkHead->tag=blkFoot->tag=vacant;
	blkHead->size=MaxHeap-sizeof(Header)*2-sizeof(Footer);
	blkFoot->uLink=blkHead;

	// ��ʼ��ĩβ���ͷ����û��β����
	headN->lLink=headN->rLink=0;
	headN->tag=used;
	headN->size=sizeof(Header);

	// ��ʼ��FreeListΪָ���һ�����п�
	FreeList=blkHead;
}

DynMem::~DynMem() {
	// TODO Auto-generated destructor stub
}

