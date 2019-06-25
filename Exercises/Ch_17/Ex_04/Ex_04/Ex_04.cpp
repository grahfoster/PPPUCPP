#include <iostream>

char* strdupe(const char* s) {
	int size = 0;
	while (s[size])
		++size;

	char* n = new char[size];
	for (int i = 0; i < size; ++i)
		n[i] = s[i];

	return n;
}

int main()
try {
	char s[] = "string";
	char* n = strdupe(s);

	for (int i = 0; i < 6; ++i)
		std::cout << n[i];
	std::cout << '\n';

	delete[] n;
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}