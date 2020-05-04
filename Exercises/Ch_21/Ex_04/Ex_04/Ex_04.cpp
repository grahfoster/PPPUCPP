#include <iostream>
#include <vector>

template<class Iter, class Pred>
int my_count_if(Iter first, Iter last, Pred p)
{
	int count = 0;
	while (first != last)
		if (p(*first++))
			++count;
	return count;
}

int main()
try {
	std::vector<int> vi{ 1, 2, 3, 2, 1 };
	int count = my_count_if(vi.begin(), vi.end(), [](int i) -> bool { return i > 1; });
	std::cout << "Count: " << count << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}