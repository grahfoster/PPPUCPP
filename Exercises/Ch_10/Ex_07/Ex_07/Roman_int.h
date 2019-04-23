/*
	This file provides interfaces for classes and helper functions used in
	creating, manipulating, and accessing Roman numeral representations.
*/

#include <iostream>

/*--------------------Roman_int Class--------------------*/

class Roman_int {	// represents a sequence of Roman numerals
public:
	Roman_int();
	Roman_int(const std::string&);

	std::string get_numerals() const { return numerals; }
	int to_int() const;
private:
	std::string numerals;
};

std::istream& operator>>(std::istream&, Roman_int&);
std::ostream& operator<<(std::ostream&, const Roman_int&);
bool are_valid_numerals(const std::string&);
int find_numeral_index(char);
bool is_numeral(char);
std::string to_numerals(int);