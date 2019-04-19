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
	day(get_default_date().get_day()) {
	set_days_since_epoch();
}

//	construct Date with custom values for year, month, and day
Date::Date(int year, Month month, int day) :
	year(year), month(month), day(day) {
	set_days_since_epoch();
	if (!is_valid())	// validate arguments
		throw exception("Date() - invalid constructor argument");
}

// construct Date with custom value for days since epoch
Date::Date(long int days_since_epoch) :
	days_since_epoch(days_since_epoch) {
	set_year_month_day();
	if (!is_valid())	// validate argument
		throw exception("Date() - invalid constructor argument");
}

/*----------Date Class Member Functions----------*/

// increase Date by n years
void Date::add_year(int n) {
	for (int i = 0; i < n; ++i) {
		if (month > Month::feb && is_leap_year(year + 1))
			days_since_epoch += 1;	// account for leap year
		days_since_epoch += 365;
	}

	if (month == Month::feb && day == 29 && !is_leap_year(year + n)) {	// account for leap years
		month = Month::mar;
		day = 1;
	}
	year += n;
}

// increase Date by n months
void Date::add_month(int n) {
	for (int i = 0; i < n; ++i) {
		days_since_epoch += find_days_in_month(year, month);

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
		days_since_epoch += n;

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
	return year >= 1970 && month >= Month::jan && month <= Month::dec &&
		day > 0 && day <= find_days_in_month(year, month);	// validate Date
}

// set number of days since epoch based on year, month, and day
void Date::set_days_since_epoch() {
	days_since_epoch = (year - 1970) * 365;	// calculate days from all previous years
	days_since_epoch += (year - 1970 + 2) / 4;	// add extra days from leap years (first isn't for two years)
	days_since_epoch += find_days_so_far(*this) - 1;	// add days in year so far
}

// set year, month, and day based on days since epoch
void Date::set_year_month_day() {
	int long days_left = days_since_epoch;
	int years = 0;
	int months = 0;

	for (int i = 2; (i % 4 == 0 && days_left > 366) || days_left > 365; ++i) {
		if (i % 4 == 0)	// account for leap years (first isn't for two years)
			days_left -= 366;	// subtract leap year worth of days
		else
			days_left -= 365;	// subtract regulat year worth of days
		++years;
	}

	year = 1970 + years;	// add years to epoch years

	for (int i = int(Month::jan); days_left > find_days_in_month(year, Month(i)); ++i) {
		days_left -= find_days_in_month(year, Month(i));	// subtract month worth of days
		++months;
	}

	month = Month(months + 1);	// adjust for enum member numbering
	day = days_left + 1;	// adjust for calendar date
}

/*----------Date Class Helper Functions----------*/

// get default Date
const Date& get_default_date() {
	static Date default_date{ 2001, Month::jan, 1 };	// first day of 21st century
	return default_date;
}

// allow input of Dates
istream& operator>>(istream & is, Date & date) {
	long int days_since_epoch;

	is >> days_since_epoch;	// read in formatted Date string
	if (!is)	// input error
		return is;

	date = Date{ days_since_epoch };	// assign input value to Date

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
		throw exception("find_days_in_month() - invalid enum member");
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