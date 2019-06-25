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

int strcomp(const char* s1, const char* s2)
{
	const int length1 = strlength(s1);
	const int length2 = strlength(s2);
	const int length = length1 < length2 ? length1 : length2;
	for (int i = 0; i < length; ++i) {
		if (*s1 < *s2)
			return 1;
		if (*s1 > * s2)
			return -1;
		++s1;
		++s2;
	}
	if (length1 == length2)
		return 0;
}

int main()
try {
	const int i = strcomp("string1", "string2");
	std::cout << "String 1 ";
	switch (i) {
	case 1:
		std::cout << "comes before";
		break;
	case -1:
		std::cout << "comes after";
		break;
	default:
		std::cout << "is lexicographically equal to";
	}
	std::cout << " string 2.\n";
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}