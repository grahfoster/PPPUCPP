#include <iostream>
#include <vector>
#include <list>

template<class I1, class I2>
I2 my_copy(I1 b1, I1 e1, I2 b2)
{
	while (b1 != e1) {
		*b2 = *b1;
		++b1;
		++b2;
	}
	return b2;
}

int main()
try {
	constexpr int length = 10;

	int ai[length]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::vector<int> vi{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::list<int> li{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	int ai2[length];
	std::copy(ai, &ai[length], ai2);
	std::vector<int> vi2{ vi };
	std::list<int> li2{ li };

	for (int i = 0; i < length; ++i) {
		ai[i] += 2;
		vi[i] += 3;		
	}
	for (int i : li)
		i += 5;

	my_copy(ai, &ai[length], vi.begin());
	my_copy(li.begin(), li.end(), ai);

	auto p1 = find(vi.begin(), vi.end(), 3);
	std::cout << "3 found at position " << int(p1 - vi.begin()) << '\n';
	auto p2 = find(vi.begin(), vi.end(), 27);
	std::cout << "27 found at position " << int(p2 - vi.begin()) << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}