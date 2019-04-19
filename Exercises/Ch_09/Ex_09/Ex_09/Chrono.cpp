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
	//	if (month == Month::feb && day == 29 && !is_leap_year(year + n)) {
	//		month = Month::mar;
	//		day = 1;
	//	}
	year += n;
}

// increase Date by n months
//void Date::add_month(int n) {
//	
//}

// increase Date by n days
//void Date::add_day(int n) {
//	
//}

// check if Date is valid calendar day
bool Date::is_valid() {
	int days_in_month = 31;	// most months have 31 days

	switch (month) {
	case Month::feb:	// february has 28 or 29 days
//		days_in_month = is_leap_year(year) ? 29 : 28;	// check for leap year
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

// check if year is leap year
//bool is_leap_year(int year) {
//
//}

// allow input of Dates
istream& operator>>(istream& is, Date& date) {
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

// find Day of week (Sunday:Saturday)
//Day find_day_of_week(const Date&) {
//	
//}

// find Date of next Sunday
//Date find_next_sunday(const Date&) {
//	
//}

// find Date of next Weekday
//Date find_next_weekday(const Date&) {
//	
//}
}