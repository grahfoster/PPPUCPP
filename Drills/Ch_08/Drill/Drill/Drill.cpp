#include "../../../../std_lib_facilities.h"

//void swap_v(int, int);
//void swap_r(int&, int&);
//void swap_cr(const int&, const int&);
//
//
//int main() {
//	int x = 7;
//	int y = 9;
//	swap_cr(x, y);
//	swap_cr(7, 9);
//	const int cx = 7;
//	const int cy = 9;
//	swap_cr(cx, cy);
//	swap_cr(7.7, 9.9);
//	double dx = 7.7;
//	double dy = 9.9;
//	swap_cr(dx, dy);
//	swap_cr(7.7, 9.9);
//}
//
//void swap_v(int a, int b) {
//	int temp;
//	temp = a;
//	a = b;
//	b = temp;
//
//	cout << "a: " << a << ", b: " << b << '\n';
//}
//
//void swap_r(int& a, int& b) {
//	int temp;
//	temp = a;
//	a = b;
//	b = temp;
//
//	cout << "a: " << a << ", b: " << b << '\n';
//}
//
//void swap_cr(const int& a, const int& b) {
//	int temp;
//	temp = a;
//	//a = b;
//	//b = temp;
//
//	cout << "a: " << a << ", b: " << b << '\n';
//}

///

namespace X {
	int var;
	
	void print() {
		cout << var << '\n';
	}
}

namespace Y {
	int var;

	void print() {
		cout << var << '\n';
	}
}

namespace Z {
	int var;

	void print() {
		cout << var << '\n';
	}
}

int main() {
	X::var = 7;
	X::print();
	
	using namespace Y;

	var = 9;
	print();

	{
		using Z::var;
		using Z::print;

		var = 11;
		print();
	}

	print();
	X::print();
}