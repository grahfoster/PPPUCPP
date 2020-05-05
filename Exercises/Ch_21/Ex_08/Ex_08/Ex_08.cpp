#include <iostream>
#include <fstream>
#include <map>
#include <set>

struct Word_comparison {
	bool operator()(const std::pair<std::string, int>& psi1, const std::pair<std::string, int>& psi2) const {
		if (psi1.second == psi2.second)
			return psi1.first < psi2.first;
		return psi1.second < psi2.second;
	}
};

int main()
try {
	std::ifstream ifs{ "Ex_08_input.txt" };
	if (!ifs)
		throw std::exception("input file not found");
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	std::map<std::string, int> msi;
	for (std::string s; ifs >> s;)
		++msi[s];
	std::set<std::pair<std::string, int>, Word_comparison> spsi{ msi.begin(), msi.end() };
	for (auto psi : spsi)
		std::cout << psi.second << ": " << psi.first << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}