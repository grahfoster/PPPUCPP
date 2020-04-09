#include <iostream>
#include <vector>
#include <list>

//const std::vector<double>& get_from_jill();

//double* get_from_jack(const int* count)
//{
//	double* jack_data = new double[*count];
//	for (int i = 0; i < *count; ++i)
//		jack_data[i] = i;
//	return jack_data;
//}
//
//std::vector<double>* get_from_jill()
//{
//	std::vector<double>* jill_data = new std::vector<double>;
//	for (int i = 0; i < 10; ++i)
//		jill_data->push_back(i);
//	return jill_data;
//}

//template<class T>
//T* high(T* first, T* last)
//{
//	double* high = first;
//	for (; first != last; ++first)
//		if (*high < *first)
//			high = first;
//	return high;
//}

//void my_copy(int* b1, int* e1, int* b2)
//{
//	while (b1 != e1) {
//		*b2 = *b1;
//		++b1;
//		++b2;
//	}
//}

//template<class Iterator>
//Iterator high(Iterator first, Iterator last)
//{
//	Iterator high = first;
//	for (; first != last; ++first)
//		if (*high < *first)
//			high = first;
//	return high;
//}

//struct range_exception : std::exception { using std::exception::exception; };
//
//template<class T, class A = std::allocator<T>>
//class Vector {
//public:
//	Vector() {}
//	explicit Vector(int sz) { resize(sz); }
//	Vector(const Vector&);
//	Vector(Vector&&);
//	~Vector() { delete[] elems; }
//
//	const T& operator[](int n) const { return elems[n]; }
//
//	Vector& operator=(const Vector&);
//	Vector& operator=(Vector&&);
//	T& operator[](int n) { return elems[n]; }
//
//	const T& at(int) const;
//	int size() const { return sz; }
//	int capacity() const { return space; }
//
//	T& at(int);
//	void resize(int, T = T{});
//	void reserve(int);
//	void push_back(const T&);
//	void push_front(const T&);
//private:
//	T* elems = nullptr;
//	A alloc;
//	int sz = 0;
//	int space = 0;
//};
//
//template<class T, class A>
//Vector<T, A>::Vector(const Vector& v)
//{
//	resize(v.sz);
//	for (int i = 0; i < sz; ++i)
//		alloc.construct(&elems[i], v[i]);
//}
//
//template<class T, class A>
//Vector<T, A>::Vector(Vector&& v)
//{
//	resize(v.sz);
//	for (int i = 0; i < sz; ++i)
//		alloc.construct(&elems[i], v[i]);
//}
//
//template<class T, class A>
//Vector<T, A>& Vector<T, A>::operator=(const Vector& v)
//{
//	if (this == &v)
//		return *this;
//	resize(v.sz);
//	for (int i = 0; i < sz; ++i)
//		alloc.construct(&elems[i], v[i]);
//	return *this;
//}
//
//template<class T, class A>
//Vector<T, A>& Vector<T, A>::operator=(Vector&& v)
//{
//	if (this == &v)
//		return *this;
//	resize(v.sz);
//	for (int i = 0; i < sz; ++i)
//		alloc.construct(&elems[i], v[i]);
//	return *this;
//}
//
//template<class T, class A>
//const T& Vector<T, A>::at(int i) const
//{
//	if (i < 0 || i < sz)
//		throw range_exception("out of range access");
//	return elems[i];
//}
//
//template<class T, class A>
//T& Vector<T, A>::at(int i)
//{
//	if (i < 0 || i < sz)
//		throw range_exception("out of range access");
//	return elems[i];
//}
//
//template<class T, class A>
//void Vector<T, A>::resize(int new_size, T def)
//{
//	reserve(new_size);
//	for (int i = sz; i < new_size; ++i)
//		alloc.construct(&elems[i], def);
//	for (int i = new_size; i < sz; ++i)
//		alloc.destroy(&elems[i]);
//	sz = new_size;
//}
//
//template<class T, class A>
//void Vector<T, A>::reserve(int new_alloc)
//{
//	if (new_alloc < space)
//		return;
//	T* temp = alloc.allocate(new_alloc);
//	for (int i = 0; i < sz; ++i)
//		alloc.construct(&temp[i], elems[i]);
//	delete[] elems;
//	elems = temp;
//	space = new_alloc;
//}
//
//template<class T, class A>
//void Vector<T, A>::push_back(const T& elem)
//{
//	if (space == 0)
//		reserve(1);
//	else if (space == sz)
//		reserve(2 * space);
//	alloc.construct(&elems[sz], elem);
//	++sz;
//}
//
//template<class T, class A>
//void Vector<T, A>::push_front(const T& elem)
//{
//	if (space == 0)
//		reserve(1);
//	else if (space == sz)
//		reserve(2 * space);
//	alloc.construct(&elems[sz], elems[sz - 1]);
//	for (int i = sz; i > 0; --i)
//		elems[i] = elems[i - 1];
//	alloc.construct(elems, elem);
//	++sz;
//}

//template<class Iter>
//void advance(Iter& p, int n)
//{
//	if (n > 0)
//		while (n > 0) {
//			++p;
//			--n;
//		}
//	else
//		while (n < 0) {
//			--p;
//			++n;
//		}
//}

template<class Iter>
void print_info(Iter b, Iter e)
{
	Iter temp = b;
	int count = 0;
	while (temp != e) {
		++count;
		++temp;
	}
	std::cout << "Element count: " << count << '\n';

	/*std::string s{ "Hello" };
	bool same = std::equal(b, e, s.begin());
	std::cout << (same ? "Same" : "Different") << '\n';

	std::string s2{ "Howdy" };
	bool less = std::lexicographical_compare(b, e, s2.begin(), s2.end());
	std::cout << (less ? "Less" : "Greater") << " than\n";*/

	std::vector<int> v { 1, 2, 3, 4, 5 };
	bool same = std::equal(b, e, v.begin());
	std::cout << (same ? "Same" : "Different") << '\n';

	std::vector<int> v2 { 2, 3, 4, 5, 6 };
	bool less = std::lexicographical_compare(b, e, v2.begin(), v2.end());
	std::cout << (less ? "Less" : "Greater") << " than\n";

}

int main()
try {
	/*constexpr int jack_count = 0;
	double* jack_data = get_from_jack(&jack_count);
	std::vector<double>* jill_data = get_from_jill();
	std::vector<double>& v = *jill_data;*/

	/*double* jack_high = high(jack_data, &jack_data[jack_count]);
	double* jill_high = high(&v[0], &v[0] + v.size());

	if (jack_high == &jack_data[jack_count])
		std::cout << "Jack's data was empty.\n";
	else
		std::cout << "Jack's max: " << *jack_high << '\n';
	if (jill_high == &v[0] + v.size())
		std::cout << "Jill's data was empty.\n";
	else
		std::cout << "Jill's max: " << *jill_high << '\n';*/

	/*auto jack_high = high(jack_data, &jack_data[jack_count]);
	auto jill_high = high(v.begin(), v.end());

	if (jack_high == &jack_data[jack_count])
		std::cout << "Jack's data was empty.\n";
	else
		std::cout << "Jack's max: " << *jack_high << '\n';
	if (jill_high == v.end())
		std::cout << "Jill's data was empty.\n";
	else
		std::cout << "Jill's max: " << *jill_high << '\n';

	delete[] jack_data;
	delete jill_data;*/

	/*constexpr int length = 3;
	int ai1[length]{ 1, 2, 3 };
	int ai2[length]{ 4, 5, 6 };
	my_copy(ai1, &ai1[length], ai2);
	for (int i = 0; i < length; ++i)
		std::cout << ai2[i] << ' ';
	std::cout << '\n';*/

	/*Vector<int> vi;
	vi.push_back(1);
	vi.push_front(2);
	vi.push_back(3);
	for (int i = 0; i < vi.size(); ++i)
		std::cout << vi[i] << ' ';
	std::cout << '\n';*/

	/*int ai[5]{ 1, 2, 3, 4, 5 };
	int* p = ai;
	std::cout << *p << '\n';
	advance(p, 4);
	std::cout << *p << '\n';
	advance(p, -2);
	std::cout << *p << '\n';*/

	/*char ac[5]{ 'H', 'e', 'l', 'l', 'o' };
	std::vector<char> vc{ 'H', 'e', 'l', 'l', 'o' };
	std::list<char> lc{ 'H', 'e', 'l', 'l', 'o' };
	std::string sc{ "Hello" };

	print_info(ac, &ac[5]);
	print_info(vc.begin(), vc.end());
	print_info(lc.begin(), lc.end());
	print_info(sc.begin(), sc.end());

	char ac2[5];
	std::copy(ac, &ac[5], ac2);
	std::vector<char> vc2{ vc };
	std::list<char> lc2{ lc };
	std::string sc2{ sc };

	print_info(ac2, &ac2[5]);
	print_info(vc2.begin(), vc2.end());
	print_info(lc2.begin(), lc2.end());
	print_info(sc2.begin(), sc2.end());*/

	int ai[5]{ 1, 2, 3, 4, 5 };
	std::vector<int> vi{ 1, 2, 3, 4, 5 };
	std::list<int> li{ 1, 2, 3, 4, 5 };

	print_info(ai, &ai[5]);
	print_info(vi.begin(), vi.end());
	print_info(li.begin(), li.end());

	int ai2[5];
	std::copy(ai, &ai[5], ai2);
	std::vector<int> vi2{ vi };
	std::list<int> li2{ li };

	print_info(ai2, &ai2[5]);
	print_info(vi2.begin(), vi2.end());
	print_info(li2.begin(), li2.end());
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}