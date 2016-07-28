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
const int MinEpsilon=sizeof(Header)+sizeof(Footer)+4;

class DynMem {
protected:
	enum Status {		// ��״̬
		vacant,used
	};
	char heap[MaxHeap];	// ��
	int WordSize;		// �ֳߴ�
	int epsilon;
	Header *FreeList;
	Header *HeadOf(void *block){
		return (Header*)block-1;
	}
public:
	DynMem();
	virtual ~DynMem();
};

#endif /* DYNMEM_H_ */
