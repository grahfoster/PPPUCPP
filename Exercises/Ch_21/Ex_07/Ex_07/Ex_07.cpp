#include <iostream>
#include <vector>
#include <list>

template<class Iter, class T>
Iter my_find(Iter first, Iter last, const T& val)
{
	int diff = std::distance(first, last) / 2;
	auto p = first;
	std::advance(p, diff);
	for (int i = 1; p != last && *p != val; ++i) {
		if (diff > 1)
			diff /= 2;
		if (*p > val)
			std::advance(p, -diff);
		else
			std::advance(p, diff);
	}
	return p;
}

int main()
try {
	std::vector<int> vi{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	auto p = my_find(vi.begin(), vi.end(), 2);
	if (p == vi.end())
		std::cout << "Value not found.\n";
	else
		std::cout << "Value found at address " << &*p << '\n';

	std::list<std::string> ls{ "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten" };
	ls.sort();
	auto q = my_find(ls.begin(), ls.end(), "two");
	if (q == ls.end())
		std::cout << "Value not found.\n";
	else
		std::cout << "Value found at address " << &*q << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}