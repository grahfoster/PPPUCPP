#include <iostream>
#include <random>
#include <chrono>

int main()
try {
	int n, d;
	std::cout << "Enter two positive integers: one for the maximum inclusive range"
		"and one for the number of times a random number will be produced.\n";
	std::cin >> n >> d;
	if (!std::cin && !std::cin.eof())
		throw std::exception("bad input");
	if (n <= 0 || d <= 0)
		throw std::exception("non-positive integer input");

	std::default_random_engine dre{ unsigned(std::chrono::system_clock::now().time_since_epoch().count()) };
	std::uniform_int_distribution<> uid{ 0, n };
	std::vector<int> vi(n + 1);

	for (int i = 0; i < d; ++i)
		++vi[uid(dre)];
	for (int i = 0; i < vi.size(); ++i)
		std::cout << i << ": " << vi[i] << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}