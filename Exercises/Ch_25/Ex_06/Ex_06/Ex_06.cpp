#include <iostream>

int main()
try {
	constexpr unsigned short max = USHRT_MAX;
	for (signed short ss = 0; ss < max; ++ss);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}