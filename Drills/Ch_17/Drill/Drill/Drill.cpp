#include <iostream>
#include <vector>

//void print_array10(std::ostream& os, int* a)
//{
//	for (int i = 0; i < 10; ++i)
//		os << a[i] << '\n';
//}

void print_array(std::ostream& os, int* a, int n)
{
	for (int i = 0; i < n; ++i)
		os << a[i] << ' ';
	os << '\n';
}

//void print_vector(std::ostream& os, const std::vector<int>& nums)
//{
//	for (int num : nums)
//		os << num << '\n';
//}

int main()
try {
	/*int* nums1 = new int[10];
	for (int i = 0; i < 10; ++i)
		std::cout << nums1[i] << '\n';
	delete[] nums1;

	int* nums2 = new int[10]{
		100, 101, 102, 103, 104, 105, 106, 107, 108, 109
	};
	print_array10(std::cout, nums2);
	delete[] nums2;

	int* nums3 = new int[11]{
		100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110
	};
	print_array10(std::cout, nums3);
	std::cout << nums3[10] << '\n';
	delete[] nums3;

	int* nums4 = new int[20]{
		100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
		110, 111, 112, 113, 114, 115, 116, 117, 118, 119
	};
	print_array(std::cout, nums4, 20);
	delete[] nums4;

	std::vector<int> v_nums1{
		100, 101, 102, 103, 104, 105, 106, 107, 108, 109
	};
	print_vector(std::cout, v_nums1);

	std::vector<int> v_nums2{
		100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110
	};
	print_vector(std::cout, v_nums2);

	std::vector<int> v_nums3{
		100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
		110, 111, 112, 113, 114, 115, 116, 117, 118, 119
	};
	print_vector(std::cout, v_nums3);*/

	int* p1 = new int{ 7 };
	std::cout << "p1: " << p1 << ", *p1: ";
	print_array(std::cout, p1, 1);

	int* p2 = new int[7]{ 1, 2, 4, 8, 16, 32, 64 };
	std::cout << "p2: " << p2 << ", *p2: ";
	print_array(std::cout, p2, 7);

	int* p3 = p2;
	p2 = p1;
	p2 = p3;

	std::cout << "p1: " << p1 << ", *p1: ";
	print_array(std::cout, p1, 1);
	std::cout << "p2: " << p2 << ", *p2: ";
	print_array(std::cout, p2, 7);

	delete p1;
	delete[] p2;

	p1 = new int[10]{
		1, 2, 4, 8, 16, 32, 64, 128, 256, 512
	};
	p2 = new int[10];
	for (int i = 0; i < 10; ++i)
		p2[i] = p1[i];

	delete[] p1;
	delete[] p2;

	std::vector<int> v1{
		1, 2, 4, 8, 16, 32, 64, 128, 256, 512
	};
	std::vector<int> v2(10);
	for (int i = 0; i < 10; ++i)
		v2[i] = v1[i];
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}