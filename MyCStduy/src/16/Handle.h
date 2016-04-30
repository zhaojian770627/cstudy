/*
 * Handle.h
 *
 *  Created on: 2016Äê4ÔÂ9ÈÕ
 *      Author: zhaojian
 */

#ifndef HANDLE_H_
#define HANDLE_H_

#include <cstddef>

template<class T> class Handle {
public:
	// unboud handle
	Handle(T *p=0):ptr(p),use(new size_t(1)){}
	// overloaded operators to support pointer behavior
	T& operator*();
	T* operator->();
	const T& operator*() const;
	const T* operator->() const;
	// copy control:normal pointer behavior,but last Handle deletes the object
	Handle(const Handle& h):ptr(h.ptr),use(h.use){
		++*use;
	}
	Handle& operator=(const Handle&);
	~Handle();
private:
	T* ptr;	// shared object
	size_t *use;	// count of how many handles spoint to *ptr
	void rem_ref()
	{
		if(--*use==0){
			delete ptr;
			delete use;
		}
	}
};

#endif /* 16_HANDLE_H_ */
