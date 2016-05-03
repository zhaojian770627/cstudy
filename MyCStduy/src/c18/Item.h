/*
 * Item.h
 *
 *  Created on: 2016Äê5ÔÂ2ÈÕ
 *      Author: zhaojian
 */

#ifndef C18_ITEM_H_
#define C18_ITEM_H_
#include "CachedObj.h"

class Item: public CachedObj<Item> {
public:
	Item(){};
	virtual ~Item(){};
};

#include "CachedObj.cpp"

#endif /* C18_ITEM_H_ */
