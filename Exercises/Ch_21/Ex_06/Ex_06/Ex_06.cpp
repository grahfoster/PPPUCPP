#include <iostream>
#include <string>
#include <set>

struct Fruit {
	std::string name;
	int count;
	double unit_price;
};

struct Fruit_comparison {
	bool operator()(Fruit* fp1, Fruit* fp2) const { return fp1->name < fp2->name; }
};

int main()
try {
	std::set<Fruit*, Fruit_comparison> sf;
	sf.insert(new Fruit{ "Quince", 5 });
	sf.insert(new Fruit{ "Apple", 200, .37 });
	sf.insert(new Fruit{ "Orange", 33, .45 });

	for (auto fp : sf)
		std::cout << fp->name << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}