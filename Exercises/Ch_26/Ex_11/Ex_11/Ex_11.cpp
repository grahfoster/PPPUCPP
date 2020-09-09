#include "../../../../Matrix.h"
#include <iostream>
#include <random>
#include <chrono>
#include <vector>

using namespace Numeric_lib;

void fill_matrix(Matrix<double, 2>& m)
{
	std::default_random_engine ran{ unsigned(std::chrono::system_clock::now().time_since_epoch().count()) };
	std::uniform_real_distribution<> ureal{ -10, 10 };

	for (int i = 0; i < m.dim1(); ++i) {
		for (int j = 0; j < m.dim2(); ++j) {
			m(i, j) = ureal(ran);
		}
	}
}

double row_sum(Matrix<double, 2> m, int n)
{
	if (n >= m.dim1() || n < 0)
		throw std::exception("invalid row number");
	double s = 0;
	for (int i = 0; i < m[n].size(); ++i)
		s += m(n, i);
	return s;
}

int main()
try {
	srand(time(NULL));

	Matrix<double, 2> m1{ 10, 10 };
	Matrix<double, 2> m2{ 50, 50 };
	Matrix<double, 2> m3{ 250, 250 };
	Matrix<double, 2> m4{ 1000, 1000 };
	fill_matrix(m1);
	fill_matrix(m2);
	fill_matrix(m3);
	fill_matrix(m4);

	auto start = std::chrono::system_clock::now();
	std::vector<double> v1;
	for (int i = 0; i < m1.dim1(); ++i) {
		if (i == 0)
			v1.push_back(row_sum(m1, i));
		else
			v1.push_back(row_sum(m1, i) + v1.back());
	}
	auto end = std::chrono::system_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Accumulated vector for matrix of size " << m1.dim1() << " by " << m1.dim2() <<
		" took " << duration.count() << " milliseconds to calculate.\n";

	start = std::chrono::system_clock::now();
	std::vector<double> v2;
	for (int i = 0; i < m2.dim1(); ++i) {
		if (i == 0)
			v2.push_back(row_sum(m2, i));
		else
			v2.push_back(row_sum(m2, i) + v2.back());
	}
	end = std::chrono::system_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Accumulated vector for matrix of size " << m2.dim1() << " by " << m2.dim2() <<
		" took " << duration.count() << " milliseconds to calculate.\n";

	start = std::chrono::system_clock::now();
	std::vector<double> v3;
	for (int i = 0; i < m3.dim1(); ++i) {
		if (i == 0)
			v3.push_back(row_sum(m3, i));
		else
			v3.push_back(row_sum(m3, i) + v3.back());
	}
	end = std::chrono::system_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Accumulated vector for matrix of size " << m3.dim1() << " by " << m3.dim2() <<
		" took " << duration.count() << " milliseconds to calculate.\n";

	start = std::chrono::system_clock::now();
	std::vector<double> v4;
	for (int i = 0; i < m4.dim1(); ++i) {
		if (i == 0)
			v4.push_back(row_sum(m4, i));
		else
			v4.push_back(row_sum(m4, i) + v4.back());
	}
	end = std::chrono::system_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Accumulated vector for matrix of size " << m4.dim1() << " by " << m4.dim2() <<
		" took " << duration.count() << " milliseconds to calculate.\n";
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}