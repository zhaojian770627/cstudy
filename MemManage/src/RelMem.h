/*
 * RelMem.h
 *
 *  Created on: 2016��8��7��
 *      Author: Administrator
 */

#ifndef RELMEM_H_
#define RELMEM_H_

#include <iostream>
#include "DynMem.h"

const int MinMasters = 16;	// ����ָ�����С��Ŀ

class RelMem: public DynMem {

	void **masters;	// ����(master)ָ��
	int nMasters;	// ����ָ�����Ŀ
	int MasIdx;		// ��ǰ����ָ���������
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
