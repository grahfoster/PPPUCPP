#include <iostream>

char* findx(const char* s, const char* x)
{
	for (int i = 0; s[i]; ++i)
		for (int j = 0; s[i + j] == x[j];)
			if (!x[++j])
				return const_cast<char*>(&s[i]);
	return nullptr;
}

int main()
try {
	char s[] = "string";
	char x[] = "trin";

	char* c = findx(s, x);
	if (c)
		std::cout << "String x begins at address " << static_cast<void*>(c) << ".\n";
	else
		std::cout << "String x is not contained within string s.\n";
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}