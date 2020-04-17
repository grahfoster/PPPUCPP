#include <iostream>

struct range_exception : std::exception { using std::exception::exception; };

template<class Elem, class A = std::allocator<Elem*>>
class Ownership_vector {
public:
	Ownership_vector() {}
	explicit Ownership_vector(int sz) { resize(sz); }
	Ownership_vector(const Ownership_vector&);
	Ownership_vector(Ownership_vector&&);
	~Ownership_vector();

	const Elem*& operator[](int n) const { return elems[n]; }

	Ownership_vector& operator=(const Ownership_vector&);
	Ownership_vector& operator=(Ownership_vector&&);
	Elem*& operator[](int n) { return elems[n]; }

	const Elem*& at(int) const;
	int size() const { return sz; }
	int capacity() const { return space; }

	Elem*& at(int);
	void resize(int, Elem = Elem{});
	void reserve(int);
	void push_back(const Elem&);
	void push_back(Elem*);
protected:
	Elem** elems = nullptr;
	A alloc;
	int sz = 0;
	int space = 0;
};

template<class Elem, class A>
Ownership_vector<Elem, A>::Ownership_vector(const Ownership_vector& v)
{
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
}

template<class Elem, class A>
Ownership_vector<Elem, A>::Ownership_vector(Ownership_vector&& v)
{
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
}

template<class Elem, class A>
Ownership_vector<Elem, A>::~Ownership_vector()
{
	for (int i = 0; i < sz; ++i)
		delete elems[i];
	delete[] elems;
}

template<class Elem, class A>
Ownership_vector<Elem, A>& Ownership_vector<Elem, A>::operator=(const Ownership_vector& v)
{
	if (this == &v)
		return *this;
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
	return *this;
}

template<class Elem, class A>
Ownership_vector<Elem, A>& Ownership_vector<Elem, A>::operator=(Ownership_vector&& v)
{
	if (this == &v)
		return *this;
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
	return *this;
}

template<class Elem, class A>
const Elem*& Ownership_vector<Elem, A>::at(int i) const
{
	if (i < 0 || i < sz)
		throw range_exception("out of range access");
	return elems[i];
}

template<class Elem, class A>
Elem*& Ownership_vector<Elem, A>::at(int i)
{
	if (i < 0 || i < sz)
		throw range_exception("out of range access");
	return elems[i];
}

template<class Elem, class A>
void Ownership_vector<Elem, A>::resize(int new_size, Elem def)
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
void Ownership_vector<Elem, A>::reserve(int new_alloc)
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
void Ownership_vector<Elem, A>::push_back(const Elem& elem)
{
	if (space == 0)
		reserve(1);
	else if (space == sz)
		reserve(2 * space);
	alloc.construct(&elems[sz], new Elem{ elem });
	++sz;
}

template<class Elem, class A>
void Ownership_vector<Elem, A>::push_back(Elem* pelem)
{
	if (space == 0)
		reserve(1);
	else if (space == sz)
		reserve(2 * space);
	alloc.construct(&elems[sz], pelem);
	++sz;
}

int main()
try {
	Ownership_vector<int> o_vi;

	int i1 = 1;
	int i2 = 2;
	int i3 = 3;
	int i4 = 4;
	int* pi = new int{ 5 };

	o_vi.push_back(i1);
	o_vi.push_back(i2);
	o_vi.push_back(i3);
	o_vi.push_back(i4);
	o_vi.push_back(pi);

	std::cout << "Ownership_vector contents: ";
	for (int i = 0; i < o_vi.size(); ++i)
		std::cout << *o_vi[i] << ' ';
	std::cout << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}