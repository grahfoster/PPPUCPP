#include <fstream>
#include <iostream>

const std::string file_name = "Ex_01.txt";

void print_sum_from_input();

int main()
try {
	print_sum_from_input();
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}

void print_sum_from_input() {
	int sum = 0;

	std::ifstream ifs{ file_name };

	for (int i = 0; ifs >> i;)
		sum += i;
	if (ifs.eof())
		std::cout << "Sum of input: " << sum << '\n';
	else if (!ifs) {
		throw std::exception("invalid input");
	}
}