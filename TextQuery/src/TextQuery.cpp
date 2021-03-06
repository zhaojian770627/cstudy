/*
 * TextQuery.cpp
 *
 *  Created on: 2016-3-6
 *      Author: zhaojian
 */

#include "TextQuery.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using std::istringstream;
using std::ifstream;
using std::string;
using std::set;
using std::map;

void TextQuery::store_file(ifstream &is) {
	string textline;
	while (getline(is, textline))
		lines_of_text.push_back(textline);
}

void TextQuery::build_map() {
	for (line_no line_num = 0; line_num != lines_of_text.size(); ++line_num) {
		istringstream line(lines_of_text[line_num]);
		string word;
		while (line >> word)
			word_map[word].insert(line_num);
	}
}

set<TextQuery::line_no> TextQuery::run_query(const string &query_word) const {
	map<string, set<line_no> >::const_iterator loc = word_map.find(query_word);
	if (loc == word_map.end())
		return set<line_no> ();
	else
		return loc->second;
}

string TextQuery::text_line(line_no line) const {
	if (line < lines_of_text.size())
		return lines_of_text[line];
	throw std::out_of_range("line number out of range");
}

