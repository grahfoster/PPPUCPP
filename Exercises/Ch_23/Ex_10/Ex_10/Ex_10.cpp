#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <map>

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
	std::ifstream ifs{ "Ex_10_input.txt" };
	if (!ifs)
		throw std::exception{ "couldn't open input file" };

	std::ofstream ofs{ "Ex_10_output.txt" };
	if (!ofs)
		throw std::exception{ "couldn't open output file" };

	std::string line;

	std::regex header{ R"(^[\w ]+(	[\w ]+)*$)" };
	std::regex row{ R"(^([\w ]+)(	\d+)(	\d+)(	\d+)$)" };

	if (std::getline(ifs, line)) {
		std::smatch matches;
		if (!std::regex_match(line, matches, header))
			throw std::exception{ "no header found" };
	}

	ofs << line << '\n';

	int boys = 0, girls = 0;
	std::vector<std::string> extras;
	std::map<int, int> boys_map;
	std::map<int, int> girls_map;
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

		int year;
		std::istringstream iss{ matches[1] };
		if (isdigit(iss.str().front())) {
			iss >> year;
			boys_map[year] += curr_boy;
			girls_map[year] += curr_girl;
		}
		else
			extras.push_back(line);

		boys += curr_boy;
		girls += curr_girl;
	}

	for (const auto& pii : boys_map) {
		int num_girls = girls_map[pii.first];
		ofs << pii.first << '\t' << pii.second << '\t' << num_girls << '\t' << pii.second + num_girls << '\n';
	}

	for (const std::string& extra : extras)
		ofs << extra << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}