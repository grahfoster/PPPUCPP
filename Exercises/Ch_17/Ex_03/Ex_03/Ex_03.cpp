#include <iostream>

void to_lower(char* s)
{
	for (int i = 0; s[i]; ++i)
		if ('A' <= s[i] && s[i] <= 'Z')
			s[i] += 'a' - 'A';
}

int main()
try {
	char s[] = "sTrInG";
	to_lower(s);
	std::cout << s << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}