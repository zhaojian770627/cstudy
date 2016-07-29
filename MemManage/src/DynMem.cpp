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
DynMem::DynMem(int eps,int wSize) {
	std::cout<<eps<<std::endl;
	std::cout<<wSize<<std::endl;
	std::cout<<sizeof(Header)<<std::endl;
}

DynMem::~DynMem() {
	// TODO Auto-generated destructor stub
}

