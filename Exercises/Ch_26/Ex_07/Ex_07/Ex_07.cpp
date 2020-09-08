#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <string>

using Line = std::vector<char>;

class Text_iterator {
public:
	std::list<Line>::iterator li;
	Line::iterator ci;

	Text_iterator(std::list<Line>::iterator ln_it, Line::iterator ch_it) : li{ ln_it }, ci{ ch_it } {}

	char& operator*() { return *ci; }
	Text_iterator& operator++();
	bool operator==(const Text_iterator& other_ti) const { return li == other_ti.li && ci == other_ti.ci; }
	bool operator!=(const Text_iterator& other_ti) const { return !(*this == other_ti); }
};

Text_iterator& Text_iterator::operator++()
{
	++ci;
	if (ci == li->end()) {
		++li;
		ci = li->begin();
	}
	return *this;
}

class Document {
public:
	std::list<Line> lines;

	Document() { lines.push_back(Line{}); }

	Text_iterator begin() { return Text_iterator{ lines.begin(), lines.begin()->begin() }; }
	Text_iterator end();
};

Text_iterator Document::end()
{
	auto p = lines.end();
	--p;
	return Text_iterator{ p, p->end() };
}

std::istream& operator>>(std::istream& is, Document& doc)
{
	for (char c; is.get(c);) {
		doc.lines.back().push_back(c);
		if (c == '\n')
			doc.lines.push_back(Line{});
	}
	if (doc.lines.back().size())
		doc.lines.push_back(Line{});
	return is;
}

void print(Document& doc)
{
	for (auto p : doc)
		std::cout << p;
}

void erase_line(Document& doc, int ln_num)
{
	if (ln_num < 0 || ln_num >= doc.lines.size() - 1)
		return;
	auto p = doc.lines.begin();
	std::advance(p, ln_num);
	doc.lines.erase(p);
}

bool match(Text_iterator b, Text_iterator e, const std::string& ms)
{
	auto p = ms.begin();
	while (b != e && *p == *b) {
		++p;
		++b;
		if (p == ms.end())
			return true;
	}
	return false;
}

Text_iterator find_txt(Text_iterator b, Text_iterator e, const std::string fs)
{
	if (fs.empty())
		return e;
	char first = fs.front();
	while (true) {
		auto p = std::find(b, e, first);
		if (p == e || match(p, e, fs))
			return p;
		b = ++p;
	}
}

struct Test {
	std::string label;
	std::string fct;
	std::string arg;
	int res;
};

std::istream& operator>>(std::istream& is, Test& t)
{
	const char ob = '{';
	const char cb = '}';

	char c;
	std::string label;
	std::string fct;
	std::string arg;
	int res;

	is >> c;
	if (is.eof())
		return is;
	if (c != ob)
		throw std::exception{ "bad Test format" };
	is >> label >> fct >> c;
	if (c != ob)
		throw std::exception{ "bad Test format" };
	is >> c;
	while (!is.eof() && c != cb) {
		arg.push_back(c);
		is.get(c);
	}
	arg.pop_back();
	is >> res >> c;
	if (c != cb)
		throw std::exception{ "bad Test format" };

	if (!is && !is.eof())
		throw std::exception{ "bad input" };

	t = Test{ label, fct, arg, res };

	return is;
}

bool run_test(const Test& t, Document& doc)
{
	if (t.fct == "find") {
		int match = find_txt(doc.begin(), doc.end(), t.arg) == doc.end() ? 0 : 1;
		if (match != t.res)
			return false;
	}
	else if (t.fct == "erase") {
		erase_line(doc, std::stoi(t.arg));
		if (doc.lines.size() != t.res)
			return false;
	}
	else
		throw std::exception{ "invalid test type" };
}

int main()
try {
	std::ifstream ifs{ "Ex_07_input1.txt" };
	if (!ifs)
		throw std::exception{ "couldn't open input file" };

	Document my_doc;
	ifs >> my_doc;

	ifs.close();
	ifs.open("Ex_07_input2.txt");
	if (!ifs)
		throw std::exception{ "couldn't open input file" };

	int error_count = 0;
	for (Test t; ifs >> t;)
		if (!run_test(t, my_doc)) {
			std::cout << "Failure: test " << t.label << " returned a different result than expected.\n";
			++error_count;
		}
	std::cout << "Total number of errors: " << error_count << ".\n";
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}