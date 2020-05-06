#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <numeric>
#include <iomanip>

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

struct Order {
	std::string name;
	std::string address;
	std::string data;
	std::vector<Purchase> purchases;
};

struct Add_fct {
	double operator()(double d, const Order& order)
	{
		double temp = 0;
		for (Purchase purchase : order.purchases)
			temp += purchase.unit_price * purchase.count;
		return d + temp;
	}
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

int main()
try {
	std::ifstream ifs1{ "Ex_10_input1.txt" };
	if (!ifs1)
		throw std::exception("input file not found");
	ifs1.exceptions(ifs1.exceptions() | std::ios_base::badbit);

	std::vector<Order> orders;
	for (Order order; ifs1 >> order;)
		orders.push_back(order);

	std::ifstream ifs2{ "Ex_10_input2.txt" };
	if (!ifs2)
		throw std::exception("input file not found");
	ifs2.exceptions(ifs2.exceptions() | std::ios_base::badbit);

	for (Order order; ifs2 >> order;)
		orders.push_back(order);

	double total = 0;
	total = std::accumulate(orders.begin(), orders.end(), total, Add_fct());
	std::cout << "Total price of all purchases in all orders: $"
		<< std::fixed << std::setprecision(2) << total << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}