/*
 * WindowMgr.h
 *
 *  Created on: 2016��3��13��
 *      Author: zhaojian
 */

#ifndef WINDOWMGR_H_
#define WINDOWMGR_H_

#include <string>
//#include "screen.h"

class Screen;

class WindowMgr {
public:
	WindowMgr();

	WindowMgr& relocate(std::string::size_type, std::string::size_type, Screen&);
};

#endif /* WINDOWMGR_H_ */
