/*
	This file provides interfaces for classes and helper functions used in creating and
	accessing monetary amounts.
*/

#include <iostream>

class Money {	// represents dollars and cents amount as total cents
public:
	Money();
	Money(double);

	long int get_total_cents() const { return total_cents; }
private:
	long int total_cents;

	bool is_valid(long int);
};