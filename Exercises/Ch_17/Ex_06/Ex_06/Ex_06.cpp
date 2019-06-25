#include <iostream>

int bytes_allocated = 0;

int main()
try {
	while (true) {
		bool* b = new bool[1000];
		bytes_allocated += 1000;
	}
}
catch (std::bad_alloc& e) {
	std::cerr << "Bytes allocated before memory exhaustion: " << bytes_allocated << ".\n";
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}