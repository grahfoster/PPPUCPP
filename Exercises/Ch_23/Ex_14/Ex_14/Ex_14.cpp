#include <iostream>
#include <fstream>
#include <regex>

int main()
try {
	std::string pat;
	std::cout << "Please enter a pattern:\n";
	std::getline(std::cin, pat);
	std::regex pattern{ pat };

	/* Example patterns:
	1. \d\n\d
	2. \d{20}\n\d{20}
	3. 004\n331
	4. 004\n332
	5. \d{15}\n\d{16}\n\d{19}
	6. \d{15}\n\d{16}\n\d{20}
	7. \n
	8. \n\n
	9. \d+\n\d+\n\d+\n\d+
	10. (\d+\n)+
	11. (\d+\n){10}
	12. (\d+\n){20} */

	std::string file_name;
	std::cout << "Please enter the name of a file to match from:\n";
	std::cin >> file_name;

	std::ifstream ifs{ file_name };
	if (!ifs)
		throw std::exception("couldn't open input file");
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	std::string buffer;
	for (std::string line; std::getline(ifs, line); buffer += line + '\n');

	std::smatch matches;
	if (std::regex_search(buffer, matches, pattern))
		std::cout << "Pattern found.\n";
	else
		std::cout << "Pattern not found.\n";
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}