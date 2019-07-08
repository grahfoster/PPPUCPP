#include <iostream>

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
Number<T> operator*(const Number<T>& i1, const Number<U>& i2) { return Number<T>{ i1.val * T(i2.val) }; }

template<class T, class U>
Number<T> operator/(const Number<T>& i1, const Number<U>& i2) { return Number<T>{ i1.val / T(i2.val) }; }

template<class T, class U>
Number<T> operator%(const Number<T>& i1, const Number<U>& i2) { return Number<T>{ i1.val % T(i2.val) }; }

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

template<class T>
Number<T> f() { return Number<T>{ 2 }; }

int main()
try {
	Number<int> num1;
	Number<double> num2{ 1.1 };
	Number<int> num3{ f<int>() };
	Number<int> num4 = 3;

	std::cout << "num1: " << num1 << "\nnum2: " << num2 << "\nnum3: " << num3 << "\nnum4: " << num4 <<
		"\nnum1 + num2: " << num1 + num2 << "\nnum2 - num1: " << num2 - num1 <<
		"\nnum2 * num3: " << num2 * num3 << "\nnum3 / num2: " << num3 / num2 << 
		"\nnum4 % num2: " << num4 % num2 << 
		//"\nnum2 % num4: " << num2 % num4 << 
		'\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}