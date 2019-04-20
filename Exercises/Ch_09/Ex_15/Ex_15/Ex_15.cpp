#include "Money.h"

int main()
try {
	Money money{ Currency::EUR, 12.345 };
	std::cout << "Total cents: " << money.get_total_cents() << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}