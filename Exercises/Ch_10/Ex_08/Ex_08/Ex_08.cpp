#include <fstream>
#include <iostream>
#include <vector>

void set_input_streams(std::ifstream&, std::ifstream&);
void read_files(std::ifstream&, std::ifstream&, std::vector<char>&);
void write_file(const std::vector<char>&);

int main()
try {
	std::ifstream ifs1;
	std::ifstream ifs2;
	std::vector<char> file_buffer;

	std::cout << "Enter the names of two input files to concatenate:\n";
	set_input_streams(ifs1, ifs2);

	std::cout << "Reading files...\n";
	read_files(ifs1, ifs2, file_buffer);

	std::cout << "Writing new file...\n";
	write_file(file_buffer);

	std::cout << "Success!\n";
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}

void set_input_streams(std::ifstream& ifs1, std::ifstream& ifs2) {
	std::string input_file1;
	std::string input_file2;
	std::cin >> input_file1 >> input_file2;
	if (!std::cin)
		throw std::exception("invalid user input");

	ifs1.open(input_file1);
	ifs2.open(input_file2);

	if (!ifs1 || !ifs2)
		throw std::exception("couldn't open file");

	ifs1.exceptions(ifs1.exceptions() | std::ios_base::badbit);
	ifs2.exceptions(ifs2.exceptions() | std::ios_base::badbit);
}

void read_files(std::ifstream & ifs1, std::ifstream & ifs2,
	std::vector<char> & file_buffer) {
	char ch;
	while (ifs1.get(ch))
		file_buffer.push_back(ch);
	if (ifs1.eof())
		ifs1.clear();
	if (ifs1.fail())
		throw std::exception("invalid file input");

	while (ifs2.get(ch))
		file_buffer.push_back(ch);
	if (ifs2.eof())
		ifs2.clear();
	if (ifs2.fail())
		throw std::exception("invalid file input");
}

void write_file(const std::vector<char> & file_buffer) {
	static const std::string output_file{ "Ex_08_output.txt" };

	std::ofstream ofs{ output_file };
	if (!ofs)
		throw std::exception("couldn't open file");

	for (char ch : file_buffer)
		ofs << ch;
	if (!ofs)
		throw std::exception("invalid output");
}