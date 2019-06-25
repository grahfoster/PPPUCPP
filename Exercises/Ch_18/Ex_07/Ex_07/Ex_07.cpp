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

char* cat_dot1(const char* s1, const char* s2) {
	const int length = strlength(s1) + 1 + strlength(s2);
	char* cp = new char[length + 1];

	while (*s1)
		* cp++ = *s1++;
	*cp++ = '.';
	while (*s2)
		* cp++ = *s2++;
	*cp = *s2;

	return cp - length;
}

char* cat_dot2(const char* s1, const char* s2, const char* s3) {
	const int length = strlength(s1) + strlength(s3) + strlength(s2);
	char* cp = new char[length + 1];

	while (*s1)
		* cp++ = *s1++;
	while (*s3)
		* cp++ = *s3++;
	while (*s2)
		* cp++ = *s2++;
	*cp = *s2;

	return cp - length;
}

int main()
try {
	char* s1 = cat_dot1("string1", "string2");
	for (int i = 0; i < strlength(s1); ++i)
		std::cout << s1[i];
	std::cout << '\n';

	char* s2 = cat_dot2("string1", "string2", "string3");
	for (int i = 0; i < strlength(s2); ++i)
		std::cout << s2[i];
	std::cout << '\n';

	delete[] s1;
	delete[] s2;
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}