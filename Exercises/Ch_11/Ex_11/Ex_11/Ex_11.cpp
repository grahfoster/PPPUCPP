#include <vector>
#include <iostream>
#include <sstream>

void set_line(std::string&);
void set_whitespaces(std::string&);
std::vector<std::string> split(std::string&, const std::string&);

int main()
try {
	std::string line;
	std::string whitespaces;

	set_line(line);
	set_whitespaces(whitespaces);

	std::vector<std::string> words{ split(line, whitespaces) };
	for (std::string word : words)
		std::cout << word << '\n';
}
catch (std::exception & e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}

void set_line(std::string & line)
{
	std::getline(std::cin, line);
	if (std::cin.eof())
		throw std::exception("no input");
	if (!std::cin)
		throw std::exception("invalid input");
}

void set_whitespaces(std::string & whitespaces)
{
	std::cin >> whitespaces;
	if (std::cin.eof())
		throw std::exception("no input");
	if (!std::cin)
		throw std::exception("invalid input");
}

bool is_whitespace(char c, const std::string & whitespaces)
{
	for (char whitespace : whitespaces)
		if (c == whitespace)
			return true;
	return false;
}

std::vector<std::string> split(std::string & line,
	const std::string & whitespaces)
{
	for (char& c : line)
		if (is_whitespace(c, whitespaces))
			c = ' ';

	std::istringstream iss{ line };
	std::vector<std::string> words;

	for (std::string word; iss >> word;)
		words.push_back(word);
	if (!iss.eof() && iss.fail())
		throw std::exception("invalid input");

	return words;
}