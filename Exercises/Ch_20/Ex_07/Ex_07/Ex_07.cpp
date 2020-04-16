#include <iostream>
#include <vector>

template<class Iter>
Iter my_max(Iter b, Iter e)
{
	auto max = b;
	for (; b != e; ++b)
		if (*max < *b)
			max = b;
	return max;
}

int main()
try {
	std::vector<std::string> vs{ "one", "two", "three", "four", "five" };
	std::cout << "Lexicographically last string: " << *my_max(vs.begin(), vs.end()) << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}