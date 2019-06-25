#include <iostream>
#include <vector>

const int size = 10;

//int ga[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };

std::vector<int> gv{ 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };

//void f(int ia[], int n)
//{
//	int la[size];
//
//	std::copy(ga, &ga[size], la);
//
//	for (int i : la)
//		std::cout << i << ' ';
//	std::cout << '\n';
//
//	int* p = new int[n];
//
//	std::copy(ia, &ia[n], p);
//
//	for (int i = 0; i < n; ++i)
//		std::cout << p[i] << ' ';
//	std::cout << '\n';
//
//	delete[] p;
//}

void f(std::vector<int> v)
{
	std::vector<int> lv(v.size());
	
	lv = gv;

	for (int i : lv)
		std::cout << i << ' ';
	std::cout << '\n';

	std::vector<int> lv2{ v };

	for (int i : lv2)
		std::cout << i << ' ';
	std::cout << '\n';
}

int fact(int n) { 
	if (n < 0)
		throw std::exception("fact() - argument must be positive");
	return !n ? 1 : n * fact(n - 1); 
}

int main()
try {
	//f(ga, size);
	//
	//int aa[size];
	//for (int i = 0; i < size; ++i)
	//	aa[i] = fact(i + 1);
	//
	//f(aa, size);

	f(gv);

	std::vector<int> vv;
	for (int i = 0; i < size; ++i)
		vv.push_back(fact(i + 1));

	f(vv);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}