#include <iostream>

class A1 {
protected:
	A1();
};

class A2 {
public:
	virtual void f() = 0;
};

int main()
try {
	A1 a1;
	A2 a2;
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}