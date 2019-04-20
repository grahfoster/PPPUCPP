/*
	This file provides implementations for classes and helper functions used in creating
	and accessing monetary amounts.
*/

#include "Money.h"
#include <iomanip>

/*--------------------Global Constants--------------------*/

const double eur_conversion = 1.124;
const double jpy_conversion = .008935;
const double gbp_conversion = 1.299;
const std::string usd_label{ "USD" };
const std::string eur_label{ "EUR" };
const std::string jpy_label{ "JPY" };
const std::string gbp_label{ "GBP" };

/*--------------------Money Class Constructors--------------------*/

// construct Money with default value for total cents
Money::Money() :
	currency(Currency::USD), total_cents(0) {}

// construct Money with custom value for total cents
Money::Money(Currency currency, double amount) :
	currency(currency) {
	total_cents = convert_to_cents(amount);
	if (!is_valid())
		throw std::exception("Money() - invalid constructor argument");
}

/*--------------------Money Class Member Functions--------------------*/

// find currency label from Currency enum
std::string Money::find_currency_label() const {
	switch (currency) {
	case Currency::USD:
		return usd_label;
	case Currency::EUR:
		return eur_label;
	case Currency::JPY:
		return jpy_label;
	case Currency::GBP:
		return gbp_label;
	default:
		throw std::exception("find_currency_label() - invalid enum member");
	}
}

// convert cents to monetary amount
double Money::convert_to_amount() const {
	double converted_cents = total_cents;

	switch (currency) {
	case Currency::EUR:
		converted_cents /= eur_conversion;
		break;
	case Currency::JPY:
		converted_cents /= jpy_conversion;
		break;
	case Currency::GBP:
		converted_cents /= gbp_conversion;
	}

	return converted_cents / 100;
}

// check if Money construction is valid
bool Money::is_valid() {
	return total_cents >= 0;	// amount must be positive
}

// convert monetary amount to cents
long int Money::convert_to_cents(double amount) {
	double converted_amount = amount;

	switch (currency) {
	case Currency::EUR:
		converted_amount *= eur_conversion;
		break;
	case Currency::JPY:
		converted_amount *= jpy_conversion;
		break;
	case Currency::GBP:
		converted_amount *= gbp_conversion;
	}

	return long int(converted_amount * 100 + .5);	// round to nearest cent
}

/*--------------------Money Class Helper Functions--------------------*/

// find Currency enum from currency label
Currency find_currency_enum(std::string currency) {
	if (currency == usd_label)
		return Currency::USD;
	if (currency == eur_label)
		return Currency::EUR;
	if (currency == jpy_label)
		return Currency::JPY;
	if (currency == gbp_label)
		return Currency::GBP;
	throw std::exception("find_currency_enum() - invalid currency label");
}

// allow output of Money
std::ostream & operator<<(std::ostream & os, const Money & money) {
	return os << money.find_currency_label() << ' ' <<
		std::fixed << std::setprecision(2) << money.convert_to_amount();
}

// allow input of Money
std::istream& operator>>(std::istream & is, Money & money) {
	std::string currency;
	double amount = 0;
	char buffer = 0;

	is >> buffer;	// ignore whitespace
	while (isalpha(buffer)) {	// get currency label
		currency.push_back(buffer);
		is >> buffer;
	}
	is.putback(buffer);

	is >> amount;	// get monetary amount

	if (!is)	// input error
		throw std::exception("operator>>() - invalid input");

	money = Money{ find_currency_enum(currency), amount };

	return is;
}