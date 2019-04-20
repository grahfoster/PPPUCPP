/*
	This file provides interfaces for classes and helper functions used in creating and
	accessing monetary amounts.
*/

#include <string>

/*--------------------Enum Classes--------------------*/

enum class Currency {	// contains common currency labels
	USD, EUR, JPY, GBP
};

/*--------------------Money Class--------------------*/

class Money {	// represents monetary amount as total cents
public:
	Money();
	Money(Currency, double);

	long int get_total_cents() const { return total_cents; }
	std::string find_currency_label() const;
	double convert_to_amount() const;
private:
	Currency currency;
	long int total_cents;

	bool is_valid();
	long int convert_to_cents(double);
};

Currency find_currency_enum(std::string);
std::ostream& operator<<(std::ostream&, const Money&);
std::istream& operator>>(std::istream&, Money&);