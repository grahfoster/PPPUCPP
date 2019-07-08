#include <iostream>

struct range_exception : std::exception { using std::exception::exception; };

template<class T, class A = std::allocator<T>>
class Vector {
public:
	Vector() {}
	explicit Vector(int sz) { resize(sz); }
	Vector(const Vector&);
	Vector(Vector&&);
	~Vector() { delete[] elems; }

	const T& operator[](int n) const { return elems[n]; }

	Vector& operator=(const Vector&);
	Vector& operator=(Vector&&);
	T& operator[](int n) { return elems[n]; }

	const T& at(int) const;
	int size() const { return sz; }
	int capacity() const { return space; }

	T& at(int);
	void resize(int, T = T{});
	void reserve(int);
	void push_back(const T&);
private:
	T* elems = nullptr;
	A alloc;
	int sz = 0;
	int space = 0;
};

template<class T, class A>
Vector<T, A>::Vector(const Vector& v)
{
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
}

template<class T, class A>
Vector<T, A>::Vector(Vector&& v)
{
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
}

template<class T, class A>
Vector<T, A>& Vector<T, A>::operator=(const Vector& v)
{
	if (this == &v)
		return *this;
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
	return *this;
}

template<class T, class A>
Vector<T, A>& Vector<T, A>::operator=(Vector&& v)
{
	if (this == &v)
		return *this;
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
	return *this;
}

template<class T, class A>
const T& Vector<T, A>::at(int i) const
{
	if (i < 0 || i < sz)
		throw range_exception("out of range access");
	return elems[i];
}

template<class T, class A>
T& Vector<T, A>::at(int i)
{
	if (i < 0 || i < sz)
		throw range_exception("out of range access");
	return elems[i];
}

template<class T, class A>
void Vector<T, A>::resize(int new_size, T def)
{
	reserve(new_size);
	for (int i = sz; i < new_size; ++i)
		alloc.construct(&elems[i], def);
	for (int i = new_size; i < sz; ++i)
		alloc.destroy(&elems[i]);
	sz = new_size;
}

template<class T, class A>
void Vector<T, A>::reserve(int new_alloc)
{
	if (new_alloc < space)
		return;
	T* temp = alloc.allocate(new_alloc);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&temp[i], elems[i]);
	delete[] elems;
	elems = temp;
	space = new_alloc;
}

template<class T, class A>
void Vector<T, A>::push_back(const T& elem)
{
	if (space == 0)
		reserve(1);
	else if (space == sz)
		reserve(2 * space);
	alloc.construct(&elems[sz], elem);
	++sz;
}

int main()
try {
	Vector<int> vi1(10);
	vi1.push_back(1);

	std::cout << "vi1:\n";
	for (int i = 0; i < vi1.size(); ++i)
		std::cout << vi1[i] << ' ';
	std::cout << "\nSize: " << vi1.size() <<
		"\nSpace: " << vi1.capacity() << '\n';

	Vector<int> vi2;
	vi2.push_back(2);
	vi2.push_back(3);

	std::cout << "\nvi2:\n";
	for (int i = 0; i < vi2.size(); ++i)
		std::cout << vi2[i] << ' ';
	std::cout << "\nSize: " << vi2.size() <<
		"\nSpace: " << vi2.capacity() << '\n';

	vi1 = vi2;

	std::cout << "\nvi1:\n";
	for (int i = 0; i < vi1.size(); ++i)
		std::cout << vi1[i] << ' ';
	std::cout << "\nSize: " << vi1.size() <<
		"\nSpace: " << vi1.capacity() << '\n';

	Vector<int> vi3{ vi1 };

	std::cout << "\nvi3:\n";
	for (int i = 0; i < vi3.size(); ++i)
		std::cout << vi3[i] << ' ';
	std::cout << "\nSize: " << vi3.size() <<
		"\nSpace: " << vi3.capacity() << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}