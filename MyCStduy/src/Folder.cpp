/*
 * Folder.cpp
 *
 *  Created on: 2016Äê3ÔÂ15ÈÕ
 *      Author: zhaojian
 */

#include <iostream>
#include "Message.h"
#include "Folder.h"

using std::cerr;
using std::endl;

Folder::Folder(const Folder &f)
{
    copy_msgs(f.msgs);  // add this Folder to each Message in f.msgs
}

void Folder::copy_msgs(const std::set<Message*>&m) {
	for (Msg_iter beg = m.begin(); beg != m.end(); ++beg)
		(*beg)->save(*this);   // add this Folder to each Message
}

Folder& Folder::operator=(const Folder &f)
{
    if (&f != this) {
        empty_msgs();  // remove this folder from each Message in msgs
        copy_msgs(f.msgs); // add this folder to each Message in msgs
    }
    return *this;
}

void Folder::empty_msgs()
{
    Msg_iter it = msgs.begin();
    while (it != msgs.end()) {
        Msg_iter next = it;
        ++next;                // remember next element in msgs
        (*it)->remove(*this);
        it = next;
    }
}

void Folder::save(Message &m)
{
    // add m and add this folder to m's set of Folders
    msgs.insert(&m);
    m.addFldr(this);
}

void Folder::remove(Message &m)
{
    // erase m from msgs and remove this folder from m
    msgs.erase(&m);
    m.remFldr(this);
}

void Folder::debug_print()
{
    cerr << "Folder contains " << msgs.size() << " messages" << endl;
    int ctr = 1;
    for (Msg_iter beg = msgs.begin(); beg != msgs.end(); ++beg)
        cerr << "Message " << ctr++ << ":\n\t"
             << (*beg)->print_message() << endl;
}

Folder::~Folder() {
	cerr << "~Folder:" << endl;
	empty_msgs();
}

