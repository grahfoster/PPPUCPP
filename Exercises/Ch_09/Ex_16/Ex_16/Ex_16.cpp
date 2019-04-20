#include "Money.h"

#include <iostream>

int main()
try {
	Money money;

	std::cout << "Enter a currency label (USD/EUR/JPY/GBP) followed by a monetary amount:\n";
	std::cin >> money;

	std::cout << "Total cents: " << money.get_total_cents() << '\n';
	std::cout << money << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}