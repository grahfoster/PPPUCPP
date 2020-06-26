#include "../../../../MatrixIO.h"
#include <iostream>
#include <random>
#include <chrono>

using Numeric_lib::Index;

using Matrix = Numeric_lib::Matrix<double, 2>;
using Vector = Numeric_lib::Matrix<double, 1>;

struct Elim_failure {
	Index i;
};

struct Back_subst_failure {
	Index i;
};

Matrix random_matrix(Index n) {
	Matrix m{ n, n };
	std::default_random_engine ran{ unsigned(std::chrono::system_clock::now().time_since_epoch().count()) };
	std::uniform_real_distribution<> ureal{ 0, double(n) };

	for (Index i = 0; i < n; ++i)
		for (Index j = 0; j < n; ++j)
			m(i, j) = ureal(ran);
	return m;
}

Vector random_vector(Index n) {
	Vector v{ n };
	std::default_random_engine ran{ unsigned(std::chrono::system_clock::now().time_since_epoch().count()) };
	std::uniform_real_distribution<> ureal{ 0, double(n) };

	for (Index i = 0; i < n; ++i)
		v(i) = ureal(ran);
	return v;
}

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

			// more variables and deeper loops mean messy code
			for (Index m = 0; m < A[i].slice(j).size(); ++m)
				A[i].slice(j)(m) = A[j].slice(j)(m) * -mult + A[i].slice(j)(m);

			b(i) -= mult * b(j);
		}
	}
}

Vector back_substitution(const Matrix& A, const Vector& b)
{
	const Index n = A.dim1();
	Vector x{ n };

	for (Index i = n - 1; i >= 0; --i) {
		// more variables and deeper loops mean messy code
		double diff = 0;
		for (Index o = 0; o < A[i].slice(i + 1).size(); ++o)
			diff += A[i].slice(i + 1)(o) * x.slice(i + 1)(o);

		double s = b(i) - diff;

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

	for (Index i = 0; i < n; ++i) {
		// more variables and deeper loops mean messy code
		double sum = 0;
		for (Index o = 0; o < m[i].size(); ++o)
			sum += m[i](o) * u(o);
		v(i) = sum;
	}
	return v;
}

int main()
try {
	const Index n = 10;

	Matrix A = random_matrix(n);
	Vector b = random_vector(n);

	std::cout << "A:\n" << A << '\n';
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