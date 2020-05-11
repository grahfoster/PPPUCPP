#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <algorithm>

struct Freq_comp {
	bool operator()(const std::pair<std::string, int>& psi1, const std::pair<std::string, int>& psi2) const {
		if (psi1.second == psi2.second)
			return psi1.first < psi2.first;
		else
			return psi1.second < psi2.second;
	}
};

struct Letters_comp {
	bool operator()(const std::pair<std::string, int>& psi1, const std::pair<std::string, int>& psi2) const {
		if (psi1.first.size() == psi2.first.size())
			return psi1.first < psi2.first;
		else
			return psi1.first.size() < psi2.first.size();
	}
};

int main()
try {
	std::ifstream ifs{ "Ex_14_input.txt" };
	if (!ifs)
		throw std::exception("input file not found");
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	std::map<std::string, int> msi;
	for (std::string s; ifs >> s;)
		++msi[s];

	if (!ifs && !ifs.eof())
		throw std::exception("bad input");

	std::cout << "Number of occurences of \"car\": " << msi["car"] << '\n';

	std::set<std::pair<std::string, int>, Freq_comp> ssi1{ msi.begin(), msi.end() };
	
	std::cout << "Most frequently appearing word: \"" << ssi1.rbegin()->first << "\" (" << ssi1.rbegin()->second << " occurances)\n";

	std::set<std::pair<std::string, int>, Letters_comp> ssi2{ ssi1.begin(), ssi1.end() };

	std::cout << "Longest word: " << ssi2.rbegin()->first << '\n';
	std::cout << "Shortest word: " << ssi2.begin()->first << '\n';

	auto p = std::find_if(msi.begin(), msi.end(),
		[](const std::pair<std::string, int>& psi) -> bool { return psi.first.front() == 's'; });
	auto q = std::find_if(msi.rbegin(), msi.rend(),
		[](const std::pair<std::string, int>& psi) -> bool { return psi.first.front() == 's'; });

	std::cout << "All words starting with 's':\n";
	while (true) {
		std::cout << p++->first;
		if (*p == *q)
			break;
		std::cout << ", ";
	}
	std::cout << '\n';

	auto r = std::find_if(ssi2.begin(), ssi2.end(),
		[](const std::pair<std::string, int>& psi) -> bool { return psi.first.size() == 4; });
	auto s = std::find_if(ssi2.rbegin(), ssi2.rend(),
		[](const std::pair<std::string, int>& psi) -> bool { return psi.first.size() == 4; });

	std::cout << "All words with 4 letters:\n";
	while (true) {
		std::cout << r++->first;
		if (*r == *s)
			break;
		std::cout << ", ";
	}
	std::cout << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}