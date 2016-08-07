/*
 * RelMem.h
 *
 *  Created on: 2016年8月7日
 *      Author: Administrator
 */

#ifndef RELMEM_H_
#define RELMEM_H_

#include <iostream>
#include "DynMem.h"

const int MinMasters = 16;	// 控制指针的最小数目

class RelMem: public DynMem {

	void **masters;	// 控制(master)指针
	int nMasters;	// 控制指针的数目
	int MasIdx;		// 当前控制指针的索引号
	void MoveBlock(Header *src, Header *desc);
public:
	RelMem(int = MinMasters, int = MinEpsilon, int = MinWordSize);
	void **NewHand(int bytes);
	void FreeHand(void **hand){
FreePtr(*hand);
*hand=0;
	}

	int HandSize(void **hand){
		return PtrSize(*hand);
	}

	void ResizeHand(void **hand,int NewSize);
	void LockHand(void **hand);
	void UnlockHand(void **hand);
	int Compace();
};

#endif /* RELMEM_H_ */
