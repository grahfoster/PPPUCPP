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

bool is_palindrome1(const std::string& s)
{
	std::string reverse;
	for (int i = s.size() - 1; i >= 0; --i)
		reverse.push_back(s[i]);

	if (s == reverse)
		return true;
	return false;
}

bool is_palindrome2(const char s[], int n)
{
	char* reverse = new char[n];
	for (int i = 0; i < n; ++i)
		reverse[i] = s[n - 1 - i];

	for (int i = 0; i < n; ++i)
		if (s[i] != reverse[i]) {
			delete[] reverse;
			return false;
		}
	delete[] reverse;
	return true;
}

bool is_palindrome3(const char* first, const char* last)
{
	const int length = last - first;
	char* reverse = new char[length];
	for (int i = 0; i < length; ++i)
		reverse[i] = *last--;

	for (int i = 0; i < length; ++i)
		if (*first++ != reverse[i]) {
			delete[] reverse;
			return false;
		}
	delete[] reverse;
	return true;
}

int main()
try {
	const std::string s{ "racecar" };
	std::cout << s << " is " << (is_palindrome1(s) ? "" : "not ") << "a palindrome.\n";

	const char s2[] = "racecar";
	std::cout << s2 << " is " << (is_palindrome2(s2, strlength(s2)) ? "" : "not ") << "a palindrome.\n";

	std::cout << s2 << " is " << (is_palindrome3(s2, &s2[strlength(s2) - 1]) ? "" : "not ") << "a palindrome.\n";
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}