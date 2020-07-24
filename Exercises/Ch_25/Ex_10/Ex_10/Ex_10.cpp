#include <iostream>

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

void print_info(const PPN& ppn)
{
	std::cout << "PFN: " << ppn.PFN <<
		"\nCCA: " << ppn.CCA <<
		"\nnonreachable: " << ppn.nonreachable <<
		"\ndirty: " << ppn.dirty <<
		"\nvalid: " << ppn.valid <<
		"\nglobal: " << ppn.global << "\n\n";
}

void print_info(const unsigned int ui)
{
	std::cout << "PFN: " << (ui >> num_bits - 22) <<
		"\nCCA: " << ((ui >> num_bits - 28) & 0b111)  <<
		"\nnonreachable: " << ((ui >> num_bits - 29) & 0b1) <<
		"\ndirty: " << ((ui >> num_bits - 30) & 0b1) <<
		"\nvalid: " << ((ui >> num_bits - 31) & 0b1) <<
		"\nglobal: " << ((ui >> num_bits - 32) & 0b1) << "\n\n";
}

int main()
try {
	PPN ppn{ 1234, 5, 0, 0, 1, 1 };
	print_info(ppn);
	
	ppn.PFN = 2468;
	ppn.CCA = 3;
	ppn.nonreachable = true;
	ppn.dirty = true;
	ppn.valid = false;
	ppn.global = false;
	print_info(ppn);

	unsigned int ui = 0xaaaaaaaa;
	print_info(ui);

	ui = 0x55555555;
	print_info(ui);

}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}