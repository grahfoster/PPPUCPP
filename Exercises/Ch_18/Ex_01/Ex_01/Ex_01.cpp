#include <iostream>

int strlength(const char* s)
{
	int length = 0;
	while (*s) {
		++length;
		++s;
	}

	return length;
}

char* strdupe(const char* s)
{
	const int length = strlength(s);
	char* cp = new char[length + 1];

	while (*s)
		*cp++ = *s++;
	*cp = *s;

	return cp - length;
}

int main()
try {
	char s[] = "string";
	char* cp = strdupe(s);

	const int length = strlength(cp);
	for (int i = 0; i < length; ++i)
		std::cout << *cp++;
	std::cout << '\n';

	delete[] (cp - length);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}