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

int count_wss_words(Document& doc)
{
	int count = 0;
	bool first = false;
	auto p = doc.begin();
	while (p != doc.end()) {
		if (iswspace(*p)) {
			if (first)
				++count;
			while (p != doc.end()) {
				if (!iswspace(*p))
					break;
				++p;
			}
		}
		else
			++p;
		first = true;
	}
	return count;
}

int count_alpha_words(Document& doc)
{
	int count = 0;
	bool first = false;
	auto p = doc.begin();
	while (p != doc.end()) {
		if (!isalpha(*p)) {
			if (first)
				++count;
			while (p != doc.end()) {
				if (isalpha(*p))
					break;
				++p;
			}
		}
		else
			++p;
		first = true;
	}
	return count;
}

int main()
try {
	std::istringstream iss{ "This is a document.\nThis is the th1rd line...\nand this is not the th1rd.\n" };
	Document my_doc;
	iss >> my_doc;
	print(my_doc);
	std::cout << "Number of whitespace-separated words: " << count_wss_words(my_doc) << '\n';
	std::cout << "Number of alphabetic words: " << count_alpha_words(my_doc) << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}