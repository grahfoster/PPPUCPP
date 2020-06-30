#include "../../../../MatrixIO.h"
#include <iostream>
#include <sstream>

using namespace Numeric_lib;

template<class T>
void swap_columns(Matrix<T, 2>& mt, Index col1, Index col2)
{
	for (Index row = 0; row < mt.dim1(); ++row)
		std::swap(mt(row, col1), mt(row, col2));
}

int main()
try {
	Matrix<double, 2> md{ 2, 2 };
	std::istringstream iss{ " { { 1 2 } { 3 4 } }" };
	iss >> md;

	std::cout << "\nmd:\n" << md << '\n';
	swap_columns(md, 0, 1);
	std::cout << "md:\n" << md << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}