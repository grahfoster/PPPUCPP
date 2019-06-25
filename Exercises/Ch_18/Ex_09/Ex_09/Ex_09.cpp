#include <iostream>
#include <vector>
#include <algorithm>

int gi;

struct Address {
	int* value;
	std::string type;
};

std::ostream& operator<<(std::ostream& os, const Address& addr) { 
	os << addr.type << ": " << addr.value;
	return os;
}

bool addr_comp(const Address& addr1, const Address& addr2) { return addr1.value < addr2.value; }

int main()
try {
	int li1;
	int li2;
	int* ip = new int[2];

	std::vector<Address> addrs{ 
		Address{ &gi, "Static"}, Address{ &li1, "Stack1"}, Address{ &li2, "Stack2"},
		Address{ ip, "Heap 1"}, Address{ &ip[1], "Heap 2"}

	};
	std::sort(addrs.begin(), addrs.end(), addr_comp);
	for (int i = 0; i < addrs.size(); ++i)
		std::cout << i + 1 << ". " << addrs[i] << '\n';

	delete[] ip;
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}