#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <list>
int main()
try {
	srand(time(NULL));

	constexpr int num = 1000;
	std::vector<int> rand_ints;
	for (int i = 0; i < num; ++i)
		rand_ints.push_back(rand() % num);

	std::vector<int> vi;
	auto start1 = std::chrono::system_clock::now();
	for (int rand_int : rand_ints) {
		auto p = std::lower_bound(vi.begin(), vi.end(), rand_int);
		vi.insert(p, rand_int);
	}
	auto end1 = std::chrono::system_clock::now();

	std::list<int> li;
	auto start2 = std::chrono::system_clock::now();
	for (int rand_int : rand_ints) {
		auto p = std::lower_bound(li.begin(), li.end(), rand_int);
		li.insert(p, rand_int);
	}
	auto end2 = std::chrono::system_clock::now();

	auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
	auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
	std::cout << "Inserting " << num << " elements into a sorted vector took " << duration1.count() <<
		" millliseconds.\n";
	std::cout << "Inserting " << num << " elements into a sorted list took " << duration2.count() <<
		" millliseconds.\n";
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}