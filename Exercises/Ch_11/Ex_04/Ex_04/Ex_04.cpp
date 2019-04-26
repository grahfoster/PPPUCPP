#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>

enum class Type {
	decimal, hexadecimal, octal
};

const std::vector<std::string> type_prefixes{ "", "0x", "0" };

void read_ints(std::vector<std::string>&, std::vector<int>&,
	std::vector<Type>&);
void print_ints(const std::vector<std::string>&, const std::vector<int>&,
	const std::vector<Type>&);

int main()
try {
	std::vector<int> ints;
	std::vector<Type> types;
	std::vector<std::string> nums;

	std::cout << "Enter some integers (decimal, octal, or hexadecimal):\n";
	read_ints(nums, ints, types);

	std::cout << "Input summary:\n";
	print_ints(nums, ints, types);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}

bool is_num(std::string num)
{
	static const int oct_min = 0;
	static const int oct_max = 7;

	if (num.size() > 2 &&
		num.substr(0, 2) == type_prefixes[int(Type::hexadecimal)]) {
		num = num.substr(2, num.size() - 1);
		for (char c : num)
			if (!isxdigit(c))
				return false;
		return true;
	}
	if (num.substr(0, 1) == type_prefixes[int(Type::octal)]) {
		for (char c : num)
			if (oct_min > c - '0' || c - '0' > oct_max)
				return false;
		return true;
	}
	for (char c : num)
		if (!isdigit(c))
			return false;
	return true;
}

void read_ints(std::vector<std::string>& nums, std::vector<int>& ints,
	std::vector<Type>& types)
{
	std::string num;
	while (std::cin >> num) {
		if (!is_num(num))
			throw std::exception("invalid input");
		nums.push_back(num);

		std::istringstream iss{ num };
		iss.unsetf(std::ios::dec | std::ios::hex | std::ios::oct);
		for (int i = 0; iss >> i;)
			ints.push_back(i);

		if (num.size() > 1 &&
			num.substr(0, 2) == type_prefixes[int(Type::hexadecimal)])
			types.push_back(Type::hexadecimal);
		if (num.substr(0, 1) == type_prefixes[int(Type::octal)])
			types.push_back(Type::octal);
		else
			types.push_back(Type::decimal);
	}
	if (std::cin.fail() && !std::cin.eof())
		throw std::exception("invalid input");
}

void print_ints(const std::vector<std::string> & nums,
	const std::vector<int> & ints, const std::vector<Type> & types)
{
	static const int column_sm = 10;
	static const int column_md = 15;
	static const int column_lg = 20;
	static const std::vector<std::string> type_names{
		"decimal", "hexadecimal", "octal"
	};
	static const std::string converts_to{ "converts to" };

	for (int i = 0; i < ints.size(); ++i) {
		std::cout << std::setw(column_sm) << nums[i] <<
			std::setw(column_md) << type_names[int(types[i])] <<
			std::setw(column_md) << converts_to <<
			std::setw(column_lg) << std::to_string(ints[i]) + ' ' +
			type_names[int(Type::decimal)] << '\n';
	}
}