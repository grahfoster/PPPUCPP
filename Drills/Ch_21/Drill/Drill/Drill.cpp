#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <algorithm>
#include <map>
#include <numeric>

//struct Item {
//	std::string name;
//	int iid;
//	double value;
//};
//
//std::istream& operator>>(std::istream& is, Item& item)
//{
//	constexpr char terminator = '|';
//
//	std::string n;
//	int i;
//	char t;
//	double v;
//
//	char c;
//	is >> c;
//	if (is.eof())
//		return is;
//	while (c != terminator) {
//		n += c;
//		is.get(c);
//	}
//	is >> i >> t >> v;
//	if (!is || t != terminator)
//		throw std::exception("bad input format");
//
//	item = Item{ n, i , v };
//	return is;
//}
//
//std::ostream& operator<<(std::ostream& os, const Item& item)
//{
//	os << item.name << " - "
//		<< item.iid << " - "
//		<< item.value;
//	return os;
//}
//
template<class Iter>
void print(Iter begin, Iter end)
{
	while (begin != end)
		std::cout << *begin++ << '\n';
	std::cout << '\n';
}
//
//template<class Iter>
//Iter find_by_name(Iter begin, Iter end, std::string name)
//{
//	while (begin != end) {
//		if (begin->name == name)
//			break;
//		++begin;
//	}
//	return begin;
//}
//
//template<class Iter>
//Iter find_by_iid(Iter begin, Iter end, int iid)
//{
//	while (begin != end) {
//		if (begin->iid == iid)
//			break;
//		++begin;
//	}
//	return begin;
//}

//template<class T, class U>
//void print(std::map<T, U> mtu)
//{
//	for (auto ptu : mtu)
//		std::cout << ptu.first << " - " << ptu.second << '\n';
//	std::cout << '\n';
//}
//
//void read_pairs(std::map<std::string, int>& msi)
//{
//	std::string s;
//	int i;
//	while (true) {
//		std::cin >> s >> i;
//		if (std::cin.eof())
//			break;
//		if (!std::cin)
//			throw std::exception("bad input format");
//		msi.insert({ s, i });
//	}
//}

class Less_than {
public:
	Less_than(double v) : val(v) {};

	bool operator()(double d) { return d < val; }
private:
	double val;
};

int main()
try {
	//std::ifstream ifs{ "Drill_input1.txt" };
	//ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);
	//if (!ifs)
	//	throw std::exception("couldn't find input file");

	////std::vector<Item> items;
	//std::list<Item> items;
	//for (Item item; ifs >> item; items.push_back(item));
	//print(items.begin(), items.end());

	////std::sort(items.begin(), items.end(),
	////	[](Item item1, Item item2) -> bool { return item1.name < item2.name; });
	//items.sort([](Item item1, Item item2) -> bool { return item1.name < item2.name; });
	//print(items.begin(), items.end());

	////std::sort(items.begin(), items.end(),
	////	[](Item item1, Item item2) -> bool { return item1.iid < item2.iid; });
	//items.sort([](Item item1, Item item2) -> bool { return item1.iid < item2.iid; });
	//print(items.begin(), items.end());

	////std::sort(items.begin(), items.end(), 
	////	[](Item item1, Item item2) -> bool { return item1.value > item2.value; });
	//items.sort([](Item item1, Item item2) -> bool { return item1.value > item2.value; });
	//print(items.begin(), items.end());

	//items.insert(items.begin(), Item{ "Horse shoe", 99, 12.34 });
	//items.insert(items.begin(), Item{ "Canon S400", 9988, 499.95 });
	//print(items.begin(), items.end());

	//auto p = find_by_name(items.begin(), items.end(), "Shampoo");
	//if (p == items.end())
	//	throw std::exception("item name not found");
	//items.erase(p);
	//p = find_by_name(items.begin(), items.end(), "Vinegar");
	//if (p == items.end())
	//	throw std::exception("item name not found");
	//items.erase(p);
	//print(items.begin(), items.end());

	//p = find_by_iid(items.begin(), items.end(), 12401);
	//if (p == items.end())
	//	throw std::exception("item id not found");
	//items.erase(p);
	//p = find_by_iid(items.begin(), items.end(), 29309);
	//if (p == items.end())
	//	throw std::exception("item id not found");
	//items.erase(p);
	//print(items.begin(), items.end());

	/*std::map<std::string, int> msi;

	msi["One"] = 1;
	msi["Two"] = 2;
	msi["Three"] = 3;
	msi["Four"] = 4;
	msi["Five"] = 5;
	msi["Six"] = 6;
	msi["Seven"] = 7;
	msi["Eight"] = 8;
	msi["Nine"] = 9;
	msi["Ten"] = 10;

	print(msi);

	msi.clear();

	read_pairs(msi);
	std::cout << '\n';

	print(msi);

	int sum = std::accumulate(msi.begin(), msi.end(), 0,
		[](int i, std::pair<std::string, int> psi) -> int { return i + psi.second; });
	std::cout << "Sum: " << sum << "\n\n";

	std::map<int, std::string> mis;

	for (auto psi : msi)
		mis.insert({ psi.second, psi.first });

	print(mis);*/

	std::vector<double> vd;
	std::ifstream ifs{ "Drill_input2.txt" };
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);
	if (!ifs)
		throw std::exception("couldn't find input file");

	for (double d; ifs >> d; vd.push_back(d));
	if (!ifs && !ifs.eof())
		throw std::exception("bad input format");

	print(vd.begin(), vd.end());

	std::vector<int> vi{ vd.begin(), vd.end() };

	for (int i = 0; i < vd.size(); ++i)
		std::cout << vd[i] << ", " << vi[i] << '\n';
	std::cout << '\n';

	double sum_vd = std::accumulate(vd.begin(), vd.end(), 0.0);
	std::cout << "Sum of elements of vd: " << sum_vd << '\n';
	std::cout << '\n';

	double sum_vi = std::accumulate(vi.begin(), vi.end(), 0);
	std::cout << "Difference between sums: " << sum_vd - sum_vi << '\n';
	std::cout << '\n';

	std::reverse(vd.begin(), vd.end());
	print(vd.begin(), vd.end());

	double mean_vd = sum_vd / vd.size();
	std::cout << "Mean value of elements of vd: " << mean_vd << '\n';
	std::cout << '\n';

	int size = std::count_if(vd.begin(), vd.end(), Less_than{ mean_vd });
	std::vector<double> vd2(size);
	std::copy_if(vd.begin(), vd.end(), vd2.begin(), Less_than{ mean_vd });

	std::sort(vd.begin(), vd.end());
	print(vd.begin(), vd.end());
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}