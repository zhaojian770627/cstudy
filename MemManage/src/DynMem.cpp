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

