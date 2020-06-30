#include "../../../../MatrixIO.h"
#include <iostream>
#include <sstream>

using namespace Numeric_lib;

Matrix<double> operator*(const Matrix<double, 2>& md1, const Matrix<double>& md2)
{
	const Index n = md1.dim1();
	Matrix<double> md3{ n };
	for (Index i = 0; i < n; ++i)
		md3(i) = dot_product(md1[i], md2);
	return md3;
}

Matrix<double> operator+(const Matrix<double>& md1, const Matrix<double>& md2)
{
	if (md1.size() != md2.size())
		throw std::exception("matrices have different dimensions");

	Matrix<double> md3{ md1 };
	for (Index i = 0; i < md1.dim1(); ++i)
		md3(i) += md2(i);

	return md3;
}

Matrix<double, 2> operator+(const Matrix<double, 2>& md1, const Matrix<double, 2>& md2)
{
	if (md1.size() != md2.size())
		throw std::exception("matrices have different dimensions");

	Matrix<double, 2> md3{ md1 };
	for (Index i = 0; i < md1.dim1(); ++i)
		for (Index j = 0; j < md1.dim2(); ++j)
			md3(i, j) += md2(i, j);

	return md3;
}

Matrix<double, 3> operator+(const Matrix<double, 3>& md1, const Matrix<double, 3>& md2)
{
	if (md1.size() != md2.size())
		throw std::exception("matrices have different dimensions");

	Matrix<double, 3> md3{ md1 };
	for (Index i = 0; i < md1.dim1(); ++i)
		for (Index j = 0; j < md1.dim2(); ++j)
			for (Index k = 0; k < md1.dim3(); ++k)
			md3(i, j, k) += md2(i, j, k);

	return md3;
}

int main()
try {
	Matrix<double, 2> md1{ 2, 2 };
	std::istringstream iss{ " { { 1 2 } { 3 4 } }" };
	iss >> md1;

	Matrix<double> md2{ 2 };
	iss.str("{ 5 6 }");
	iss >> md2;

	Matrix<double> md3{ md1 * md2 };
	std::cout << "md3:\n" << md3 << '\n';

	Matrix<double, 2> md4{ 2, 2 };
	iss.str("{ { 5 6 } { 7 8 } }");
	iss >> md4;

	Matrix<double, 2> md5{ md1 + md4 };
	std::cout << "md5:\n" << md5 << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}