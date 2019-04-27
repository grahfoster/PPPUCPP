#include "Punct_stream.h"

int main()
try {
	Punct_stream ps{ std::cin };
	for (std::string s; ps >> s; std::cout << s << '\n');
}
catch (std::exception & e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}