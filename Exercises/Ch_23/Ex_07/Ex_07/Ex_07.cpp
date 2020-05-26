#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int main()
try {
	std::ifstream ifs{ "Ex_07_input.txt" };
	if (!ifs)
		throw std::exception("couldn't open input file");
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	int line_num = 1;
	std::regex pattern{ R"(4[0-9]{12}([0-9]{3})?|)"
							R"((5[1-5][0-9]{2}|222[1-9]|22[3-9][0-9]|2[3-6][0-9]{2}|27[01][0-9]|2720)[0-9]{12}|)"
							R"(3[47][0-9]{13}|)"
							R"(6(011|5[0-9]{2})[0-9]{12})" };
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