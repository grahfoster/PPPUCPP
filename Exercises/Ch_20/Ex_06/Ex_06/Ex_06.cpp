#include <iostream>
#include <vector>
#include <list>
#include <sstream>

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

bool find_replace(Document& doc, const std::string fs, const std::string rs)
{
	if (fs.empty())
		return false;
	auto p = find_txt(doc.begin(), doc.end(), fs);
	if (p == doc.end())
		return false;
	while (p != doc.end()) {
		for (char c : fs)
			p.ci = p.li->erase(p.ci);
		p.ci = p.li->insert(p.ci, rs.begin(), rs.end());
		p = find_txt(p, doc.end(), fs);
	}
	return true;

}

int main()
try {
	std::istringstream iss{ "This is a document.\nThis is the third line...\nand this is not the third.\n" };
	Document my_doc;
	iss >> my_doc;
	if (!find_replace(my_doc, "third", "second"))
		std::cout << "Find and replace failed.\n";
	else
		print(my_doc);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}