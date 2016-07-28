/*
 * DynMem.h
 *
 *  Created on: 2016年7月28日
 *      Author: Administrator
 */

#ifndef DYNMEM_H_
#define DYNMEM_H_

enum Status {
	vacant, used
};

struct Header {		// 内存块头部
	Header * lLink;	// 左指针
	Header * rLink;	// 右指针
	void ** master;	// 本块的控制指针
	int size;		// 以字节记得块大小
	Status tag;		// 块状态
};

struct Footer{		// 内存块尾部
	Header *uLink;	// 上指针
	Status tag;		// 块状态
};

const int MaxHeap=16384;	//16KB
const int MinWordSize=sizeof(int);
const int MinEpsilon=sizeof(Header)+sizeof(Footer)+4;

class DynMem {
protected:
	enum Status {		// 块状态
		vacant,used
	};
	char heap[MaxHeap];	// 堆
	int WordSize;		// 字尺寸
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
