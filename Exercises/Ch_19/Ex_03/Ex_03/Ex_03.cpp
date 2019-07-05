#include <iostream>
#include <vector>

template<class T, class U>
struct Pair {
	T t;
	U u;
};

int main()
try {
	std::vector<Pair<std::string, double>> vp;
	vp.push_back({ "pi", atan(1) * 4 });
	vp.push_back({ "Euler's number", exp(1) });
	vp.push_back({ "Pythagoras's constant", sqrt(2) });

	for (Pair<std::string, double> p : vp)
		std::cout << p.t << ": " << p.u << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}