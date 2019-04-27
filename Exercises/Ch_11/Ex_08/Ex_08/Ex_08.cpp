#include "Punct_stream.h"
#include <fstream>
#include <vector>
#include <algorithm>

void open_stream(std::ifstream&);
void write_dictionary(std::ifstream&);

int main()
try {
	std::ifstream ifs;
	open_stream(ifs);

	std::cout << "Dictionary:\n";
	write_dictionary(ifs);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}

void open_stream(std::ifstream& ifs)
{
	static const std::string input_file{ "Ex_08_input.txt" };

	ifs.open(input_file);
	if (!ifs)
		throw std::exception("couldn't open file");
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);
}

void write_dictionary(std::ifstream & ifs)
{
	Punct_stream ps{ ifs };
	std::vector<std::string> words;

	for (std::string word; ps >> word;)
		words.push_back(word);

	std::sort(words.begin(), words.end());
	for (int i = 0; i < words.size(); ++i)
		if (i == 0 || words[i] != words[i - 1])
			std::cout << words[i] << '\n';
}