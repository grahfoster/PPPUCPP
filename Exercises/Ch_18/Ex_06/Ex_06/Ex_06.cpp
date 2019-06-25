#include <iostream>

std::string cat_dot(const std::string& s1, const std::string& s2, const std::string& s3) { return s1 + s3 + s2; }

int main()
try {
	std::cout << cat_dot("string1", "string2", "string3") << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}