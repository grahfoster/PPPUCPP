#include <iostream>
#include <vector>

template<class T>
void f(std::vector<T>& v1, const std::vector<T>& v2)
{
	for ( int i = 0; i < v1.size() && i < v2.size(); ++i)
		v1[i] += v2[i];
}

int main()
try {
	std::vector<int> v1{ 1, 2, 3, 4 };
	std::vector<int> v2{ 1, 2, 3 };

	f(v1, v2);

	for (int i : v1)
		std::cout << i << ' ';
	std::cout << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}