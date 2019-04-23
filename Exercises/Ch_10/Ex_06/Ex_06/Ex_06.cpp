#include "Roman_int.h"

int main()
try {
	Roman_int roman_int{};

	std::cout << "Enter a Roman numeral:\n";
	while (std::cin >> roman_int) {
		std::cout << "Roman numerals: " << roman_int <<
			"\nArabic numerals: " << roman_int.to_int() <<
			"\n\nEnter another Roman numeral:\n";
	}
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cout << '\n';
	main();
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}