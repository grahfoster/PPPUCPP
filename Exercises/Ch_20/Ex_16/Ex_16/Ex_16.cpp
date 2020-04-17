#include <iostream>

struct range_exception : std::exception { using std::exception::exception; };

template<class Elem, class A = std::allocator<Elem*>>
class Ovector {
public:
	class Ov_iterator;

	Ovector() {}
	explicit Ovector(int sz) { resize(sz); }
	Ovector(const Ovector&);
	Ovector(Ovector&&);
	~Ovector();

	const Elem*& operator[](int n) const { return elems[n]; }

	Ovector& operator=(const Ovector&);
	Ovector& operator=(Ovector&&);
	Elem& operator[](int n) { return *elems[n]; }

	const Elem& at(int) const;
	int size() const { return sz; }
	int capacity() const { return space; }

	Ov_iterator begin() { return Ov_iterator{ &elems[0] }; }
	Ov_iterator end() { return Ov_iterator{ &elems[sz] }; }
	Elem& at(int);
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
class Ovector<Elem, A>::Ov_iterator {
public:
	Ov_iterator(Elem** elp) : ep{ elp } {};

	Elem& operator*() { return **ep; }
	Ov_iterator& operator++();
	Ov_iterator& operator+=(int n);
	Ov_iterator& operator--();
	Ov_iterator& operator-=(int n);
	bool operator==(Ov_iterator other) { return ep == other.ep; };
	bool operator!=(Ov_iterator other) { return !(*this == other); }
private:
	Elem** ep;
};

template<class Elem, class A>
typename Ovector<Elem, A>::Ov_iterator& Ovector<Elem, A>::Ov_iterator::operator++()
{
	++ep;
	return *this;
}

template<class Elem, class A>
typename Ovector<Elem, A>::Ov_iterator& Ovector<Elem, A>::Ov_iterator::operator+=(int n)
{
	ep += n;
	return *this;
}

template<class Elem, class A>
typename Ovector<Elem, A>::Ov_iterator& Ovector<Elem, A>::Ov_iterator::operator--()
{
	--ep;
	return *this;
}

template<class Elem, class A>
typename Ovector<Elem, A>::Ov_iterator& Ovector<Elem, A>::Ov_iterator::operator-=(int n)
{
	ep -= n;
	return *this;
}

template<class Elem, class A>
Ovector<Elem, A>::Ovector(const Ovector& v)
{
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
}

template<class Elem, class A>
Ovector<Elem, A>::Ovector(Ovector&& v)
{
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
}

template<class Elem, class A>
Ovector<Elem, A>::~Ovector()
{
	for (int i = 0; i < sz; ++i)
		delete elems[i];
	delete[] elems;
}

template<class Elem, class A>
Ovector<Elem, A>& Ovector<Elem, A>::operator=(const Ovector& v)
{
	if (this == &v)
		return *this;
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
	return *this;
}

template<class Elem, class A>
Ovector<Elem, A>& Ovector<Elem, A>::operator=(Ovector&& v)
{
	if (this == &v)
		return *this;
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
	return *this;
}

template<class Elem, class A>
const Elem& Ovector<Elem, A>::at(int i) const
{
	if (i < 0 || i < sz)
		throw range_exception("out of range access");
	return *elems[i];
}

template<class Elem, class A>
Elem& Ovector<Elem, A>::at(int i)
{
	if (i < 0 || i < sz)
		throw range_exception("out of range access");
	return *elems[i];
}

template<class Elem, class A>
void Ovector<Elem, A>::resize(int new_size, Elem def)
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
void Ovector<Elem, A>::reserve(int new_alloc)
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
void Ovector<Elem, A>::push_back(const Elem& elem)
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
	Ovector<int> ovi;
	ovi.push_back(1);
	ovi.push_back(2);
	ovi.push_back(3);
	ovi.push_back(4);
	ovi.push_back(5);

	std::cout << "Ovector contents: ";
	for (int i = 0; i < ovi.size(); ++i)
		std::cout << ovi[i] << ' ';
	std::cout << '\n';

	std::cout << "Ovector contents: ";
	for (int i : ovi)
		std::cout << i << ' ';
	std::cout << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}