#include <iostream>
#include <vector>

template<class T, class U>
T sum(const std::vector<T>& vt, const std::vector<U>& vu)
{
	T sum = T();
	for (int i = 0; i < vt.size() && i < vu.size(); ++i)
		sum += vt[i] * vu[i];
	return sum;
}

int main()
try {
	std::vector<double> vd{ 1.1, 2.2, 3.3 };
	std::vector<int> vi{ 1, 2, 3, 4 };

	std::cout << "Sum: " << sum(vd, vi) << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}