/*
	This file provides implementations for classes and helper functions used in creating,
	accessing, and manipulating calendar dates.
*/

#include "Chrono.h"

namespace Chrono {

/*----------Date Class Constructors----------*/

// construct Date with default values for year, month, and day
Date::Date() :
	year(get_default_date().get_year()), month(get_default_date().get_month()),
	day(get_default_date().get_day()) {}

//	construct Date with custom values for year, month, and day
Date::Date(int year, Month month, int day) :
	year(year), month(month), day(day) {
	if (!is_valid())	// validate arguments
		throw exception("Date() - invalid constructor argument");
}

/*----------Date Class Member Functions----------*/

// increase Date by n years
void Date::add_year(int n) {
	if (month == Month::feb && day == 29 && !is_leap_year(year + n)) {	// account for leap years
		month = Month::mar;
		day = 1;
	}
	year += n;
}

// increase Date by n months
void Date::add_month(int n) {
	for (int i = 0; i < n; ++i) {
		if (month == Month::dec) {	// wrap around to new year
			month == Month::jan;
			add_year(1);
		}
		else
			month = Month(int(month) + 1);
	}
}

// increase Date by n days
void Date::add_day(int n) {
	for (int i = 0; i < n; ++i) {
		if (day == find_days_in_month(year, month)) {	// wrap around to new month
			day = 1;
			add_month(1);
		}
		else
			day += 1;
	}
}

// check if Date is valid calendar day
bool Date::is_valid() {
	int days_in_month = 31;	// most months have 31 days

	switch (month) {
	case Month::feb:	// february has 28 or 29 days
		days_in_month = is_leap_year(year) ? 29 : 28;	// check for leap year
		break;
	case Month::apr: case Month::jun: case Month::sep: case Month::nov:	// these months have 30 days
		days_in_month = 30;
	}

	return day > 0 && day <= days_in_month && month >= Month::jan && month <= Month::dec;	// validate Date
}

/*----------Date Class Helper Functions----------*/

// get default Date
const Date& get_default_date() {
	static Date default_date{ 2001, Month::jan, 1 };	// first day of 21st century
	return default_date;
}

// allow input of Dates
istream& operator>>(istream & is, Date & date) {
	int year;
	int month;
	int day;
	char ch1;
	char ch2;

	is >> month >> ch1 >> year >> ch2 >> day;	// read in formatted Date string
	if (!is)	// input error
		return is;
	if (ch1 != '/' || ch2 != '/') {	// format error
		is.clear(std::ios_base::failbit);
		return is;
	}

	date = Date{ year, Month(month), day };	// assign input values to Date

	return is;
}

int find_days_in_month(int year, Month month) {
	switch (month) {
	case Month::feb:
		if (is_leap_year(year))	// leap years have 29 days in February
			return 29;
		return 28;	// non–leap years have 28 days in February
	case Month::jan: case Month::mar: case Month::may: case Month::jul:
	case Month::aug: case Month::oct: case Month::dec:	// these months have 31 days
		return 31;
	case Month::apr: case Month::jun: case Month::sep: case Month::nov:	// these months have 30 days
		return 30;
	default:
		throw exception("invalid enum member");
	}
}

// find number of days in year so far
int find_days_so_far(const Date & date) {
	int days_so_far = 0;
	for (int i = int(Month::jan); i < int(date.get_month()); ++i)	// add days from previous months
		days_so_far += find_days_in_month(date.get_year(), Month(i));

	days_so_far += date.get_day();	// add days from current month

	return days_so_far;
}

// check if Day is workday (weekday)
bool is_workday(const Date & date) {
	Day day = find_day_of_week(date);

	switch (day) {
	case Day::sat: case Day::sun:	// weekends are not workdays
		return false;
	default:
		return true;
	}
}

// find Date of next workday
Date find_next_workday(const Date & date) {
	Date temp{ date };

	while (true) {	// add days until a workday is found
		temp.add_day(1);
		if (is_workday(temp))
			return temp;
	}
}

// find Date of next Sunday
Date find_next_sunday(const Date & date) {
	Date temp{ date };

	while (true) {	// add days until a Sunday is found
		temp.add_day(1);
		if (find_day_of_week(temp) == Day::sun)
			return temp;
	}
}
}