/*
 * CachedObj.h
 *
 *  Created on: 2016Äê4ÔÂ30ÈÕ
 *      Author: zhaojian
 */

#ifndef C18_CACHEDOBJ_H_
#define C18_CACHEDOBJ_H_
#include <cstddef>
#include <iostream>
#include <stdexcept>

using namespace std;

template<class T> class CachedObj {
public:
	void *operator new(std::size_t);
	void operator delete(void *, std::size_t);
	virtual ~CachedObj(){};

	void operator delete[](void *, std::size_t);
	void *operator new[](std::size_t);
protected:
	T *next;
private:
	static void add_to_freelist(T*);
	static std::allocator<T> alloc_mem;
	static T *freeStore;
	static const std::size_t chunk;

};

#endif /* C18_CACHEDOBJ_H_ */
