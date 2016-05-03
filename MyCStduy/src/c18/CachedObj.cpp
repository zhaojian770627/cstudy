/*
 * CachedObj.cpp
 *
 *  Created on: 2016Äê4ÔÂ30ÈÕ
 *      Author: zhaojian
 */

#include "CachedObj.h"

template<class T> void* CachedObj<T>::operator new(size_t sz) {
	if (sz != sizeof(T))
		throw std::runtime_error("CachedObj:wrong size object in oerator new");

	if (!freeStore) {
		T* array = alloc_mem.allocate(chunk);
		for (size_t i = 0; i != chunk; ++i)
			add_to_freelist(&array[i]);
	}

	T *p = freeStore;
	freeStore = freeStore->CachedObj < T > ::next;
	return p;
}

template<class T> void CachedObj<T>::operator delete(void *p, size_t) {
	if (p != 0)
		add_to_freelist(static_cast<T*>(p));
}

template<class T> void CachedObj<T>::add_to_freelist(T *p) {
	p->CachedObj < T > ::next = freeStore;
	freeStore = p;
}

template<class T> allocator<T> CachedObj<T>::alloc_mem;
template<class T> T *CachedObj<T>::freeStore = 0;
template<class T> const size_t CachedObj<T>::chunk = 24;
