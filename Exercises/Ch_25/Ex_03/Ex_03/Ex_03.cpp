#include <iostream>
#include <vector>

int main()
try {
	std::vector<signed int> vsi;
	vsi.push_back(0b00000000000000000000000000000000);
	vsi.push_back(0b11111111111111111111111111111111);
	vsi.push_back(0b10101010101010101010101010101010);
	vsi.push_back(0b01010101010101010101010101010101);
	vsi.push_back(0b11001100110011001100110011001100);
	vsi.push_back(0b00110011001100110011001100110011);
	vsi.push_back(0b11111111000000001111111100000000);
	vsi.push_back(0b00000000111111110000000011111111);

	std::vector<unsigned int> vui;
	for (signed int si : vsi) {
		std::cout << si << '\n';
		vui.push_back(si);
	}
	std::cout << '\n';

	for (unsigned int ui : vui)
		std::cout << ui << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}