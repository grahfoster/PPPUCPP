#include <iostream>
#include <vector>

template<class T>
struct Number {
	T val;

	Number(T v = T{}) : val{ v } {}
	Number(const Number& i) : val{ i.val } {}
	Number(Number&& i) : val{ i.val } {}

	Number& operator=(const Number&);
	Number& operator=(Number&&);
};

template<class T>
Number<T>& Number<T>::operator=(const Number<T>& i) {
	val = i.val;
	return *this;
}

template<class T>
Number<T>& Number<T>::operator=(Number<T>&& i) {
	val = i.val;
	return *this;
}

template<class T, class U>
Number<T> operator+(const Number<T>& i1, const Number<U>& i2) { return Number<T>{ i1.val + T(i2.val) }; }

template<class T, class U>
Number<T> operator-(const Number<T>& i1, const Number<U>& i2) { return Number<T>{ i1.val - T(i2.val) }; }

template<class T, class U>
Number<T> operator*(const Number<T>& i1, const Number<U>& i2) { return Number<T>{ i1.val* T(i2.val) }; }

template<class T, class U>
Number<T> operator/(const Number<T>& i1, const Number<U>& i2) { return Number<T>{ i1.val / T(i2.val) }; }

template<class T, class U>
Number<T> operator%(const Number<T>& i1, const Number<U>& i2) { return Number<T>{ i1.val% T(i2.val) }; }

template<class T>
std::istream& operator>>(std::istream& is, Number<T>& i) {
	is >> i.val;
	return is;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const Number<T>& i) {
	os << i.val;
	return os;
}

template<class T, class U>
T sum(const std::vector<T>& vt, const std::vector<U>& vu)
{
	T sum = T();
	for (int i = 0; i < vt.size() && i < vu.size(); ++i)
		sum = sum + vt[i] * vu[i];
	return sum;
}

int main()
try {
	std::vector<Number<int>> nums1{ 1, 2, 3, 4 };
	std::vector<Number<double>> nums2{ 1.1, 2.2, 3.3, 4.4 };

	std::cout << "Sum1: " << sum(nums1, nums2) << 
		"\nSum2: " << sum(nums2, nums1) << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}