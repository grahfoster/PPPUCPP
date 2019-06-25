#include <iostream>

int main()
try {
	std::string s;
	std::cin >> s;
	std::cout << s << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}