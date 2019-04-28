#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

void set_streams(std::ifstream&, std::ofstream&);
void reverse_file(std::ifstream&, std::ofstream&);

int main()
try {
	std::ifstream ifs;
	std::ofstream ofs;

	set_streams(ifs, ofs);
	reverse_file(ifs, ofs);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}

void set_streams(std::ifstream& ifs, std::ofstream& ofs)
{
	static const std::string input_file{ "Ex_13_input.txt" };
	static const std::string output_file{ "Ex_13_output.txt" };

	ifs.open(input_file);
	ofs.open(output_file);

	if (!ifs || !ofs)
		throw std::exception("couldn't open file");

	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);
	ofs.exceptions(ofs.exceptions() | std::ios_base::badbit);
}

void reverse_file(std::ifstream & ifs, std::ofstream & ofs)
{
	std::vector<std::string> lines;
	for (std::string buffer; std::getline(ifs, buffer);) {
		std::istringstream iss{ buffer };
		std::vector<std::string> words;

		for (std::string word; iss >> word;)
			words.insert(words.begin(), word);
		if (!iss.eof() && iss.fail())
			throw std::exception("invalid input");

		std::string line;
		for (int i = 0; i < words.size(); ++i) {
			line += words[i];
			if (i != words.size() - 1)
				line += ' ';
		}
		lines.insert(lines.begin(), line);
	}
	if (!ifs.eof() && ifs.fail())
		throw std::exception("invalid input");

	for (std::string line : lines)
		ofs << line << '\n';
	if (!ofs.eof() && ofs.fail())
		throw std::exception("invalid output");
}