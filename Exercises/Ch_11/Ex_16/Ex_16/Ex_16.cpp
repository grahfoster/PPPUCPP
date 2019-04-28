#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

void set_stream(std::ifstream&);
void set_numbers(std::ifstream&, std::vector<double>&);
void set_counts(std::vector<double>&, std::vector<int>&);
void print_numbers_counts(const std::vector<double>&, const std::vector<int>&);

int main()
try {
	std::ifstream ifs;
	set_stream(ifs);

	std::vector<double> numbers;
	set_numbers(ifs, numbers);

	std::vector<int> counts;
	set_counts(numbers, counts);

	print_numbers_counts(numbers, counts);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}

void set_stream(std::ifstream& ifs)
{
	static const std::string input_file{ "Ex_16_input.txt" };

	ifs.open(input_file);
	if (!ifs)
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

void set_counts(std::vector<double> & numbers, std::vector<int> & counts)
{
	std::sort(numbers.begin(), numbers.end());

	for (int i = 0, count = 1; i < numbers.size(); ++i) {
		if (i > 0 && numbers[i] == numbers[i - 1])
			++count;
		if (i > 0 && numbers[i] != numbers[i - 1]) {
			counts.push_back(count);
			count = 1;
		}
		if (i == numbers.size() - 1)
			counts.push_back(count);
	}
}

void print_numbers_counts(const std::vector<double> & numbers,
	const std::vector<int> & counts)
{
	for (int i = 0, j = 0; i < numbers.size(); ++i) {
		if (i == 0 || numbers[i] != numbers[i - 1]) {
			std::cout << numbers[i] << '\t' << counts[j] << '\n';
			++j;
		}
	}
}