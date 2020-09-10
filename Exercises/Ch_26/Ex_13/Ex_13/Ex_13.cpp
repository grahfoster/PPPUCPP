#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

int main()
try {
	srand(time(NULL));

	std::vector<std::string> vs1{ 500000 };
	std::vector<std::string> vs2{ 5000000 };

	for (std::string& s : vs1) {
		const int l = rand() % 100 + 1;
		for (int i = 0; i < l; ++i)
			s.push_back(char{ int{'a'} + rand() % (int{'z' - 'a'} + 1) });
	}
	for (std::string& s : vs2) {
		const int l = std::rand() % 100 + 1;
		for (int i = 0; i < l; ++i)
			s.push_back(char{ int{'a'} + rand() % (int{'z' - 'a'} + 1) });
	}

	auto start = std::chrono::system_clock::now();
	std::sort(vs1.begin(), vs1.end());
	auto end = std::chrono::system_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Sorting vd1's " << vs1.size() << " elements took " << duration.count() << " milliseconds.\n";

	start = std::chrono::system_clock::now();
	std::sort(vs2.begin(), vs2.end());
	end = std::chrono::system_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Sorting vd2's " << vs2.size() << " elements took " << duration.count() << " milliseconds.\n";
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}