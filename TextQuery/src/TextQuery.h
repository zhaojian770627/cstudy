/*
 * TextQuery.h
 *
 *  Created on: 2016-3-6
 *      Author: zhaojian
 */

#ifndef TEXTQUERY_H_
#define TEXTQUERY_H_

#include <string>
#include <vector>
#include <set>
#include <map>

class TextQuery {
public:
	// typedef to make declarations easier
	typedef std::vector<std::string>::size_type line_no;

	void read_file_file(std::ifstream &is) {
		store_file(is);
		build_map();
	}

	std::set<line_no> run_query(const std::string&) const;
	std::string text_line(line_no) const;
private:
	void store_file(std::ifstream&);
	void build_map();
	std::vector<std::string> lines_of_text;
	std::map< std::string,std::set<line_no> > word_map;
};

#endif /* TEXTQUERY_H_ */
