#include <vector>
#include <list>
#include <iostream>

class Iterator {
public:
	virtual double* next() = 0;
};

class Vector_iterator : public Iterator {
public:
	Vector_iterator(const std::vector<double>& v) : vect{ v } {}

	double* next() override;
private:
	std::vector<double> vect;
	int i = 0;
};

double* Vector_iterator::next()
{
	if (i == vect.size())
		return 0;
	return &vect[i++];
}

class List_iterator : public Iterator {
public:
	List_iterator(const std::list<double>& l) : lst{ l } {}

	double* next() override;
private:
	std::list<double> lst;
	int i = 0;
};

double* List_iterator::next()
{
	if (i == lst.size())
		return 0;
	return &*std::next(lst.begin(), i++);
}

void print(Iterator& iter)
{
	double* dp = iter.next();
	while (dp) {
		std::cout << *dp << '\n';
		dp = iter.next();
	}
}

int main()
try {
	std::vector<double> vect{ 1, 2, 4.5, 6.44, 3.0 / 2, 5.999 };
	Vector_iterator vi{ vect };
	std::cout << "Vector iterator:\n";
	print(vi);

	std::list<double> lst{ 1, 2, 4.5, 6.44, 3.0 / 2, 5.999 };
	List_iterator li{ lst };
	std::cout << "List iterator:\n";
	print(li);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}