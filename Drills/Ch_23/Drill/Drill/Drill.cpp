#include <iostream>
#include <fstream>
#include <regex>

int main()
try {
	std::ifstream ifs{ "Drill_input.txt" };
	if (!ifs)
		throw std::exception("couldn't open input file");
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	std::regex pattern{ R"(\w{2}\s*\d{5}(-\d{4})?)" };

	int line_num = 1;
	for (std::string line; std::getline(ifs, line); ++line_num) {
		std::smatch matches;
		if (std::regex_search(line, matches, pattern)) {
			std::cout << line_num << ": " << matches[0] << '\n';
			if (matches.size() > 1 && matches[1].matched)
				std::cout << "\t: " << matches[1] << '\n';
		}
	}
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}