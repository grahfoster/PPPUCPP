#include <iostream>
#include <vector>

template<class T>
std::istream& operator>>(std::istream& is, std::vector<T>& v)
{
	for (T t; is >> t;)
		v.push_back(t);
	if (!is && !is.eof())
		throw std::exception("bad input format");
	return is;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
	for (T t : v)
		os << t << '\n';
	return os;
}

int main()
try {
	std::vector<int> vi;
	std::cin >> vi;
	std::cout << vi;
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}