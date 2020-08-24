#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include <algorithm>

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

template <unsigned int N>
class Stack
{
public:
	Stack() : data(new unsigned char[N]), end(data + N), top(data), index(0), block_size(new unsigned int[N]) {}
	~Stack() { delete[] data; }

	unsigned int available() const { return end - top; };

	void* get(unsigned int);
	void free();
private:
	unsigned char* data;
	unsigned char* end;
	unsigned char* top;
	unsigned int index;
	unsigned int* block_size;

	bool is_full() const { return !(top < end); }
	bool is_empty() const { return top == data && index == 0; }

	void update(unsigned int, bool);
};

template<unsigned int N>
void* Stack<N>::get(unsigned int n)
{
	if (is_full() || top + n > end)
		throw std::exception("Stack overflow");
	void* ret = (void*)top;
	update(n, true);
	return ret;
}

template<unsigned int N>
void Stack<N>::free()
{
	if (is_empty())
		throw std::exception("Stack underflow");
	update(0, false);
}

template<unsigned int N>
void Stack<N>::update(unsigned int n, bool allocate)
{
	if (allocate) {
		top += n;
		block_size[index] = n;
		++index;
	}
	else {
		--index;
		n = block_size[index];
		top -= n;
	}
}

int main()
try {
	srand(time(NULL));

	constexpr int num_objs = 10000;
	constexpr int max_size = 1000;
	constexpr int num_trials = 3;

	for (int i = 0; i < num_trials; ++i) {
		std::vector<char*> vcp;
		auto start = std::chrono::system_clock::now();
		for (int i = 0; i < num_objs; ++i)
			vcp.push_back(new char[rand() % (max_size - 1) + 1]);
		for (int i = num_objs - 1; i >= 0; --i)
			delete vcp[i];
		auto end = std::chrono::system_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "Heap allocation, reverse deallocation took " << duration.count() << " milliseconds.\n";
	}

	std::cout << '\n';

	for (int i = 0; i < num_trials; ++i) {
		std::vector<char*> vcp;
		std::vector<int> vri(num_objs);
		std::iota(vri.begin(), vri.end(), 0);
		std::random_shuffle(vri.begin(), vri.end());
		auto start = std::chrono::system_clock::now();
		for (int i = 0; i < num_objs; ++i)
			vcp.push_back(new char[rand() % (max_size - 1) + 1]);
		for (int i = 0; i < num_objs; ++i)
			delete vcp[vri[i]];
		auto end = std::chrono::system_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "Heap allocation, random deallocation " << duration.count() << " milliseconds.\n";
	}

	std::cout << '\n';

	for (int i = 0; i < num_trials; ++i) {
		Pool<char[500], num_objs> pcp;
		std::vector<char(*)[500]> vca;
		auto start = std::chrono::system_clock::now();
		for (int i = 0; i < num_objs; ++i)
			vca.push_back(pcp.get());
		for (int i = num_objs - 1; i >= 0; --i)
			pcp.free(vca[i]);
		auto end = std::chrono::system_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "Pool allocation, reverse deallocation took " << duration.count() << " milliseconds.\n";
	}

	std::cout << '\n';

	for (int i = 0; i < num_trials; ++i) {
		Pool<char[500], num_objs> pcp;
		std::vector<char(*)[500]> vca;
		std::vector<int> vri(num_objs);
		std::iota(vri.begin(), vri.end(), 0);
		std::random_shuffle(vri.begin(), vri.end());
		auto start = std::chrono::system_clock::now();
		for (int i = 0; i < num_objs; ++i)
			vca.push_back(pcp.get());
		for (int i = 0; i < num_objs; ++i)
			pcp.free(vca[vri[i]]);
		auto end = std::chrono::system_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "Pool allocation, random deallocation took " << duration.count() << " milliseconds.\n";
	}

	std::cout << '\n';

	for (int i = 0; i < num_trials; ++i) {
		Stack<num_objs* max_size> stack;
		std::vector<void*> vvp;
		auto start = std::chrono::system_clock::now();
		for (int i = 0; i < num_objs; ++i)
			vvp.push_back(stack.get(rand() % (max_size - 1) + 1));
		for (int i = 0; i < num_objs; ++i)
			stack.free();
		auto end = std::chrono::system_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "Stack allocation, reverse deallocation took " << duration.count() << " milliseconds.\n";
	}
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}