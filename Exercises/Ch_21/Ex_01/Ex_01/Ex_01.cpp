#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iterator>
#include <algorithm>

//template<class Iter, class T>
//Iter find1(Iter first, Iter last, const T& val)
//{
//	while (first != last && *first != val)
//		++first;
//	return first;
//}
//
//template<class Iter, class T>
//Iter find2(Iter first, Iter last, const T& val)
//{
//	for (Iter p = first; p != last; ++p)
//		if (*p == val)
//			return p;
//	return last;
//}

//struct Record {
//	double unit_price;
//	int units;
//};

int main()
try {
	/*std::vector<int> vi{ 1, 2, 3, 4, 5 };
	auto p1 = find1(vi.begin(), vi.end(), 3);
	auto p2 = find2(vi.begin(), vi.end(), 3);
	if (p1 != p2)
		std::cout << "Uh oh.\n";*/

		/*std::vector<Record> vr{ { 1.99, 23 }, { 99.99, 3 }, { 2.49, 15 }, { 10.99, 20 } };
		double total = std::accumulate(vr.begin(), vr.end(), 0.0,
			[](double d, Record& r) -> double { return d + r.units * r.unit_price; });
		std::cout << "Total price of all units: " << total << '\n';*/

		/*std::map<std::string, double> dow_price{
			{ "MMM", 81.86 }, { "AA", 34.69 }, { "MO", 54.45 },
			{ "AAPL", 292.06 }, { "UNH", 283.55 }, { "PFE", 37.60  }
		};

		std::map<std::string, double> dow_weight{
			{ "MMM", 5.8549 }, { "AA", 2.4808 }, { "MO", 3.8940 },
			{ "AAPL", 8.2746 }, { "UNH", 8.2372 }, { "PFE", 1.0804 }
		};

		std::map<std::string, std::string> dow_name{
			{ "MMM", "3M Co." }, { "AA", "Alcoa Inc." }, { "MO", "Altria Group Inc." },
			{ "AAPL", "Apple Inc." }, { "UNH", "UnitedHealth Group Inc." }, { "PFE", "Pfizer Inc." }
		};

		for (const auto& p : dow_price) {
			const std::string& symbol = p.first;
			std::cout << symbol << '\t' << p.second << '\t' << dow_name[symbol] << '\n';
		}*/

		/*std::unordered_map<std::string, int> umsi;*/

	std::string from, to;
	std::cin >> from >> to;

	std::ifstream ifs{ from };
	std::ofstream ofs{ to };

	std::istream_iterator<std::string> isi{ ifs };
	std::istream_iterator<std::string> eof;
	std::ostream_iterator<std::string> osi{ ofs, "\n" };

	/*std::vector<std::string> b{ isi, eof };*/
	std::vector<std::string> b(100);
	std::copy(isi, eof, b.begin());
	std::sort(b.begin(), b.end());
	std::copy(b.begin(), b.end(), osi);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}