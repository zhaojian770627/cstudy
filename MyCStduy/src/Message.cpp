/*
 * Message.cpp
 *
 *  Created on: 2016Äê3ÔÂ15ÈÕ
 *      Author: zhaojian
 */

#include "Message.h"
#include "Folder.h"

Message::Message(const Message &m) :
		contents(m.contents), folders(m.folders) {
	//put_Msg_in_Folders(folders);
}
Message::~Message() {
	// TODO Auto-generated destructor stub
}

// add this Message to Folders that point to rhs
//void Message::put_Msg_in_Folders(const set<Folder*> &rhs)
//{
//    for(std::set<Folder*>::const_iterator beg = rhs.begin();
//                                     beg != rhs.end(); ++beg)
//        (*beg)->addMsg(this);  // *beg points to a Folder
//}

void Message::put_Msg_in_Folders(const std::set<Folder*> &rhs) {
	for (std::set<Folder*>::const_iterator beg = rhs.begin(); beg != rhs.end();
			++beg)
		(*beg)->addMsg(this);  // *beg points to a Folder
}

