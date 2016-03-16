/*
 * Message.h
 *
 *  Created on: 2016Äê3ÔÂ15ÈÕ
 *      Author: zhaojian
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string>
#include <set>
#include <vector>

using std::vector;

class Folder;

class Message {
	friend class Folder;
public:
	Message(const std::string &str=""):contents(str){};
	Message(const Message&);
	Message& operator=(const Message&);
	virtual ~Message();

	void save(Folder&);
	void remove(Folder&);

    vector<Folder*> get_folders();
    std::string print_message() { return contents; }
    void debug_print(); // print contents and it's list of Folders,
private:
	std::string contents;
	std::set<Folder*> folders;
	void put_Msg_in_Folders(const std::set<Folder*> &);
	void remove_Msg_from_Folders();

    // used by Folder class to add self to this Message's set of Folder's
    void addFldr(Folder *f) { folders.insert(f); }
    void remFldr(Folder *f) { folders.erase(f); }
};

#endif /* MESSAGE_H_ */
