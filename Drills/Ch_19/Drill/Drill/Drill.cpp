#include <iostream>
#include <vector>

template<class T>
struct S {
	S(const T& v = T{}) : val{ v } {};

	const T& get() const;

	T& get();
	T& operator=(const T&);
private:
	T val;
};

template <class T>
const T& S<T>::get() const { return val; }

template <class T>
T& S<T>::get() { return val; }

template <class T>
T& S<T>::operator=(const T& v) { val = v; }

template <class T>
std::istream& operator>>(std::istream& is, std::vector<T>& vs)
{
	vs.clear();
	for (T v; is >> v;) {
		vs.push_back(v);
		if (is.get() != ',')
			return is;
	}
	return is;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vs)
{
	for (int i = 0; i < vs.size(); ++i) {
		os << vs[i];
		if (i < vs.size() - 1)
			os << ", ";
	}
	return os;
}

template<class T>
void read_val(T& v) {
	while (true) {
		std::cin >> v;
		if (std::cin.eof()) {
			std::cin.clear();
			return;
		}
		if (!std::cin) {
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << "Invalid input. Try again.\n";
			continue;
		}
		break;
	}
}

int main()
try {
	S<int> si;
	S<char> sc{ 'a' };
	S<double> sd{ 1.1 };
	S<std::string> ss{ "string" };
	S<std::vector<int>> svi{ std::vector<int>{ 1, 2, 3} };

	std::cout << si.get() << '\n'
		<< sc.get() << '\n'
		<< sd.get() << '\n'
		<< ss.get() << '\n';
	for (int i : svi.get())
		std::cout << i << ' ';
	std::cout << "\n\n";

	read_val(si.get());
	read_val(sc.get());
	read_val(sd.get());
	read_val(ss.get());
	read_val(svi.get());
	std::cout << '\n';

	std::cout << si.get() << '\n'
		<< sc.get() << '\n'
		<< sd.get() << '\n'
		<< ss.get() << '\n'
		<< svi.get() << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}