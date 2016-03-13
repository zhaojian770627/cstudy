/*
 * screen.h
 *
 *  Created on: 2016Äê3ÔÂ12ÈÕ
 *      Author: zhaojian
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include <string>
#include "WindowMgr.h"

//class WindowMgr;
//class Screen;
//WindowMgr& WindowMgr::relocate(std::string::size_type, std::string::size_type, Screen&);

/**
 * Screen
 */
class Screen {
public:
	Screen() :cursor(0),height(0),width(0){
	}
	;
	typedef std::string::size_type index;
	char get() const {
		return contents[cursor];
	}

	friend WindowMgr& WindowMgr::relocate(Screen::index, Screen::index, Screen&);

	inline char get(index ht, index wd) const;
	index get_cursor() const;

	Screen& move(index r, index c);
	Screen& set(char);
	//Screen& set(index,index,char);
	const Screen& display(std::ostream &os) const {
		do_display(os);
		return *this;
	}

	Screen& display(std::ostream &os) {
		do_display(os);
		return *this;
	}
private:
	void do_display(std::ostream &os) const {
		os << contents;
	}
	std::string contents;
	index cursor;
	index height, width;
};

#endif /* SCREEN_H_ */
