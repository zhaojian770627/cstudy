/*
 * Handle.cpp
 *
 *  Created on: 2016Äê4ÔÂ9ÈÕ
 *      Author: zhaojian
 */

#include "Handle.h"
#include <stdexcept>

template<class T> Handle<T>::~Handle() {
	rem_ref();
}

template<class T> inline Handle<T>& Handle<T>::operator=(const Handle &rhs) {
	++rhs.use;
	rem_ref();
	ptr = rhs.ptr;
	use = rhs.use;
}

template<class T> inline T& Handle<T>::operator*() {
	if(ptr)
		return *ptr;
	throw std::runtime_error("dereference of unbound Handle");
}

template<class T> inline T* Handle<T>::operator->() {
	if(ptr)
		return ptr;
	throw std::runtime_error("access through unbound Handle");
}

template<class T> inline const T& Handle<T>::operator*() const {
	if(ptr)
		return *ptr;
	throw std::runtime_error("dereference of unbound Handle");
}

template<class T> inline const T* Handle<T>::operator->() const{
	if(ptr)
		return ptr;
	throw std::runtime_error("access through unbound Handle");
}
