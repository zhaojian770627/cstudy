/*
 * Folder.h
 *
 *  Created on: 2016Äê3ÔÂ15ÈÕ
 *      Author: zhaojian
 */

#ifndef FOLDER_H_
#define FOLDER_H_
#include <iostream>
#include <vector>
#include <set>
#include "Message.h"

class Folder {
	friend class Message;
public:
	Folder() { std::cerr<<"Folder()"<<std::endl; } // defaults ok
    Folder(const Folder&); // add new folder to each Message| in msgs
    Folder& operator=(const Folder&); // delete Folder from lhs messages

    void save(Message&); // add this message to folder
    void remove(Message&); // remove this message from this folder

    std::vector<Message*> messages(); // return list of messages in this folder
    void debug_print(); // print contents and it's list of Folders,

	virtual ~Folder();
private:
    typedef std::set<Message*>::const_iterator Msg_iter;
    std::set<Message*> msgs;  // messages in this folder

    void copy_msgs(const std::set<Message*>&); // add this Folder to each Message
    void empty_msgs();           // remove this Folder from each Message
    void addMsg(Message *m) { msgs.insert(m); }
    void remMsg(Message *m) { msgs.erase(m); }
};

#endif /* FOLDER_H_ */
