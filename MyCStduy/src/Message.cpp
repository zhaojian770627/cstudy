/*
 * Message.cpp
 *
 *  Created on: 2016Äê3ÔÂ15ÈÕ
 *      Author: zhaojian
 */

#include <iostream>
#include "Message.h"
#include "Folder.h"

using std::cerr;
using std::endl;

Message::Message(const Message &m) :
		contents(m.contents), folders(m.folders) {
	put_Msg_in_Folders(folders);
}

Message& Message::operator=(const Message &rhs) {
	if (&rhs != this) {
		remove_Msg_from_Folders(); // update existing Folders
		contents = rhs.contents;   // copy contents from rhs
		folders = rhs.folders;     // copy Folder pointers from rhs
		// add this Message to each Folder in rhs
		put_Msg_in_Folders(rhs.folders);
	}
	return *this;
}

Message::~Message() {
	cerr << "~Message:" <<contents<< endl;
	remove_Msg_from_Folders();
}

// add this Message to Folders that point to rhs
void Message::put_Msg_in_Folders(const std::set<Folder*> &rhs) {
	for (std::set<Folder*>::const_iterator beg = rhs.begin(); beg != rhs.end();
			++beg)
		(*beg)->addMsg(this);  // *beg points to a Folder
}

void Message::remove_Msg_from_Folders() {
	// remove this message from corresponding folders
	for (std::set<Folder*>::const_iterator beg = folders.begin();
			beg != folders.end(); ++beg)
		(*beg)->remMsg(this);  // *beg points to a Folder
}

void Message::save(Folder &f) {
	// add f to Folders and this Message to f's list of Messages
	folders.insert(&f);
	f.addMsg(this);
}

void Message::remove(Folder &f) {
	// remove f from Folders and this Message from f's list of Messages
	folders.erase(&f);
	f.remMsg(this);
}

vector<Folder*> Message::get_folders() {
	return vector<Folder*>(folders.begin(), folders.end());
}

void Message::debug_print() {
	cerr << "Message:\n\t" << contents << endl;
	cerr << "Appears in " << folders.size() << " Folders" << endl;
}
