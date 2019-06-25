#include <iostream>

int main()
try {
	int i1 = 1;
	int i2 = 2;
	int* i3 = new int{ 3 };
	int* i4 = new int{ 4 };

	std::cout << "Stack growth: " << &i1 << " -> " << &i2 << 
		(&i1 < &i2 ? " (upward)" : " (downward)") << '\n' <<
		"Heap growth: " << i3 << " -> " << i4 << 
		(i3 < i4 ? " (upward)" : " (downward)") << '\n';

}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}