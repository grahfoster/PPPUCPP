#include <iostream>
#include <regex>

int main()
try {
	std::string s{ "\n" };
	std::regex pattern{ R"(.)" };
	std::smatch matches;
	if (std::regex_search(s, matches, pattern))
		std::cout << "'.' matches '\\n'.\n";
	else
		std::cout << "'.' doesn't match '\\n'.\n";
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}