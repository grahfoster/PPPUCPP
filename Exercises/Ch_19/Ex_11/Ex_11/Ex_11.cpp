#include <iostream>
#include <vector>

template<class T>
class Counted_ptr {
public:
	Counted_ptr(const T& def) : ptr{ new T{ def } }, use_count{ new int{ 1} } {}
	Counted_ptr(const Counted_ptr&);
	~Counted_ptr();

	Counted_ptr& operator=(const Counted_ptr&);
	T* operator->() { return ptr; }
	T& operator*() { return *ptr; }

	int get_use_count() const { return *use_count; }

	T* release();
private:
	T* ptr;
	int* use_count;
};

template<class T>
Counted_ptr<T>::Counted_ptr(const Counted_ptr& cp) :
	ptr{ cp.ptr }, use_count{ cp.use_count }
{
	++* use_count;
}

template<class T>
Counted_ptr<T>::~Counted_ptr()
{
	if (*use_count == 1) {
		delete ptr;
		delete use_count;
	}
	else
		--* use_count;
}

template<class T>
Counted_ptr<T>& Counted_ptr<T>::operator=(const Counted_ptr& cp)
{
	ptr = cp.ptr;
	use_count = cp.use_count;
	++* use_count;
}

template<class T>
T* Counted_ptr<T>::release()
{
	T* temp = ptr;
	ptr = nullptr;
	return temp;
}

struct A { int a = 0; };

template<class T>
T* f(const T& def) {
	Counted_ptr<T> cp{ def };
	return cp.release();
}

int main()
try {
	Counted_ptr<int> up1{ 1 };
	*up1 = 1;
	std::cout << *up1 << '\n'
		<< up1.get_use_count() << "\n\n";

	Counted_ptr<A> up2{ A{} };
	up2->a = 2;
	std::cout << up2->a << '\n'
		<< up2.get_use_count() << "\n\n";

	*up1 = 3;
	Counted_ptr<int> up3{ up1 };
	std::cout << *up3 << '\n'
		<< up1.get_use_count() << "\n\n";

	up3.~Counted_ptr();
	std::cout << *up1 << '\n'
		<< up1.get_use_count() << "\n\n";

	A* a{ f(A{ 4 }) };
	std::cout << a->a << "\n\n";

	std::vector<Counted_ptr<int>> cps;
	cps.push_back(Counted_ptr<int>{ 5 });
	cps.push_back(Counted_ptr<int>{ 6 });
	cps.push_back(Counted_ptr<int>{ 7 });
	cps.push_back(Counted_ptr<int>{ cps.front() });
	for (Counted_ptr<int> cp : cps)
		std::cout << *cp << ' ';
	std::cout << '\n'
		<< cps.front().get_use_count() << "\n\n";

	cps.resize(1, 1);
	std::cout << *cps.front() << '\n'
		<< cps.front().get_use_count() << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}