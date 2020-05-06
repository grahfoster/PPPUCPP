#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <list>
#include <iterator>

struct Purchase {
	std::string name;
	double unit_price;
	int count;
};

std::string get_string(std::istream& is, const char div)
{
	std::string s;
	char c;
	is >> c;
	if (!is)
		return s;
	while (!is.eof() && c != div) {
		s += c;
		is.get(c);
	}
	return s;
}

std::istream& operator>>(std::istream& is, Purchase& purchase)
{
	constexpr char div = '|';

	// format: Name|Unit Price|Count
	char c;
	std::string pn;
	double up;
	int ct;

	pn = get_string(is, div);
	is >> up;
	is.get(c);
	if (c != div)
		throw std::exception("bad input format");
	is >> ct;

	if (!is && !is.eof())
		throw std::exception("bad input format");

	purchase = Purchase{ pn, up, ct };
	return is;
}

std::ostream& operator<<(std::ostream& os, const Purchase& purchase)
{
	os << purchase.name << " @ " << purchase.unit_price << " X " << purchase.count;
	return os;
}

struct Order {
	std::string name;
	std::string address;
	std::string data;
	std::vector<Purchase> purchases;
};

std::istream& operator>>(std::istream& is, Order& order)
{
	constexpr char div = '|';
	constexpr char obrack = '{';
	constexpr char cbrack = '}';

	// format: Name|Address|Data|{Purchase}{Purchase}|
	std::string nm;
	std::string ad;
	std::string dt;
	std::vector<Purchase> vp;

	nm = get_string(is, div);
	ad = get_string(is, div);
	dt = get_string(is, div);

	if (!is && !is.eof())
		throw std::exception("bad input format");
	if (is.eof())
		return is;

	char c = is.get();
	while (c != div) {
		Purchase ps;

		if (c != obrack)
			throw std::exception("bad input format");
		is >> ps;
		is.get(c);
		if (c != cbrack)
			throw std::exception("bad input format");
		is.get(c);

		vp.push_back(ps);
	}

	order = Order{ nm, ad, dt, vp };
	return is;
}

std::ostream& operator<<(std::ostream& os, const Order& order)
{
	os << "Order:\n"
		<< "\tName: " << order.name << '\n'
		<< "\tAddress: " << order.address << '\n'
		<< "\tData: " << order.data << '\n'
		<< "\tPurchases:\n";
	for (Purchase purchase : order.purchases)
		os << "\t\t" << purchase << '\n';
	return os;
}

template<class Iter>
void print_orders(Iter first, Iter last, std::ostream& os)
{
	while (first != last)
		os << *first++;
}

int main()
try {
	std::ifstream ifs1{ "Ex_09_input1.txt" };
	if (!ifs1)
		throw std::exception("input file not found");
	ifs1.exceptions(ifs1.exceptions() | std::ios_base::badbit);

	std::ofstream ofs{ "Ex_09_output1.txt" };
	if (!ofs)
		throw std::exception("output file not found");

	std::vector<Order> orders1;
	for (Order order; ifs1 >> order;)
		orders1.push_back(order);

	std::sort(orders1.begin(), orders1.end(),
		[](const Order& order1, const Order& order2) -> bool { return order1.name < order2.name; });

	print_orders(orders1.begin(), orders1.end(), ofs);

	std::ifstream ifs2{ "Ex_09_input2.txt" };
	if (!ifs2)
		throw std::exception("input file not found");
	ifs2.exceptions(ifs2.exceptions() | std::ios_base::badbit);

	ofs.close();
	ofs.open("Ex_09_output2.txt");
	if (!ofs)
		throw std::exception("output file not found");

	std::list<Order> orders2;
	for (Order order; ifs2 >> order;)
		orders2.push_back(order);

	orders2.sort([](const Order& order1, const Order& order2) -> bool {
		return order1.address < order2.address;
		});

	print_orders(orders2.begin(), orders2.end(), ofs);

	ofs.close();
	ofs.open("Ex_09_output3.txt");
	if (!ofs)
		throw std::exception("output file not found");

	ifs1.clear();
	ifs1.seekg(0, std::ios::beg);
	ifs2.clear();
	ifs2.seekg(0, std::ios::beg);

	std::istream_iterator<Order> isi1{ ifs1 };
	std::istream_iterator<Order> isi2{ ifs2 };
	std::istream_iterator<Order> eof;
	std::ostream_iterator<Order> osi{ ofs };

	std::merge(isi1, eof, isi2, eof, osi,
		[](const Order& order1, const Order& order2) -> bool { return order1.name < order2.name; });
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}