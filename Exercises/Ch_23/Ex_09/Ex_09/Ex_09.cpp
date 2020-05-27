#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>

struct Bad_from_string : std::bad_cast {
	const char* what() const override { return "bad cast from string"; }
};

template<class T>
T from_string(const std::string& s)
{
	std::istringstream iss{ s };
	T t;
	if (!(iss >> t))
		throw Bad_from_string{};
	return t;
}

int main()
try {
	std::ifstream ifs{ "Ex_09_input.txt" };
	if (!ifs)
		throw std::exception{ "couldn't open input file" };

	std::string line;

	std::regex header{ R"(^[\w ]+(	[\w ]+)*$)" };
	std::regex row{ R"(^([\w ]+)(	\d+)(	\d+)(	\d+)$)" };

	if (std::getline(ifs, line)) {
		std::smatch matches;
		if (!std::regex_match(line, matches, header))
			throw std::exception{ "no header found" };
	}

	int boys = 0, girls = 0;
	for (int line_num = 1; std::getline(ifs, line); ++line_num) {
		std::smatch matches;
		if (!std::regex_match(line, matches, row))
			throw std::exception{ "bad row format" };

		int curr_boy = from_string<int>(matches[2]);
		int curr_girl = from_string<int>(matches[3]);
		int curr_total = from_string<int>(matches[4]);
		if (curr_boy + curr_girl != curr_total)
			throw std::exception{ "bad row sum" };

		if ((ifs >> std::ws).eof()) {
			std::cout << "Reached end of file.\n";
			if (curr_boy != boys)
				throw std::exception{ "bad boys column sum" };
			if (curr_girl != girls)
				throw std::exception{ "bad girls column sum" };
		}

		boys += curr_boy;
		girls += curr_girl;
	}
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}