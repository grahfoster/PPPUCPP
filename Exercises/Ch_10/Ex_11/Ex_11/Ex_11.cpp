#include <vector>
#include <iostream>
#include <fstream>
#include <string>

void read_file(std::vector<std::string>&);
int find_sum(const std::vector<std::string>&);

int main()
try {
	std::vector<std::string> numbers;

	read_file(numbers);
	std::cout << "Sum: " << find_sum(numbers) << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}

void read_file(std::vector<std::string>& numbers) {
	static const std::string input_file{ "Ex_11_input.txt" };

	std::ifstream ifs{ input_file };
	if (!ifs)
		throw std::exception("couldn't open file");
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);
	
	std::string number;
	while (!ifs.eof()) {
		ifs >> number;

		bool is_number = true;
		for (char c : number)
			if (!isdigit(c))
				is_number = false;

		if (is_number)
			numbers.push_back(number);
	}
	if (!ifs)
		throw std::exception("invalid file input");
}

int find_sum(const std::vector<std::string>& numbers) {
	int sum = 0;

	for (std::string number : numbers)
		sum += stoi(number);
	
	return sum;
}