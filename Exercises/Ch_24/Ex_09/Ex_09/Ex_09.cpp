#include "../../../../MatrixIO.h"
#include <iostream>

using namespace Numeric_lib;

template<class F, class T>
auto my_apply(F f, const Matrix<T>& mu)
{
	using R = decltype(f(mu[0]));
	Matrix<R> mr(mu.size());
	for (Index i = 0; i < mu.size(); ++i)
		mr(i) = f(mu(i));
	return mr;
}

template<class F, class T, class U>
auto my_apply(F f,  const Matrix<T>& mu, U u)
{
	using R = decltype(f(mu[0], u));
	Matrix<R> mr(mu.size());
	for (Index i = 0; i < mu.size(); ++i)
		mr(i) = f(mu(i), u);
	return mr;
}

double halve(double d)
{
	return d / 2.0;
}

float divide(double d, float f)
{
	return d / f;
}

int main()
try {
	Matrix<int> mi1{ 10 };
	for (int i = 0; i < mi1.size(); ++i)
		mi1(i) = i + 1;
	std::cout << "mi1:\n" << mi1 << '\n';

	Matrix<double> mi2{ my_apply(halve, mi1) };
	std::cout << "mi2:\n" << mi2 << '\n';

	Matrix<float> mi3{ my_apply(divide, mi2, 10) };
	std::cout << "mi3:\n" << mi3 << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}