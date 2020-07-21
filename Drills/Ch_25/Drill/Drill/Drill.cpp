#include <iostream>
#include <vector>

int main()
try {
	/*int v = 1;*/
	unsigned int v = 1;
	for (int i = 0; i < sizeof(v) * CHAR_BIT; ++i) {
		std::cout << v << ' ';
		v <<= 1;
	}
	std::cout << "\n\n";

	std::vector<unsigned short> vus1;
	vus1.push_back(0xffff);
	vus1.push_back(0x0001);
	vus1.push_back(0x8000);
	vus1.push_back(0x00ff);
	vus1.push_back(0xff00);
	vus1.push_back(0x5555);
	vus1.push_back(0xaaaa);

	for (unsigned short us : vus1)
		std::cout << "Decimal: " << std::dec << us << "\tHexadecimal: " << std::hex << us << '\n';
	std::cout << '\n';

	std::vector<unsigned short> vus2;
	unsigned short us = 0;
	us = ~us;
	vus2.push_back(us);
	us = 1;
	vus2.push_back(us);
	us <<= sizeof(us) * CHAR_BIT - 1;
	vus2.push_back(us);
	us = ~0;
	us >>= CHAR_BIT;
	vus2.push_back(us);
	us <<= CHAR_BIT;
	vus2.push_back(us);
	us = 1;
	for (int i = 0; i < CHAR_BIT; ++i) {
		us <<= sizeof(us);
		++us;
	}
	vus2.push_back(us);
	us = ~us;
	vus2.push_back(us);

	for (unsigned short us : vus2)
		std::cout << "Decimal: " << std::dec << us << "\tHexadecimal: " << std::hex << us << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}