#include <iostream>

template <class T, unsigned int N>
class Pool {
public:
	Pool() { create_pool(sizeof(T), N); };
	~Pool() { delete[] data; };

	unsigned int available() const { return num_free_blocks; }

	T* get();
	void free(T*);
private:
	unsigned int num_blocks;
	unsigned int block_size;
	unsigned int num_free_blocks;
	unsigned int num_init_blocks;
	unsigned char* data;
	unsigned char* next;

	unsigned char* addr_from_index(unsigned int i) const { return data + (i * block_size); }
	unsigned int index_from_addr(const unsigned char* ptr) const { return (((unsigned int)(ptr - data)) / block_size); }

	void create_pool(unsigned int, unsigned int);
};

template <class T, unsigned int N>
T* Pool<T, N>::get()
{
	if (num_init_blocks < num_blocks) {
		unsigned int* p = (unsigned int*)addr_from_index(num_init_blocks);
		*p = num_init_blocks + 1;
		++num_init_blocks;
	}

	void* ret = nullptr;

	if (num_free_blocks > 0) {
		ret = (void*)next;
		--num_free_blocks;

		if (num_free_blocks != 0)
			next = addr_from_index(*((unsigned int*)next));
		else
			next = nullptr;
	}

	return reinterpret_cast<T*>(ret);
}

template <class T, unsigned int N>
void Pool<T, N>::free(T* ptr2)
{
	void* ptr = (void*)ptr2;

	if (next != nullptr) {
		*(unsigned int*)ptr = index_from_addr(next);
		next = (unsigned char*)ptr;
	}
	else {
		*(unsigned int*)ptr = num_blocks;
		next = (unsigned char*)ptr;
	}

	++num_free_blocks;
}

template <class T, unsigned int N>
void Pool<T, N>::create_pool(unsigned int blocks_size, unsigned int blocks_number)
{
	num_blocks = blocks_number;
	block_size = blocks_size;
	num_free_blocks = blocks_number;
	num_init_blocks = 0;

	data = new unsigned char[block_size * num_blocks];
	next = data;
}

template <class T, int N>
class Pool_allocator {
public:
	Pool_allocator() {}
	~Pool_allocator() {}

	T* allocate() { return pool.get(); }
	void deallocate(T* ptr) { pool.free(ptr); }
	void construct(T* ptr, const T& v) { new(ptr) T{ v }; }
	void destroy(T* ptr) { ptr->~T(); }
private:
	Pool<T, N> pool;
};

struct Range_exception : std::exception { using std::exception::exception; };
struct Size_exception : std::exception { using std::exception::exception; };

template<class T, unsigned int N, class A = Pool_allocator<T, N>>
class Vector {
public:
	Vector() {}
	explicit Vector(int sz) { resize(sz); }
	Vector(const Vector&);
	Vector(Vector&&);

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

template<class T, unsigned int N, class A>
Vector<T, N, A>::Vector(const Vector& v)
{
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
}

template<class T, unsigned int N, class A>
Vector<T, N, A>::Vector(Vector&& v)
{
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
}

template<class T, unsigned int N, class A>
Vector<T, N, A>& Vector<T, N, A>::operator=(const Vector& v)
{
	if (this == &v)
		return *this;
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
	return *this;
}

template<class T, unsigned int N, class A>
Vector<T, N, A>& Vector<T, N, A>::operator=(Vector&& v)
{
	if (this == &v)
		return *this;
	resize(v.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elems[i], v[i]);
	return *this;
}

template<class T, unsigned int N, class A>
const T& Vector<T, N, A>::at(int i) const
{
	if (i < 0 || i < sz)
		throw Range_exception{ "out of range access" };
	return elems[i];
}

template<class T, unsigned int N, class A>
T& Vector<T, N, A>::at(int i)
{
	if (i < 0 || i < sz)
		throw Range_exception{ "out of range access" };
	return elems[i];
}

template<class T, unsigned int N, class A>
void Vector<T, N, A>::resize(int new_size, T def)
{
	reserve(new_size);
	for (int i = sz; i < new_size; ++i)
		alloc.construct(&elems[i], def);
	sz = new_size;
}

template<class T, unsigned int N, class A>
void Vector<T, N, A>::reserve(int new_alloc)
{
	if (new_alloc >= N)
		throw Size_exception{ "vector size limit reached" };
	if (new_alloc < space)
		return;
	T* temp = alloc.allocate();
	for (int i = 0; i < sz; ++i)
		alloc.construct(&temp[i], elems[i]);
	for (int i = 0; i < sz; ++i) {
		alloc.destroy(&elems[i]);
		alloc.deallocate(&elems[i]);
	}
	elems = temp;
	space = new_alloc;
}

template<class T, unsigned int N, class A>
void Vector<T, N, A>::push_back(const T& elem)
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
	Vector<int, 1000> vi(999);
	vi.push_back(1);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}