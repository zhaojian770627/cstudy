/*
 * SmallInt.h
 *
 *  Created on: 2016Äê3ÔÂ20ÈÕ
 *      Author: zhaojian
 */

#ifndef SMALLINT_H_
#define SMALLINT_H_

#include <cstddef>
#include <stdexcept>

class SmallInt {
public:
	SmallInt(int i = 0) :
			val(i) {
		if (i < 0 || i > 255)
			throw std::out_of_range("Bad SmallInt initializer");
	}
	operator int() const {
		return val;
	}
private:
	std::size_t val;
};

#endif /* SMALLINT_H_ */
