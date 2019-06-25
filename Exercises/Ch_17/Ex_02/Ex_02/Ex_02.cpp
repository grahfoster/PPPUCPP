#include <iostream>

int main()
try {
	std::cout << "Bytes in an int: " << sizeof(int) <<
		"\nBytes in a double: " << sizeof(double) <<
		"\nBytes in a bool: " << sizeof(bool) << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}