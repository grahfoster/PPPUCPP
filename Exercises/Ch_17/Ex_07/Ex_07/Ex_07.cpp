#include <iostream>

int main()
try {
	const char terminator = '!';

	int size = 10;

	char* s = new char[size];
	for (int i = 0; std::cin; ++i) {
		char c = std::cin.get();
		if (c == terminator || std::cin.eof()) {
			size = i;
			break;
		}
		s[i] = c;
	}

	for (int i = 0; i < size; ++i)
		std::cout << s[i];
	std::cout << '\n';

	delete[] s;
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}