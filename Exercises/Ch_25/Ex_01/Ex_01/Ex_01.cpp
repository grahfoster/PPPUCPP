#include <iostream>
#include <bitset>
#include <string>
#include <fstream>

//struct Message {
//	int i1;
//	int i2;
//	int i3;
//};
//
//struct Node {
//	int i1;
//	int i2;
//};

//void infinite()
//{
//	unsigned char max = 160;
//	for (signed char i = 0; i < max; ++i)
//		std::cout << int(i) << '\n';
//}

//template<class T> void print(T i) { std::cout << i << '\t'; }
//
//void print(char i) { std::cout << int(i) << '\t'; }
//
//void print(signed char i) { std::cout << int(i) << '\t'; }
//
//void print(unsigned char i) { std::cout << int(i) << '\t'; }

void decipher(const unsigned long* const v, unsigned long* const w, const unsigned long* const k)
{
	static_assert(sizeof(long) == 4, "Size of long is wrong for TEA.");

	unsigned long y = v[0];
	unsigned long z = v[1];
	unsigned long sum = 0xc6ef3720;
	const unsigned long delta = 0x9e3779b9;

	for (unsigned long n = 0; n < 32; ++n) {
		z -= (y << 4 ^ y >> 5) + y ^ sum + k[sum >> 11 & 3];
		sum -= delta;
		y -= (z << 4 ^ z >> 5) + z ^ sum + k[sum & 3];
	}

	w[0] = y;
	w[1] = z;
}

int main()
try {
	/*for (int i = 0; i < 3; ++i) {
		Message* pm = new Message;
		std::cout << "Address of pm #" << i + 1 << ": " << pm
			<< "\nSize of Message: " << sizeof(Message) << " bytes\n";

		Node* pn1 = new Node;
		std::cout << "Address of pn1 #" << i + 1 << ": " << pn1
			<< "\nSize of Node: " << sizeof(Node) << " bytes\n";

		delete pm;

		Node* pn2 = new Node;
		std::cout << "Address of pn2 #" << i + 1 << ": " << pn2
			<< "\nSize of Node: " << sizeof(Node) << " bytes\n\n";
	}*/

	/*for (int i; std::cin >> i;)
		std::cout << std::dec << i << "=="
		<< std::hex << "0x" << i << "=="
		<< std::bitset<sizeof(int) * CHAR_BIT>(i) << '\n';*/

		/*infinite();*/

		/*int si = 128;
		char c = si;
		unsigned char uc = si;
		signed char sc = si;
		print(si);
		print(c);
		print(uc);
		print(sc);*/

	const int nchar = 2 * sizeof(long);
	const int kchar = 2 * nchar;

	std::string key;

	std::cout << "Please enter the key:\n";
	std::cin >> key;
	while (key.size() < kchar)
		key += '0';

	std::ifstream inf{ "Ex_01_input.txt" };
	std::ofstream outf{ "Ex_01_output.txt" };
	if (!inf || !outf)
		throw std::exception{ "couldn't open input and output files" };

	const unsigned long* k = reinterpret_cast<const unsigned long*>(key.data());
	unsigned long inptr[2];
	char outbuf[nchar + 1];
	outbuf[nchar] = 0;
	unsigned long* outptr = reinterpret_cast<unsigned long*>(outbuf);
	inf.setf(std::ios_base::hex, std::ios_base::basefield);

	while (inf >> inptr[0] >> inptr[1]) {
		decipher(inptr, outptr, k);
		outf << outbuf;
	}
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}