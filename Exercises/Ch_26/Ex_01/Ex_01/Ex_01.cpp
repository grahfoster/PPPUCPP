#include <iostream>
#include <vector>
#include <fstream>

struct Test {
	std::string label;
	int val;
	std::vector<int> seq;
	bool res;
};

std::istream& operator>>(std::istream& is, Test& t)
{
	const char ob = '{';
	const char cb = '}';

	char c;
	std::string label;
	int val;
	std::vector<int> seq;
	bool res;

	is >> c;
	if (is.eof())
		return is;
	if (c != ob)
		throw std::exception{ "bad Test format" };
	is >> label >> val >> c;
	if (c != ob)
		throw std::exception{ "bad Test format" };
	is >> c;
	for (int i = 0; isdigit(c) || isspace(c); is >> c) {
		is.unget();
		is >> i;
		seq.push_back(i);
	}
	if (c != cb)
		throw std::exception{ "bad Test format" };
	is >> res >> c;
	if (c != cb)
		throw std::exception{ "bad Test format" };

	if (!is && !is.eof())
		throw std::exception{ "bad input" };

	t = Test{ label, val, seq, res };

	return is;
}

template<class ForwardIterator, class T>
bool binary_search(ForwardIterator first, ForwardIterator last, const T& value)
{
	while (first != last) {
		ForwardIterator middle = first;
		std::advance(middle, std::distance(first, last) / 2);
		if (*middle == value)
			return true;
		else if (*middle > value)
			last = middle;
		else
			first = ++middle;
	}
	return false;
}

int test_all(std::istream& is)
{
	int error_count = 0;
	for (Test t; is >> t;) {
		bool r = binary_search(t.seq.begin(), t.seq.end(), t.val);
		if (r != t.res) {
			std::cout << "Failure: test " << t.label <<
				" of binary_search with " << t.seq.size() <<
				" elements searching for value " << t.val <<
				" returned result different from " << t.res << ".\n";
			++error_count;
		}
	}
	return error_count;
}

int main()
try {
	std::ifstream ifs{ "Ex_01_input.txt" };
	if (!ifs)
		throw std::exception{ "input file not found" };
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	int errors = test_all(ifs);
	std::cout << "Total number of errors: " << errors << ".\n";
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}