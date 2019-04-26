#include <fstream>
#include <iostream>
#include <vector>
#include <string>

void set_streams(std::ifstream&, std::ofstream&);
void remove_vowels(std::ifstream&, std::ofstream&);

int main()
try {
	std::ifstream ifs;
	std::ofstream ofs;

	set_streams(ifs, ofs);
	remove_vowels(ifs, ofs);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}

void set_streams(std::ifstream& ifs, std::ofstream& ofs)
{
	static const std::string input_file = "Ex_03_input.txt";
	static const std::string output_file = "Ex_03_output.txt";

	ifs.open(input_file);
	ofs.open(output_file);

	if (!ifs || !ofs)
		throw std::exception("couldn't open file");

	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);
}

bool is_vowel(char c) {
	static const std::vector<char> vowels{ 'a', 'e', 'i', 'o', 'u' };

	for (char vowel : vowels)
		if (c == vowel)
			return true;
	return false;
}

void remove_vowels(std::ifstream& ifs, std::ofstream& ofs)
{
	std::string buffer;

	while (std::getline(ifs, buffer)) {
		for (int i = 0; i < buffer.size(); ++i)
			if (is_vowel(buffer[i]))
				buffer.erase(buffer.begin() + i);

		ofs << buffer << '\n';
	}

	if (ifs.fail() && !ifs.eof())
		throw std::exception("invalid input");
}