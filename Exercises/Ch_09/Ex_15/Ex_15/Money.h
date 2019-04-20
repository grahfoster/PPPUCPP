/*
	This file provides interfaces for classes and helper functions used in creating and
	accessing monetary amounts.
*/

#include <string>
#include <iostream>

enum class Currency {	// contains common currency denominations
	USD, EUR, JPY, GBP
};

class Money {	// represents dollars and cents amount as total cents
public:
	Money();
	Money(Currency, double);

	long int get_total_cents() const { return total_cents; }
private:
	Currency currency;
	long int total_cents;

	long int convert_to_cents(double);
	bool is_valid(long int);
};