#include <iostream>

std::string cat_dot(const std::string& s1, const std::string& s2) { return s1 + '.' + s2; }

int main()
try {
	std::cout << cat_dot("string1", "string2") << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}