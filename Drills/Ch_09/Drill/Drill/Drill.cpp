#include "../../../../std_lib_facilities.h"

//struct Date { int y, m, d; };
//
//void init_day(Date&, int, int, int);
//void add_day(Date&, int);
//ostream& operator<<(ostream&, const Date&);
//
//int main() {
//	try {
//		Date today;
//		init_day(today, 1978, 6, 25);
//		Date tomorrow = today;
//		add_day(tomorrow, 1);
//		cout << "Today: " << today << "Tomorrow: " << tomorrow << '\n';
//	}
//	catch (exception & e) {
//		cerr << "Error: " << e.what() << ".\n";
//	}
//}
//
//void init_day(Date& date, int y, int m, int d) {
//	if (y < 0 || m < 1 || m > 12 || d < 1 || d > 31)
//		error("invalid date");
//	date.y = y;
//	date.m = m;
//	date.d = d;
//}
//
//void add_day(Date& date, int n) {
//	for (int i = 0; i < n; ++i) {
//		if (date.d == 31) {
//			date.d = 1;
//			if (date.m == 12) {
//				date.m = 1;
//				date.y += 1;
//			}
//			else
//				date.m += 1;
//		}
//		else
//			date.d += 1;
//	}
//}
//
//ostream& operator<<(ostream& os, const Date& date) {
//	return os << date.m << '/' << date.d << '/' << date.y << '\n';
//}

///

//struct Date {
//	int y, m, d;
//	Date(int, int, int);
//	void add_day(int);
//};
//
//ostream& operator<<(ostream&, const Date&);
//
//int main() {
//	try {
//		Date today{ 1978, 6, 25 };
//		Date tomorrow{ today };
//		tomorrow.add_day(1);
//		cout << "Today: " << today << "Tomorrow: " << tomorrow << '\n';
//	}
//	catch (exception & e) {
//		cerr << "Error: " << e.what() << ".\n";
//	}
//}
//
//Date::Date(int y, int m, int d) :
//	y(y), m(m), d(d) {
//	if (y < 0 || m < 1 || m > 12 || d < 1 || d > 31)
//		error("invalid date");
//}
//
//void Date::add_day(int n) {
//	for (int i = 0; i < n; ++i) {
//		if (d == 31) {
//			d = 1;
//			if (m == 12) {
//				m = 1;
//				y += 1;
//			}
//			else
//				m += 1;
//		}
//		else
//			d += 1;
//	}
//}
//
//ostream& operator<<(ostream & os, const Date & date) {
//	return os << date.m << '/' << date.d << '/' << date.y << '\n';
//}

///

//class Date {
//	int y, m, d;
//public:
//	Date(int, int, int);
//	void add_day(int);
//	int year() const { return y; }
//	int month() const { return m; }
//	int day() const { return d; }
//};
//
//ostream& operator<<(ostream&, const Date&);
//
//int main() {
//	try {
//		Date today{ 1978, 6, 25 };
//		Date tomorrow{ today };
//		tomorrow.add_day(1);
//		cout << "Today: " << today << "Tomorrow: " << tomorrow << '\n';
//	}
//	catch (exception & e) {
//		cerr << "Error: " << e.what() << ".\n";
//	}
//}
//
//Date::Date(int y, int m, int d) :
//	y(y), m(m), d(d) {
//	if (y < 0 || m < 1 || m > 12 || d < 1 || d > 31)
//		error("invalid date");
//}
//
//void Date::add_day(int n) {
//	for (int i = 0; i < n; ++i) {
//		if (d == 31) {
//			d = 1;
//			if (m == 12) {
//				m = 1;
//				y += 1;
//			}
//			else
//				m += 1;
//		}
//		else
//			d += 1;
//	}
//}
//
//ostream& operator<<(ostream & os, const Date & date) {
//	return os << date.month() << '/' << date.day() << '/' << date.year() << '\n';
//}

///

//enum class Month {
//	jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
//};
//
//class Date {
//public:
//	class Invalid {};
//	Date(int, Month, int);
//	void add_day(int);
//	int year() const { return y; }
//	Month month() const { return m; }
//	int day() const { return d; }
//private:
//	int y, d;
//	Month m;
//	bool is_valid() { return y >= 0 && d >= 1 && d <= 31; };
//};
//
//ostream& operator<<(ostream&, const Date&);
//
//int main() {
//	try {
//		Date today{ 1978, Month::jun, 25 };
//		Date tomorrow{ today };
//		tomorrow.add_day(1);
//		cout << "Today: " << today << "Tomorrow: " << tomorrow << '\n';
//	}
//	catch (Date::Invalid) {
//		cerr << "Error: invalid date.\n";
//	}
//}
//
//Date::Date(int y, Month m, int d) :
//	y(y), m(m), d(d) {
//	if (!is_valid()) throw Invalid{};
//}
//
//void Date::add_day(int n) {
//	for (int i = 0; i < n; ++i) {
//		if (d == 31) {
//			d = 1;
//			if (m == Month::dec) {
//				m = Month::jan;
//				y += 1;
//			}
//			else
//				m = Month(int(m) + 1);
//		}
//		else
//			d += 1;
//	}
//}
//
//ostream& operator<<(ostream & os, const Date & date) {
//	return os << int(date.month()) << '/' << date.day() << '/' << date.year() << '\n';
//}

///

enum class Month {
	jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

class Date {
public:
	class Invalid {};
	Date();
	Date(int, Month, int);
	void add_day(int);
	int year() const { return y; }
	Month month() const { return m; }
	int day() const { return d; }
private:
	int y, d;
	Month m;
	bool is_valid() { return y >= 0 && d >= 1 && d <= 31; };
};

const Date& default_date();

ostream& operator<<(ostream&, const Date&);

int main() {
	try {
		Date today{ 1978, Month::jun, 25 };
		Date tomorrow{ today };
		tomorrow.add_day(1);
		cout << "Today: " << today << "Tomorrow: " << tomorrow << '\n';
	}
	catch (Date::Invalid) {
		cerr << "Error: invalid date.\n";
	}
}

Date::Date() : 
	y(default_date().year()), m(default_date().month()), d(default_date().day()) {}

Date::Date(int y, Month m, int d) :
	y(y), m(m), d(d) {
	if (!is_valid()) throw Invalid{};
}

void Date::add_day(int n) {
	for (int i = 0; i < n; ++i) {
		if (d == 31) {
			d = 1;
			if (m == Month::dec) {
				m = Month::jan;
				y += 1;
			}
			else
				m = Month(int(m) + 1);
		}
		else
			d += 1;
	}
}

const Date& default_date() {
	static Date date{ 2001, Month::jan, 1 };
	return date;
}

ostream& operator<<(ostream & os, const Date & date) {
	return os << int(date.month()) << '/' << date.day() << '/' << date.year() << '\n';
}