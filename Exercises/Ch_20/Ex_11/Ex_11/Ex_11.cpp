#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

std::vector<double> copy_to_vec(const std::list<int>& li)
{
	std::vector<double> vd(li.size());
	std::copy(li.begin(), li.end(), vd.begin());
	return vd;
}

int main()
try {
	std::list<int> li{ 1, 2, 3, 4, 5 };
	std::vector<double> vd = copy_to_vec(li);
	std::sort(vd.begin(), vd.end());

	std::cout << "List contents: ";
	for (int i : li)
		std::cout << i << ' ';
	std::cout << "\nVector contents: ";
	for (double d : vd)
		std::cout << d << ' ';
	std::cout << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}