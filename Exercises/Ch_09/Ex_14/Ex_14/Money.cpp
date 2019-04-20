/*
	This file provides implementations for classes and helper functions used in creating
	and accessing monetary amounts.
*/

#include "Money.h"

// construct Money with default value for total cents
Money::Money() :
	total_cents(0) {}

// construct Money with custom value for total cents
Money::Money(double dollars_cents) :
	total_cents(dollars_cents * 100 + .5) {	// round to nearest cent
	if (!is_valid(total_cents))
		throw std::exception("Money() - invalid constructor argument");
}

// check if Money construction is valid
bool Money::is_valid(long int total_cents) {
	return total_cents >= 0;	// amount must be positive
}
