#include <iostream>

struct range_exception : std::exception { using std::exception::exception; };

template<class Elem, class A = std::allocator<Elem>>
class Vector {
public:
	class V_iterator;

	Vector() {}
	explicit Vector(int sz) { resize(sz); }
	Vector(const Vector&);
	Vector(Vector&&);
	~Vector() { delete[] elems; }

	const Elem*& operator[](int n) const { return elems[n]; }

	Vector& operator=(const Vector&);
	Vector& operator=(Vector&&);
	Elem& operator[](int n) { return elems[n]; }

	const Elem& at(int) const;
	int size() const { return sz; }
	int capacity() const { return space; }

	V_iterator begin() { return V_iterator{ &elems[0], &elems[0], &elems[sz - 1] }; }
	V_iterator end() { return V_iterator{ &elems[sz], &elems[0], &elems[sz - 1] }; }
	Elem& at(int);
	void resize(int, Elem = Elem{});
	void reserve(int);
	void push_back(const Elem&);
private:
	Elem* elems = nullptr;
	A alloc;
	int sz = 0;
	int space = 0;
};

template<class Elem, class A>
class Vector<Elem, A>::V_iterator {
public:
	V_iterator(Elem* elp, Elem* first_el, Elem* last_el) : ep{ elp }, first{ first_el }, last{ last_el } {};

	Elem& operator*();
	V_iterator& operator++();
	V_iterator& operator+=(int n);
	V_iterator& operator--();
	V_iterator& operator-=(int n);
	bool operator==(V_iterator other) { return ep == other.ep; };
	bool operator!=(V_iterator other) { return !(*this == other); }
private:
	Elem* ep;
	Elem* first;
	Elem* last;
};

template<class Elem, class A>
Elem& Vector<Elem, A>::V_iterator::operator*()
{
	if (ep < first || ep > last)
		throw range_exception("out of range access");
	return *ep;
}

template<class Elem, class A>
typename Vector<Elem, A>::V_iterator& Vector<Elem, A>::V_iterator::operator++()
{
	++ep;
	return *this;
}

template<class Elem, class A>
typename Vector<Elem, A>::V_iterator& Vector<Elem, A>::V_iterator::operator+=(int n)
{
	ep += n;
	return *this;
}

template<class Elem, class A>
typename Vector<Elem, A>::V_iterator& Vector<Elem, A>::V_iterator::operator--()
{
	--ep;
	return *this;
}

template<class Elem, class A>
typename Vector<Elem, A>::V_iterator& Vector<Elem, A>::V_iterator::operator-=(int n)
{
	ep -= n;
	return *this;
}

template<class Elem, class A>
Vector<Elem, A>::Vector(const Vector& v)
{
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
}

template<class Elem, class A>
Vector<Elem, A>::Vector(Vector&& v)
{
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
}

template<class Elem, class A>
Vector<Elem, A>& Vector<Elem, A>::operator=(const Vector& v)
{
	if (this == &v)
		return *this;
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
	return *this;
}

template<class Elem, class A>
Vector<Elem, A>& Vector<Elem, A>::operator=(Vector&& v)
{
	if (this == &v)
		return *this;
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
	return *this;
}

template<class Elem, class A>
const Elem& Vector<Elem, A>::at(int i) const
{
	if (i < 0 || i < sz)
		throw range_exception("out of range access");
	return *elems[i];
}

template<class Elem, class A>
Elem& Vector<Elem, A>::at(int i)
{
	if (i < 0 || i < sz)
		throw range_exception("out of range access");
	return *elems[i];
}

template<class Elem, class A>
void Vector<Elem, A>::resize(int new_size, Elem def)
{
	reserve(new_size);
	for (int i = sz; i < new_size; ++i)
		alloc.construct(&elems[i], new Elem{ def });
	for (int i = new_size; i < sz; ++i)
		alloc.destroy(&elems[i]);
	sz = new_size;
}

template<class Elem, class A>
void Vector<Elem, A>::reserve(int new_alloc)
{
	if (new_alloc < space)
		return;
	Elem* temp = alloc.allocate(new_alloc);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&temp[i], elems[i]);
	delete[] elems;
	elems = temp;
	space = new_alloc;
}

template<class Elem, class A>
void Vector<Elem, A>::push_back(const Elem& elem)
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
	Vector<int> vi;
	vi.push_back(1);
	vi.push_back(2);
	vi.push_back(3);
	vi.push_back(4);
	vi.push_back(5);

	std::cout << *vi.end();
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}