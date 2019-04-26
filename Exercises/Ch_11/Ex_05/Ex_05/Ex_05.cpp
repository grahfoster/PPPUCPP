#include <vector>
#include <iostream>

void set_char_types(std::vector<std::string>& char_types, char);
void print_char_types(const std::string&);

int main()
try {
	std::cout << "Enter some words:\n";
	for (std::string word; std::cin >> word; print_char_types(word));
	if (std::cin.eof())
		throw std::exception("no input");
	if (!std::cin)
		throw std::exception("invalid input");
}
catch (std::exception & e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}

void set_char_types(std::vector<std::string> & char_types, char c)
{
	static std::string alpha{ "letter" };
	static std::string digit{ "decimal" };
	static std::string xdigit{ "hexadecimal" };
	static std::string upper{ "uppercase" };
	static std::string lower{ "lowercase" };
	static std::string alnum{ "alphanumeric" };
	static std::string cntrl{ "control character" };
	static std::string punct{ "punctuation" };
	static std::string print{ "printable" };
	static std::string graph{ "graphic" };

	if (isalpha(c))
		char_types.push_back(alpha);
	if (isdigit(c))
		char_types.push_back(digit);
	if (isxdigit(c))
		char_types.push_back(xdigit);
	if (isupper(c))
		char_types.push_back(upper);
	if (islower(c))
		char_types.push_back(lower);
	if (isalnum(c))
		char_types.push_back(alnum);
	if (iscntrl(c))
		char_types.push_back(cntrl);
	if (ispunct(c))
		char_types.push_back(punct);
	if (isprint(c))
		char_types.push_back(print);
	if (isgraph(c))
		char_types.push_back(graph);
}

void print_char_types(const std::string & word)
{
	std::cout << "Characters in " << word << ":\n";
	for (char c : word) {
		std::vector<std::string> char_types;
		set_char_types(char_types, c);

		std::cout << c << " (";
		for (int i = 0; i < char_types.size(); ++i) {
			std::cout << char_types[i];
			if (char_types.size() > 1 && i != char_types.size() - 1)
				std::cout << ", ";
		}
		std::cout << ")\n";
	}
}