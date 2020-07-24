#include <iostream>
#include <bitset>
#include <sstream>

constexpr unsigned int num_bits = sizeof(unsigned int) * CHAR_BIT;

struct PPN {
	unsigned int PFN : 22;
	int : 3;
	unsigned int CCA : 3;
	bool nonreachable : 1;
	bool dirty : 1;
	bool valid : 1;
	bool global : 1;
};

unsigned long get_range(const std::bitset<32> bs, const int begin, const int length)
{
	std::ostringstream ss;
	for (int i = begin + length - 1; i >= begin; --i)
		ss << bs[i];
	return std::bitset<32>{ ss.str() }.to_ulong();
}

void print_info(const std::bitset<32> bs)
{
	std::cout << "PFN: " << get_range(bs, num_bits - 22, 22) <<
		"\nCCA: " << get_range(bs, num_bits - 28, 3) <<
		"\nnonreachable: " << get_range(bs, num_bits - 29, 1) <<
		"\ndirty: " << get_range(bs, num_bits - 30, 1) <<
		"\nvalid: " << get_range(bs, num_bits - 31, 1) <<
		"\nglobal: " << get_range(bs, num_bits - 32, 1) << "\n\n";
}

int main()
try {
	std::bitset<32> bs = 0xaaaaaaaa;
	print_info(bs);

	bs = 0x55555555;
	print_info(bs);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}