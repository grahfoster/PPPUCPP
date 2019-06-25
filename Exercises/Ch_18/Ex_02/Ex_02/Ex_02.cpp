#include <iostream>

char* findx(const char* s, const char* x)
{
	while (*s++)
		if (*s == *x) {
			char* cp = const_cast<char*>(s);
			while (*s++ == *x++)
				if (!*x)
					return cp;
		}
	return nullptr;
}

int main()
try {
	char s[] = "string";
	char x[] = "trin";
	
	char* cp = findx(s, x);
	if (cp)
		std::cout << "String x begins at address " << static_cast<void*>(cp) << ".\n";
	else
		std::cout << "String x is not contained within string s.\n";
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}