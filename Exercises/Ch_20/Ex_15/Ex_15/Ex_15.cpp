#include <iostream>

struct range_exception : std::exception { using std::exception::exception; };

template<class Elem, class A = std::allocator<Elem*>>
class Pvector {
public:
	Pvector() {}
	explicit Pvector(int sz) { resize(sz); }
	Pvector(const Pvector&);
	Pvector(Pvector&&);
	~Pvector();

	const Elem*& operator[](int n) const { return elems[n]; }

	Pvector& operator=(const Pvector&);
	Pvector& operator=(Pvector&&);
	Elem*& operator[](int n) { return elems[n]; }

	const Elem*& at(int) const;
	int size() const { return sz; }
	int capacity() const { return space; }

	Elem*& at(int);
	void resize(int, Elem = Elem{});
	void reserve(int);
	void push_back(const Elem&);
private:
	Elem** elems = nullptr;
	A alloc;
	int sz = 0;
	int space = 0;
};

template<class Elem, class A>
Pvector<Elem, A>::Pvector(const Pvector& v)
{
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
}

template<class Elem, class A>
Pvector<Elem, A>::Pvector(Pvector&& v)
{
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
}

template<class Elem, class A>
Pvector<Elem, A>::~Pvector()
{
	for (int i = 0; i < sz; ++i)
		delete elems[i];
	delete[] elems;
}

template<class Elem, class A>
Pvector<Elem, A>& Pvector<Elem, A>::operator=(const Pvector& v)
{
	if (this == &v)
		return *this;
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
	return *this;
}

template<class Elem, class A>
Pvector<Elem, A>& Pvector<Elem, A>::operator=(Pvector&& v)
{
	if (this == &v)
		return *this;
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
	return *this;
}

template<class Elem, class A>
const Elem*& Pvector<Elem, A>::at(int i) const
{
	if (i < 0 || i < sz)
		throw range_exception("out of range access");
	return elems[i];
}

template<class Elem, class A>
Elem*& Pvector<Elem, A>::at(int i)
{
	if (i < 0 || i < sz)
		throw range_exception("out of range access");
	return elems[i];
}

template<class Elem, class A>
void Pvector<Elem, A>::resize(int new_size, Elem def)
{
	reserve(new_size);
	for (int i = sz; i < new_size; ++i)
		alloc.construct(&elems[i], new Elem{ def });
	for (int i = new_size; i < sz; ++i) {
		delete elems[i];
		alloc.destroy(&elems[i]);
	}
	sz = new_size;
}

template<class Elem, class A>
void Pvector<Elem, A>::reserve(int new_alloc)
{
	if (new_alloc < space)
		return;
	Elem** temp = alloc.allocate(new_alloc);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&temp[i], elems[i]);
	delete[] elems;
	elems = temp;
	space = new_alloc;
}

template<class Elem, class A>
void Pvector<Elem, A>::push_back(const Elem& elem)
{
	if (space == 0)
		reserve(1);
	else if (space == sz)
		reserve(2 * space);
	alloc.construct(&elems[sz], new Elem{ elem });
	++sz;
}

int main()
try {
	Pvector<int> pvi;
	pvi.push_back(1);
	pvi.push_back(2);
	pvi.push_back(3);
	pvi.push_back(4);
	pvi.push_back(5);

	std::cout << "Pvector contents: ";
	for (int i = 0; i < pvi.size(); ++i)
		std::cout << *pvi[i] << ' ';
	std::cout << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}