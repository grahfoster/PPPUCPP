#include <iostream>
#include <random>
#include <chrono>

int main()
try {
	std::default_random_engine ran{ unsigned(std::chrono::system_clock::now().time_since_epoch().count()) };
	std::uniform_real_distribution<> ureal{ 0, 10 };

	std::vector<double> vd1;
	std::vector<double> vd2;

	for (int i = 0; i < 500000; ++i)
		vd1.push_back(ureal(ran));
	for (int i = 0; i < 5000000; ++i)
		vd2.push_back(ureal(ran));

	auto start = std::chrono::system_clock::now();
	std::sort(vd1.begin(), vd1.end());
	auto end = std::chrono::system_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Sorting vd1's " << vd1.size() << " elements took " << duration.count() << " milliseconds.\n";

	start = std::chrono::system_clock::now();
	std::sort(vd2.begin(), vd2.end());
	end = std::chrono::system_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Sorting vd2's " << vd2.size() << " elements took " << duration.count() << " milliseconds.\n";
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}