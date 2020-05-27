#include <iostream>
#include <fstream>
#include <regex>

int main()
try {
	std::string pat;
	std::cout << "Please enter a pattern:\n";
	std::getline(std::cin, pat);
	std::regex pattern{ pat };

	std::string file_name;
	std::cout << "Please enter the name of a file to match from:\n";
	std::cin >> file_name;

	std::ifstream ifs{ file_name };
	if (!ifs)
		throw std::exception("couldn't open input file");
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	int line_num = 1;
	for (std::string line; std::getline(ifs, line); ++line_num) {
		std::smatch matches;
		if (std::regex_search(line, matches, pattern))
			std::cout << "Line " << line_num << ": " << line << '\n';
	}
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}