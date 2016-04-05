/*
 * compare.cpp
 *
 *  Created on: 2016Äê4ÔÂ5ÈÕ
 *      Author: zhaojian
 */

#include "compare.h"

template<typename T> int compare(const T &v1, const T &v2) {
	if (v1 < v2)
		return -1;
	if (v2 < v1)
		return 1;
	return 0;
}
