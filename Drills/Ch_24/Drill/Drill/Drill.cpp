#include "../../../../MatrixIO.h"
#include <iostream>
#include <complex>
#include <numeric>

using namespace Numeric_lib;

int main()
try {
	/*std::cout << "Size of char: " << sizeof(char) <<
		"\nSize of short: " << sizeof(short) <<
		"\nSize of int: " << sizeof(int) <<
		"\nSize of long: " << sizeof(long) <<
		"\nSize of float: " << sizeof(float) <<
		"\nSize of double: " << sizeof(double) <<
		"\nSize of int*: " << sizeof(int*) <<
		"\nSize of double*: " << sizeof(double*) << '\n';*/

	/*Matrix<int> a{ 10 };
	Matrix<int> b{ 100 };
	Matrix<double> c{ 10 };
	Matrix<int, 2> d{ 10, 10 };
	Matrix<int, 3> e{ 10, 10, 10 };*/

	/*std::cout << "Size of Matrix<int>{ 10 }: " << sizeof(a) <<
		"\nSize of Matrix<int>{ 100 }: " << sizeof(b) <<
		"\nSize of Matrix<double>{ 10 }: " << sizeof(c) <<
		"\nSize of Matrix<int, 2>{ 10, 10 }: " << sizeof(d) <<
		"\nSize of Matrix<int, 3>{ 10, 10, 10 }: " << sizeof(e) << '\n';*/

	/*std::cout << "a: \n" << a <<
		"\nb: \n" << b <<
		"\nc: \n" << c <<
		"\nd: \n" << d <<
		"\ne: \n" << "N/A" << '\n';*/

	/*std::cout << "Please enter some integers:\n";
	for (int i = 0; std::cin >> i;) {
		errno = 0;
		double sq_rt = sqrt(i);
		if (errno == EDOM)
			std::cerr << "sqrt() is not defined for negative arguments.\n";
		else
			std::cout << "The square root of " << i << " is " << sq_rt << '\n';
	}

	if (!std::cin && !std::cin.eof())
		throw std::exception{ "bad input" };*/

	/*Matrix<double> md{ 10 };
	std::cout << "Please enter ten floating-point values:\n";
	for (Index i = 0; i < md.size(); ++i) {
		double d = 0;
		while (!(std::cin >> d)) {
			std::cerr << "Please enter exactly ten floating-point values.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		md(i) = d;
	}

	std::cout << md;*/

	/*const int n = 12, m = 12;
	Matrix<int, 2> times_table{ n, m };
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			times_table(i - 1, j - 1) = i * j;
	
	std::cout << times_table << '\n';*/

	/*Matrix<std::complex<double>> mcd{ 10 };
	std::complex<double> sum;
	std::cout << "Please enter ten complex values:\n";
	for (Index i = 0; i < mcd.size(); ++i) {
		std::complex<double> cd;
		while (!(std::cin >> cd)) {
			std::cerr << "Please enter exactly ten complex values.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		mcd(i) = cd;
		sum += cd;
	}

	std::cout << "Sum: " << sum << '\n';*/

	Matrix<int, 2> mi{ 2, 3 };
	std::cout << "Please enter six integers:\n";
	for (Index i = 0; i < mi.dim1(); ++i)
		for (Index j = 0; j < mi.dim2(); ++j) {
			int val = 0;
			while (!(std::cin >> val)) {
				std::cerr << "Please enter exactly six integers.\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			mi(i, j) = val;
		}

	std::cout << mi;
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}