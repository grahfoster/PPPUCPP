#include <fstream>
#include <iostream>
#include <string>

void set_streams(std::ifstream&, std::ofstream&);
void convert_input(std::ifstream&, std::ofstream&);

int main()
try {
	std::ifstream ifs;
	std::ofstream ofs;

	set_streams(ifs, ofs);

	convert_input(ifs, ofs);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}

void set_streams(std::ifstream& ifs, std::ofstream& ofs)
{
	static const std::string input_file = "Ex_01_input.txt";
	static const std::string output_file = "Ex_01_output.txt";

	ifs.open(input_file);
	ofs.open(output_file);

	if (!ifs || !ofs)
		throw std::exception("couldn't open file");

	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);
}

void convert_input(std::ifstream& ifs, std::ofstream& ofs)
{
	std::string buffer;

	while (std::getline(ifs, buffer)) {
		for (char& ch : buffer)
			ch = tolower(ch);

		ofs << buffer << '\n';
	}
}