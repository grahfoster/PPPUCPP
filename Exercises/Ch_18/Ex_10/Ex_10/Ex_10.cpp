#include <iostream>

//std::istream& read_word1(std::istream& is, char* buffer, int max)
//{
//	is.width(max);
//	is >> buffer;
//	if (std::strlen(buffer) == max - 1)
//		throw std::exception("read_word1() - input too long");
//	return is;
//}

std::istream& read_word2(std::istream& is, char*& buffer)
{
	int limit = 10;
	buffer = new char[limit];

	char c = 0;
	for (int i = 0; is.get(c) || is.eof(); ++i) {
		if (c == '\n' || is.eof()) {
			is.clear();
			buffer[i] = 0;
			break;
		}
		if (i == limit - 1) {
			char* temp = buffer;
			limit *= 2;
			buffer = new char[limit];
			std::copy(temp, &temp[limit / 2], buffer);
			delete[] temp;
		}
		buffer[i] = c;
	}
	return is;
}

bool is_palindrome(const char s[], int n)
{
	int first = 0;
	int last = n - 1;
	while (first < last) {
		if (s[first] != s[last])
			return false;
		++first;
		--last;
	}
	return true;
}

int main()
try {
	/*constexpr int max = 10;
	for (char s[max]; read_word1(std::cin, s, max);) {
		std::cout << s << " is";
		if (!is_palindrome(s, std::strlen(s)))
			std::cout << " not";
		std::cout << " a palindrome\n";
	}*/

	char* s = nullptr;
	while (read_word2(std::cin, s)) {
		std::cout << s << " is";
		if (!is_palindrome(s, std::strlen(s)))
			std::cout << " not";
		std::cout << " a palindrome\n";
	}
	if (s)
		delete[] s;
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}