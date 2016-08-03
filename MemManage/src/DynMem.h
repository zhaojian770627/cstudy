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

struct Footer {		// �ڴ��β��
	Header *uLink;	// ��ָ��
	Status tag;		// ��״̬
};

const int MaxHeap = 16384;	//16KB
const int MinWordSize = sizeof(int);
const int MinEpsilon = sizeof(Header) + sizeof(Footer) + 4;

class DynMem {
protected:
	char heap[MaxHeap];	// ��
	int WordSize;		// �ֳߴ�
	int epsilon;
	Header *FreeList;
	Header *HeadOf(void *block) {
		return (Header*) block - 1;
	}
	Footer * FootOf(Header *h) {
		return (Footer*) ((char*) h + h->size) - 1;
	}
	void * BlockOf(Header *h) {
		return (void*) (h + 1);
	}

	Header * PrevHead(Header *h) {
		return ((Footer*)h-1)->uLink;
	}

	Header *NextHead(Header* h){
		return (Header*)((char*)h+h->size);
	}
	void InsertBlock(Header *h);
	void RemoveBlock(Header *h);

public:
	DynMem(int eps=MinEpsilon,int wSize=MinWordSize);
	void * NewPtr(int bytes);
	void FreePtr(void *ptr);
	int PtrSize(void *ptr)
	{
		return HeadOf(ptr)->size-sizeof(Header)-sizeof(Footer);
	}
	void *ResizePtr(void *ptr,int NewSize);
	virtual ~DynMem();
};

#endif /* DYNMEM_H_ */
