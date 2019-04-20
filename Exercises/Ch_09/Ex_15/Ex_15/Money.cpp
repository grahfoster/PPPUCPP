/*
	This file provides implementations for classes and helper functions used in creating
	and accessing monetary amounts.
*/

#include "Money.h"

const double eur_conversion = 1.124;
const double jpy_conversion = .008935;
const double gbp_conversion = 1.299;

// construct Money with default value for total cents
Money::Money() :
	currency(Currency::USD), total_cents(0) {}

// construct Money with custom value for total cents
Money::Money(Currency currency, double amount) :
	currency(currency) {
	total_cents = convert_to_cents(amount);
	if (!is_valid(total_cents))
		throw std::exception("Money() - invalid constructor argument");
}

// convert monetary amount to cents
long int Money::convert_to_cents(double amount) {
	double converted_amount = 0;

	switch (currency) {
	case Currency::USD:
		converted_amount = amount;
		break;
	case Currency::EUR:
		converted_amount = amount * eur_conversion;
		break;
	case Currency::JPY:
		converted_amount = amount * jpy_conversion;
		break;
	case Currency::GBP:
		converted_amount = amount * gbp_conversion;
	}

	return (converted_amount * 100 + .5);	// round to nearest cent
}

// check if Money construction is valid
bool Money::is_valid(long int total_cents) {
	return total_cents >= 0;	// amount must be positive
}