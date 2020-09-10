#include <iostream>
#include <vector>
#include <map>
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
		const int l = rand() % 100 + 1;
		for (int i = 0; i < l; ++i)
			s.push_back(char{ int{'a'} + rand() % (int{'z' - 'a'} + 1) });
	}

	std::multimap<std::string, int> ms1;
	std::multimap<std::string, int> ms2;

	auto start = std::chrono::system_clock::now();
	for (std::string s : vs1)
		ms1.insert({ s, s.length() });
	auto end = std::chrono::system_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Inserting ms1's " << ms1.size() << " elements took " << duration.count() << " milliseconds.\n";

	start = std::chrono::system_clock::now();
	for (std::string s : vs2)
		ms2.insert({ s, s.length() });
	end = std::chrono::system_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Inserting ms2's " << ms2.size() << " elements took " << duration.count() << " milliseconds.\n";
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}