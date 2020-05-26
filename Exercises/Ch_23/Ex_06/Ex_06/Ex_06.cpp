#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int main()
try {
	std::ifstream ifs{ "Ex_06_input.txt" };
	if (!ifs)
		throw std::exception("couldn't open input file");
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	int line_num = 1;
	std::regex pattern{ R"(([1-9]|0[1-9]|1[0-2])(/|-)([1-9]|[12]\d|3[01])(/|-)(\d{2}|[12]\d{3}))" };
	for (std::string s; std::getline(ifs, s); ++line_num) {
		std::smatch matches;
		if (std::regex_match(s, matches, pattern))
			std::cout << "Line " << line_num << ": " << s << '\n';
	}

	if (!ifs && !ifs.eof())
		throw std::exception("bad input");
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}