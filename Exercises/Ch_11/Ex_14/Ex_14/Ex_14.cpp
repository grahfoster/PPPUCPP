#include <fstream>
#include <vector>
#include <iostream>

enum class Type {
	whitespace, letter, decimal, hexadecimal, uppercase, lowercase,
	alphanumeric, control, punctuation, printable, graphic, size
};

void set_stream(std::ifstream&);
void set_type_counts(std::ifstream&, std::vector<int>&);
void print_type_counts(const std::vector<int>&);

int main()
try {
	std::ifstream ifs;
	std::vector<int> type_counts(int(Type::size), 0);
	
	set_stream(ifs);
	set_type_counts(ifs, type_counts);
	print_type_counts(type_counts);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}

void set_stream(std::ifstream& ifs)
{
	static const std::string input_file{ "Ex_14_input.txt" };

	ifs.open(input_file);
	if (!ifs)
		throw std::exception("couldn't open file");
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);
}

void set_type_counts(std::ifstream& ifs, std::vector<int>& type_counts)
{

	for (char c = 0; ifs.get(c);) {
		if (isspace(c))
			++type_counts[int(Type::whitespace)];
		if (isalpha(c))
			++type_counts[int(Type::letter)];
		if (isdigit(c))
			++type_counts[int(Type::decimal)];
		if (isxdigit(c))
			++type_counts[int(Type::hexadecimal)];
		if (isupper(c))
			++type_counts[int(Type::uppercase)];
		if (islower(c))
			++type_counts[int(Type::lowercase)];
		if (isalnum(c))
			++type_counts[int(Type::alphanumeric)];
		if (iscntrl(c))
			++type_counts[int(Type::control)];
		if (ispunct(c))
			++type_counts[int(Type::punctuation)];
		if (isprint(c))
			++type_counts[int(Type::printable)];
		if (isgraph(c))
			++type_counts[int(Type::graphic)];
	}
	if (!ifs.eof() && ifs.fail())
		throw std::exception("invalid input");
}

void print_type_counts(const std::vector<int>& type_counts)
{
	std::vector<std::string> type_labels{
		"Whitespace", "Letter", "Decimal", "Hexadecimal", "Uppercase",
		"Lowercase", "Alphanumeric", "Control Character", "Punctuation",
		"Printable", "Graphic"
	};

	for (int i = 0; i < int(Type::size); ++i)
		std::cout << type_labels[i] << ": " << type_counts[i] << '\n';
}