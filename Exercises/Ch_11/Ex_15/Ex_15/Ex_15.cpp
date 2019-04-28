#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>

void set_streams(std::ifstream&, std::ofstream&);
void set_numbers(std::ifstream&, std::vector<double>&);
void write_numbers(std::ofstream&, const std::vector<double>&);

int main()
try {
	std::ifstream ifs;
	std::ofstream ofs;
	set_streams(ifs, ofs);

	std::vector<double> numbers;
	set_numbers(ifs, numbers);

	write_numbers(ofs, numbers);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}

void set_streams(std::ifstream& ifs, std::ofstream& ofs)
{
	static const std::string input_file{ "Ex_15_input.txt" };
	static const std::string output_file{ "Ex_15_output.txt" };

	ifs.open(input_file);
	ofs.open(output_file);

	if (!ifs || !ofs)
		throw std::exception("couldn't open file");

	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);
}

void set_numbers(std::ifstream & ifs, std::vector<double> & numbers)
{
	for (double number; ifs >> number;)
		numbers.push_back(number);
	if (!ifs.eof() && ifs.fail())
		throw std::exception("invalid input");
}

void write_numbers(std::ofstream & ofs, const std::vector<double> & numbers)
{
	static const int column_width = 20;
	static const int precision = 8;
	static const int row_size = 4;

	for (int i = 0; i < numbers.size(); ++i) {
		ofs << std::setw(column_width) << std::scientific <<
			std::setprecision(precision) << numbers[i];
		if ((i + 1) % row_size == 0)
			ofs << '\n';
	}
}