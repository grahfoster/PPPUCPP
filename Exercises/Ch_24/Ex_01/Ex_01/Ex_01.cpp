#include "../../../../MatrixIO.h"
#include <iostream>

using namespace Numeric_lib;

template<class Scalar>
void triple_ref(Scalar& s)
{
	s *= 3;
}

template<class Scalar>
Scalar triple_const(const Scalar& s)
{
	return 3 * s;
}

template<class Scalar>
Scalar triple(Scalar& s)
{
	return s *= 3;
}

int main()
try {
	Matrix<int> mi1{ 5 };
	for (Index i = 0; i < mi1.size(); ++i)
		mi1(i) = i + 1;

	mi1.apply(triple_ref<int>);
	std::cout << "mi1:\n" << mi1 << '\n';
	
	Matrix<int> mi2 = apply(triple_const<int>, mi1);
	std::cout << "mi2:\n" << mi2 << '\n';

	mi1.apply(triple<int>);
	std::cout << "mi1:\n" << mi1 << '\n';

	Matrix<int> mi3 = apply(triple<int>, mi1);
	std::cout << "mi3:\n" << mi3 << '\n';	
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}