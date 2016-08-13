/*
 * Text.cpp
 *
 *  Created on: 2016Äê8ÔÂ13ÈÕ
 *      Author: Administrator
 */

#include "Text.h"

Text::Text() {
	MinSize = 4;

	LinesPtr = new LinPtr[size = MinSize];
	for (int i = 0; i < size; ++i)
		LinesPtr[i] = 0;
	used = WordLine = 0;
}

Text::~Text() {
	for (int i = 0; i < used; ++i)
		delete LinesPtr[i];
	delete LinesPtr;
}

void Text::NewLine(short pos, Line *line) {
	pos = pos < 0 ? 0 : (pos > used ? used : pos);
	Line **old = 0;
	if (used == size) {
		old = LinesPtr;
		LinesPtr = new LinPtr[size += MinSize];
		int i;
		for (i = 0; i < pos; ++i)
			LinesPtr[i] = old[i];
		for (i = pos + 1; i <= used; ++i)
			LinesPtr[i] = old[i - 1];
		for (i = used + 1; i < size; ++i)
			LinesPtr[i] = 0;
		delete old;
	} else
		for (int i = used; i > pos; --i)
			LinesPtr[i] = LinesPtr[i - 1];
	LinesPtr[pos] = line;
	++used;
}

void Text::RmvLine(short pos) {
	if (used == 0)
		return;
	pos = pos < 0 ? 0 : (pos >= used ? used - 1 : pos);
	Line **old = 0;
	delete LinesPtr[pos];
	--used;
	if (size - used > MinSize) {
		old = LinesPtr;
		LinesPtr = new LinPtr[size -= MinSize];
		int i;
		for (i = 0; i < pos; ++i)
			LinesPtr[i] = old[i];
		for (i = pos; i <= used; ++i)
			LinesPtr[i] = old[i + 1];
		for (i = used + 1; i < size; ++i)
			LinesPtr[i] = 0;
		delete old;
	} else {
		for (int i = pos; i < used; ++i)
			LinesPtr[i] = LinesPtr[i + 1];
		LinesPtr[used] = 0;
	}
}

void Text::Insert(short pos, short from, short to, const char *str) {
	if (pos >= 0 && pos < used)
		LinesPtr[pos]->Insert(from, to, str);
}

bool Text::GetWord(char *word) {
	if (WordLine < size) {
		if (LinesPtr[WordLine]->GetWord(word))
			return true;
		++WordLine;
		return GetWord(word);
	}
	WordLine = 0;
	return false;
}

istream& operator>>(istream& in, Text& text) {
	Line *line;
	for (;;) {
		line = new Line;
		in >> *line;
		if (line->Empty()) {
			delete line;
			return in;
		}
		text.NewLine(text.used, line);
	}
	return in;
}

ostream& operator<<(ostream& out, Text& text) {
	for (int i = 0; i < text.used; ++i)
		out << *(text.LinesPtr[i]) << "\n";
	return out;
}
