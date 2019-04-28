#include <vector>
#include <iostream>
#include <sstream>

void set_line(std::string&);
std::vector<std::string> split(const std::string&);

int main()
try {
	std::string line;
	set_line(line);

	std::vector<std::string> words{ split(line) };
	for (std::string word : words)
		std::cout << word << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}

void set_line(std::string& line)
{
	std::getline(std::cin, line);
	if (std::cin.eof())
		throw std::exception("no input");
	if (!std::cin)
		throw std::exception("invalid input");
}

std::vector<std::string> split(const std::string& line)
{
	std::vector<std::string> words;
	std::istringstream iss{ line };

	for (std::string word; iss >> word;)
		words.push_back(word);
	if (!iss.eof() && iss.fail())
		throw std::exception("invalid input");

	return words;
}