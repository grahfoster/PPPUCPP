#include "../../../../MatrixIO.h"
#include <iostream>
#include <sstream>

using Numeric_lib::Index;

using Matrix = Numeric_lib::Matrix<double, 2>;
using Vector = Numeric_lib::Matrix<double, 1>;

struct Elim_failure {
	Index i;
};

struct Back_subst_failure {
	Index i;
};

void elim_with_partial_pivot(Matrix& A, Vector& b)
{
	const Index n = A.dim1();

	for (Index j = 0; j < n; ++j) {
		Index pivot_row = j;

		for (Index k = j + 1; k < n; ++k)
			if (abs(A(k, j)) > abs(A(pivot_row, j)))
				pivot_row = k;

		if (pivot_row != j) {
			A.swap_rows(j, pivot_row);
			std::swap(b(j), b(pivot_row));
		}

		for (Index i = j + 1; i < n; ++i) {
			const double pivot = A(j, j);
			if (!pivot)
				throw std::exception{ "can't solve: pivot == 0" };
			const double mult = A(i, j) / pivot;
			A[i].slice(j) = Numeric_lib::scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
			b(i) -= mult * b(j);
		}
	}
}

Vector back_substitution(const Matrix& A, const Vector& b)
{
	const Index n = A.dim1();
	Vector x{ n };

	for (Index i = n - 1; i >= 0; --i) {
		double s = b(i) - Numeric_lib::dot_product(A[i].slice(i + 1), x.slice(i + 1));

		if (double m = A(i, i))
			x(i) = s / m;
		else
			throw Back_subst_failure{ i };
	}

	return x;
}

Vector classical_gaussian_elimination(Matrix A, Vector b)
{
	elim_with_partial_pivot(A, b);
	return back_substitution(A, b);
}

Vector operator*(const Matrix& m, const Vector& u)
{
	const Index n = m.dim1();
	Vector v{ n };
	for (Index i = 0; i < n; ++i)
		v(i) = Numeric_lib::dot_product(m[i], u);
	return v;
}

int main()
try {
	std::istringstream iss{ "{ { 0 1 } { 1 0 } }" };
	Matrix A{ 2, 2 };
	iss >> A;
	std::cout << "A:\n" << A << '\n';

	iss.str("{ 5 6 }");
	Vector b{ 2 };
	iss >> b;
	std::cout << "b:\n" << b << '\n';

	Vector x = classical_gaussian_elimination(A, b);
	std::cout << "x:\n" << x << '\n';

	Vector v = A * x;
	std::cout << "v:\n" << v << '\n';
}
catch (Elim_failure& ef) {
	std::cerr << "Elimination failure at index " << ef.i << ".\n";
}
catch (Back_subst_failure& bsf) {
	std::cerr << "Back substitution failure at index " << bsf.i << ".\n";
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}