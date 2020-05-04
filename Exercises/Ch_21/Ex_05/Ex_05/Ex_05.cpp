#include <iostream>
#include <vector>

template<class Iter, class T>
Iter my_find(Iter first, Iter last, const T& val)
{
	while (first != last && *first != val) {
		++first;
	}
	return first;
}

template<class Iter, class T>
int my_count(Iter first, Iter last, const T& val)
{
	int count = 0;
	while (first <= last)
		if (*first++ == val)
			++count;
	return count;
}

int main()
try {
	std::vector<int> vi{ 1, 2, 3, 2, 1 };
	int val = 4;

	auto p = my_find(vi.begin(), vi.end() - 1, val);
	if (p == vi.begin() + vi.size() - 1 && vi.back() != val)
		std::cout << val << " not found.\n";
	else
		std::cout << val << " found at address " << &*p << '\n';

	int count = my_count(vi.begin(), vi.end() - 1, val);
	std::cout << "Count: " << count << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}