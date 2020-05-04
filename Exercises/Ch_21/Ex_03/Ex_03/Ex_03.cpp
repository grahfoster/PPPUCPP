#include <iostream>
#include <vector>

template<class Iter, class T>
int my_count(Iter first, Iter last, const T& val)
{
	int count = 0;
	while (first != last)
		if (*first++ == val)
			++count;
	return count;
}

int main()
try {
	std::vector<int> vi{ 1, 2, 3, 2, 1 };
	int count = my_count(vi.begin(), vi.end(), 1);
	std::cout << "Count: " << count << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}