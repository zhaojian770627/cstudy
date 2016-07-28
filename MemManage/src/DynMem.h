/*
 * DynMem.h
 *
 *  Created on: 2016��7��28��
 *      Author: Administrator
 */

#ifndef DYNMEM_H_
#define DYNMEM_H_

enum Status {
	vacant, used
};

struct Header {		// �ڴ��ͷ��
	Header * lLink;	// ��ָ��
	Header * rLink;	// ��ָ��
	void ** master;	// ����Ŀ���ָ��
	int size;		// ���ֽڼǵÿ��С
	Status tag;		// ��״̬
};

struct Footer{		// �ڴ��β��
	Header *uLink;	// ��ָ��
	Status tag;		// ��״̬
};

const int MaxHeap=16384;	//16KB
const int MinWordSize=sizeof(int);
class DynMem {
public:
	DynMem();
	virtual ~DynMem();
};

#endif /* DYNMEM_H_ */
