#include "../../../../MatrixIO.h"
#include <iostream>

using namespace Numeric_lib;

template <class F, class T>
Matrix<T> my_apply(F f, Matrix<T>& mt)
{
	for (Index i = 0; i < mt.size(); ++i)
		mt(i) = f(mt(i));
	return mt;
}

template<class Scalar>
Scalar triple(Scalar& s)
{
	return s *= 3;
}

template<class Scalar>
struct Triple {
	Scalar operator()(Scalar& s) { return s *= 3; }
};

int main()
try {
	Matrix<int> mi1{ 5 };
	for (Index i = 0; i < mi1.size(); ++i)
		mi1(i) = i + 1;

	Matrix<int> mi2 = my_apply(triple<int>, mi1);
	std::cout << "mi1:\n" << mi1 << '\n';
	std::cout << "mi2:\n" << mi2 << '\n';

	Matrix<int> mi3 = my_apply(Triple<int>(), mi1);
	std::cout << "mi1:\n" << mi1 << '\n';
	std::cout << "mi3:\n" << mi3 << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}