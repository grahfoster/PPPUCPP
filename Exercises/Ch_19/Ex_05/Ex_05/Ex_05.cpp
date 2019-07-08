#include <iostream>

struct Int {
	int val;

	Int(int v = int{}) : val{ v } {}
	Int(const Int& i) : val{ i.val } {}
	Int(Int&& i) : val{ i.val } {}

	Int& operator=(const Int&);
	Int& operator=(Int&&);
};

Int& Int::operator=(const Int& i) {
	val = i.val;
	return *this;
}

Int& Int::operator=(Int&& i) {
	val = i.val;
	return *this;
}

Int operator+(const Int& i1, const Int& i2) { return Int{ i1.val + i2.val }; }
Int operator-(const Int& i1, const Int& i2) { return Int{ i1.val - i2.val }; }
Int operator*(const Int& i1, const Int& i2) { return Int{ i1.val * i2.val }; }
Int operator/(const Int& i1, const Int& i2) { return Int{ i1.val / i2.val }; }

std::istream& operator>>(std::istream& is, Int& i) {
	is >> i.val;
	return is;
}

std::ostream& operator<<(std::ostream& os, const Int& i) {
	os << i.val;
	return os;
}

Int f() { return Int{ 2 }; }

int main()
try {
	Int int1;
	Int int2{ 1 };
	Int int3{ f() };

	std::cout << "int1: " << int1 << "\nint2: " << int2 << "\nint3: " << int3 <<
		"\nint1 + int2: " << int1 + int2 << "\nint2 - int1: " << int2 - int1 <<
		"\nint2 * int3: " << int2 * int3 << "\nint3 / int2: " << int3 / int2 << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}