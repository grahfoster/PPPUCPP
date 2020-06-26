#include "../../../../MatrixIO.h"
#include <iostream>

using namespace Numeric_lib;

template<class Scalar>
struct Triple_ref {
	void operator()(Scalar& s) { s *= 3; }
};

template<class Scalar>
struct Triple_const {
	Scalar operator()(const Scalar& s) { return 3 * s; }
};

template<class Scalar>
struct Triple {
	Scalar operator()(Scalar& s) { return s *= 3; }
};

int main()
try {
	Matrix<int> mi1{ 5 };
	for (Index i = 0; i < mi1.size(); ++i)
		mi1(i) = i + 1;

	mi1.apply(Triple_ref<int>());
	std::cout << "mi1:\n" << mi1 << '\n';

	Matrix<int> mi2 = apply(Triple_const<int>(), mi1);
	std::cout << "mi2:\n" << mi2 << '\n';

	mi1.apply(Triple<int>());
	std::cout << "mi1:\n" << mi1 << '\n';

	Matrix<int> mi3 = apply(Triple<int>(), mi1);
	std::cout << "mi3:\n" << mi3 << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}