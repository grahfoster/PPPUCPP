#include <iostream>
#include <fstream>
#include <regex>

int main()
try {
	std::ifstream ifs{ "Ex_12_input.txt" };
	if (!ifs)
		throw std::exception("couldn't open input file");
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	std::ofstream ofs{ "Ex_12_output.txt" };
	if (!ofs)
		throw std::exception("couldn't open output file");

	int line_num = 1;
	std::regex pattern{ R"(([1-9]|0[1-9]|1[0-2])[/-]([1-9]|[12]\d|3[01])[/-]([12]\d{3}|\d{2}))" };
	for (std::string s; std::getline(ifs, s); ++line_num) {
		std::smatch matches;
		if (std::regex_search(s, matches, pattern)) {
			std::string ISO_date;
			if (matches[3].length() == 2)
				ISO_date += "20";
			ISO_date += matches[3];
			ISO_date += '-';
			if (matches[1].length() == 1)
				ISO_date += "0";
			ISO_date += matches[1];
			ISO_date += '-';
			if (matches[2].length() == 1)
				ISO_date += "0";
			ISO_date += matches[2];

			const int start = matches.position(0);
			const int end = start + matches[0].length();
			s.erase(s.begin() + start, s.begin() + end);
			s.insert(start, ISO_date);
			ofs << s << '\n';
		}
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