#include <iostream>

int main()
try {
	int int_bits = 0;
	for (int i = 1; i != 0; i <<= 1)
		++int_bits;
	std::cout << "int has " << int_bits << " bits.\n";
	
	char c = 0;
	c = ~c;
	std::cout << "char is " << (c < 0 ? "signed" : "unsigned") << ".\n";
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}