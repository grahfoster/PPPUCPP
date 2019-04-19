/*
	This file provides interfaces for classes and helper functions used in creating,
	accessing, and manipulating calendar dates.
*/

#include <iostream>

using std::ostream;
using std::istream;
using std::exception;

namespace Chrono {

/*----------Enum Classes----------*/

enum class Month {	// contains twelve months of the year
	jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};
enum class Day {	// contains seven days of the week
	sun, mon, tue, wed, thu, fri, sat
};

/*----------Date Class----------*/

class Date {	// represents calendar date
public:
	Date();
	Date(int, Month, int);

	int get_year() const {
		return year;
	}
	Month get_month() const {
		return month;
	}
	int get_day() const {
		return day;
	}

	void add_year(int);
	void add_month(int);
	void add_day(int);
private:
	int year;
	Month month;
	int day;

	bool is_valid();
};

/*----------Date Class Helper Functions----------*/

const Date& get_default_date();
inline bool is_leap_year(int year) { return year % 4 == 0; }
inline bool operator==(const Date& date1, const Date& date2) {	// allow comparison of Dates
	return date1.get_year() == date2.get_year() &&
		date1.get_month() == date2.get_month() && date1.get_day() == date2.get_day();
}
inline bool operator!=(const Date& date1, const Date& date2) {	// allow differentiation of Dates
	return !(date1 == date2);
}
inline ostream& operator<<(ostream & os, const Date & date) {	// allow output of Dates
	return os << int(date.get_month()) << '/' << date.get_day() << '/' << date.get_year();
}
istream& operator>>(istream&, Date&);
int find_days_in_month(int, Month);
int find_days_so_far(const Date&);
inline int find_week_of_year(const Date& date) {	// find which week (1:52) of year it is
	return (find_days_so_far(date) / 7 + 1);
}
inline Day find_day_of_week(const Date& date) {	// find Day of week (Sunday:Saturday)
	return Day((find_days_so_far(date) - 1) % 7);
}
Date find_next_workday(const Date&);
Date find_next_sunday(const Date&);
}