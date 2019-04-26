#include <fstream>
#include <iostream>
#include <sstream>

void set_stream(std::ifstream&);
void set_string(std::string&);
void find_lines(std::ifstream&, std::string&);

int main()
try {
	std::ifstream ifs;
	std::string word;

	std::cout << "Enter input file name:\n";
	set_stream(ifs);

	std::cout << "Enter a word to search:\n";
	set_string(word);

	std::cout << "Lines where \"" << word << "\" appears:\n";
	find_lines(ifs, word);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}

void set_stream(std::ifstream& ifs)
{
	std::string input_file;
	set_string(input_file);

	ifs.open(input_file);
	if (!ifs)
		throw std::exception("couldn't open file");
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);
}

void set_string(std::string & word)
{
	std::cin >> word;
	if (std::cin.eof())
		throw std::exception("no input");
	if (std::cin.fail())
		throw std::exception("invalid input");
}

void find_lines(std::ifstream & ifs, std::string & word)
{
	std::string buffer;
	int line_num = 1;

	while (ifs) {
		std::getline(ifs, buffer);
		if (!ifs && !ifs.eof())
			throw std::exception("invalid file input");

		std::istringstream iss{ buffer };
		for (std::string s; iss >> s;)
			if (s == word)
				std::cout << "Line " << line_num << ": " << buffer << '\n';

		++line_num;
	}
}