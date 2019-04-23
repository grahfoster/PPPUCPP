#include <fstream>
#include <iostream>
#include <vector>

void read_files(std::vector<std::string>&);
void write_file(const std::vector<std::string>&);

int main()
try {
	std::vector<std::string> sorted_words;

	read_files(sorted_words);
	write_file(sorted_words);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}

void read_files(std::vector<std::string>& sorted_words) {
	static const std::string input_file1{ "Ex_09_input1.txt" };
	static const std::string input_file2{ "Ex_09_input2.txt" };

	bool file1_is_finished = false;
	bool file2_is_finished = false;

	std::ifstream ifs1{ input_file1 };
	std::ifstream ifs2{ input_file2 };

	if (!ifs1 || !ifs2)
		throw std::exception("couldn't open file");

	ifs1.exceptions(ifs1.exceptions() | std::ios_base::badbit);
	ifs2.exceptions(ifs2.exceptions() | std::ios_base::badbit);

	std::string word;
	while (!file1_is_finished && !file2_is_finished) {
		ifs1 >> word;
		if (ifs1.eof()) {
			file1_is_finished = true;
			ifs1.clear();
		}
		if (ifs1.fail())
			throw std::exception("invalid file input");
		sorted_words.push_back(word);

		ifs2 >> word;
		if (ifs2.eof()) {
			file2_is_finished = true;
			ifs2.clear();
		}
		if (ifs2.fail())
			throw std::exception("invalid file input");
		sorted_words.push_back(word);
	}
}

void write_file(const std::vector<std::string>& sorted_words) {
	static const std::string output_file{ "Ex_09_output.txt" };

	std::ofstream ofs{ output_file };
	if (!ofs)
		throw std::exception("couldn't open file");

	for (std::string word : sorted_words)
		ofs << word << '\n';
	if (!ofs)
		throw std::exception("invalid output");
}