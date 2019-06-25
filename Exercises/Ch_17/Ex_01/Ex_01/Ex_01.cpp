#include <iostream>

int main()
try {
	int* p = new int{};
	std::cout << "p: " << p << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}