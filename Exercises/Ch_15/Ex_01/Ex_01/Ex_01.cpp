#include <iostream>

int fac(int n) { return n > 1 ? n * fac(n - 1) : 1; }

int fac2(int n)
{
	int r = 1;
	while (n > 1)
		r *= n--;
	return r;
}

int main()
try {
	for (int i = 0; i <= 20; ++i)
		std::cout << "Recursive factorial of " << i << ": " << fac(i) <<
		"\nIterative factorial of " << i << ": " << fac2(i) << "\n\n";
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}