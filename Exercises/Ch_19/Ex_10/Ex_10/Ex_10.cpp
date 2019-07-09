#include <iostream>

template<class T>
class Unique_ptr {
public:
	Unique_ptr(T* p) : ptr{ p } {}
	~Unique_ptr() { delete ptr; }

	T* operator->() { return ptr; }
	T& operator*() { return *ptr; }

	T* release();
private:
	T* ptr;
};

template<class T>
T* Unique_ptr<T>::release()
{
	T* temp = ptr;
	ptr = nullptr;
	return temp;
}

struct A { int a = 0; };

int main()
try {
	Unique_ptr<int> up1{ new int };
	*up1 = 1;
	std::cout << *up1 << '\n';

	Unique_ptr<A> up2{ new A };
	up2->a = 2;
	std::cout << up2->a << '\n';

	*up1 = 3;
	Unique_ptr<int> up3{ up1.release() };
	std::cout << *up3 << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}