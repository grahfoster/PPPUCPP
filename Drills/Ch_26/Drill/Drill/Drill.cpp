#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>
#include <string>
#include <algorithm>

struct Test {
	std::string label;
	//int val;
	std::string val;
	//std::vector<int> seq;
	std::vector<std::string> seq;
	bool res;
};

std::istream& operator>>(std::istream& is, Test& t)
{
	const char ob = '{';
	const char cb = '}';

	char c;
	std::string label;
	//int val;
	std::string val;
	//std::vector<int> seq;
	std::vector<std::string> seq;
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
	/*for (int i = 0; isdigit(c) || isspace(c); is >> c) {
		is.unget();
		is >> i;
		seq.push_back(i);
	}*/
	for (std::string s; isalnum(c); is >> c) {
		is.unget();
		is >> s;
		seq.push_back(s);
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

std::ostream& operator<<(std::ostream& os, const Test& t)
{
	const char ob = '{';
	const char cb = '}';

	os << ob << ' ' << t.label << ' ' << t.val << ' ' << ob << ' ';
	/*for (int i : t.seq)
		os << i << ' ';*/
	for (std::string s : t.seq)
		os << s << ' ';
	os << cb << ' ' << t.res << ' ' << cb << '\n';

	return os;
}

void generate_tests(std::ofstream& ofs)
{
	/*std::vector<int> vi(1000);
	std::iota(vi.begin(), vi.end(), 0);
	ofs << Test{ "1", 500, vi, true };*/
	std::vector<std::string> vs(1000);
	for (int i = 0; i < 1000; ++i)
		vs[i] = std::to_string(i);
	ofs << Test{ "1", "500", vs, true };

	/*for (int i = 0; i < 10; ++i) {
		std::vector<int> rvi(rand() % 100);
		std::iota(rvi.begin(), rvi.end(), 0);
		ofs << Test{ std::to_string(2 + i), 1, rvi, true };
	}*/
	for (int i = 0; i < 10; ++i) {
		std::vector<std::string> rvs(rand() % 100);
		for (int i = 0; i < rvs.size(); ++i)
			rvs[i] = std::to_string(i);
		ofs << Test{ std::to_string(2 + i), "1", rvs, true };
	}

	/*for (int i = 0; i < 10; ++i) {
		std::vector<int> vri(i);
		for (int& i : vri)
			i = rand() % 10;
		std::sort(vri.begin(), vri.end());
		ofs << Test{ std::to_string(12 + i), 1, vri, true };
	}*/
	for (int i = 0; i < 10; ++i) {
		std::vector<std::string> vrs(i);
		for (std::string& s : vrs)
			s = std::to_string(rand() % 10);
		std::sort(vrs.begin(), vrs.end());
		ofs << Test{ std::to_string(12 + i), "1", vrs, true };
	}
}

int test_all(std::istream& is)
{
	int error_count = 0;
	for (Test t; is >> t;) {
		bool r = std::binary_search(t.seq.begin(), t.seq.end(), t.val);
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
	//std::ifstream ifs{ "Drill_input1.txt" };
	std::ifstream ifs{ "Drill_input2.txt" };
	if (!ifs)
		throw std::exception{ "input file not found" };
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	int errors = test_all(ifs);
	std::cout << "Total number of errors: " << errors << ".\n\n";
	ifs.close();

	//std::ofstream ofs{ "Drill_output1.txt" };
	std::ofstream ofs{ "Drill_output2.txt" };
	if (!ofs)
		throw std::exception{ "output file not found" };
	generate_tests(ofs);
	ofs.close();
	
	//ifs.open("Drill_output1.txt");
	ifs.open("Drill_output2.txt");
	if (!ifs)
		throw std::exception{ "input file not found" };

	errors = test_all(ifs);
	std::cout << "Total number of errors: " << errors << ".\n";
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}