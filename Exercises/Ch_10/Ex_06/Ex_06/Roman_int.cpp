/*
	This file provides implementations for classes and helper functions used in
	creating, manipulating, and accessing Roman numeral representations.
*/

#include "Roman_int.h"
#include <vector>

/*--------------------Global Constants--------------------*/

const std::string roman_zero{ "Nulla" };
const std::vector<char> roman_numerals{
	'I', 'V', 'X', 'L', 'C', 'D', 'M'
};
const std::vector<int> arabic_numerals{
	1, 5, 10, 50, 100, 500, 1000
};
const int max_repeating_numerals = 3;

/*--------------------Roman_int Class Constructors--------------------*/

// construct Roman_int with default value for numerals
Roman_int::Roman_int() :
	numerals(roman_zero) {};

// construct Roman_int with custom value for numerals
Roman_int::Roman_int(const std::string& numerals) {
	if (!are_valid_numerals(numerals))
		throw std::exception("invalid numerals");
	this->numerals = numerals;
}

/*--------------------Roman_int Class Member Functions--------------------*/

// convert numerals to integer
int Roman_int::to_int() const {
	int sum = 0;

	if (numerals == roman_zero)	// default value; must be 0
		return sum;

	std::vector<int> numeral_indexes;
	for (char numeral : numerals)	// form vector of corresponding indices
		numeral_indexes.push_back(find_numeral_index(numeral));

	for (int i = 0; i < numerals.size(); ++i) {
		// account for "less-than" numeral combinations
		if (i < numerals.size() - 1 &&
			numeral_indexes[i] < numeral_indexes[i + 1]) {
			sum += arabic_numerals[numeral_indexes[i + 1]] -
				arabic_numerals[numeral_indexes[i]];
			++i;	// eat both numerals
		}
		else
			sum += arabic_numerals[numeral_indexes[i]];
	}

	return sum;
}

/*--------------------Roman_int Class Helper Functions--------------------*/

// allow input of Roman_ints
std::istream& operator>>(std::istream& is, Roman_int& roman_int) {
	std::string numerals;
	is >> numerals;	// input numerals string
	if (is.eof())
		throw std::exception("no input");
	if (!is)
		throw std::exception("invalid input");
	roman_int = Roman_int{ numerals };

	return is;
}

// allow output of Roman_ints
std::ostream& operator<<(std::ostream& os, const Roman_int& roman_int) {
	return os << roman_int.get_numerals();
}

// validate numerals string
bool are_valid_numerals(const std::string& numerals) {
	std::vector<int> numeral_indexes;
	for (char numeral : numerals)	// form vector of corresponding indices
		numeral_indexes.push_back(find_numeral_index(numeral));

	// test each numeral in relation to preceding or following numeral
	for (int i = 0; i < numerals.size(); ++i) {
		// V, L, and D can't precede greater or equal numerals
		if (numeral_indexes[i] % 2 != 0 && i < numerals.size() - 1 &&
			numeral_indexes[i] <= numeral_indexes[i + 1])
			return false;
		// numeral can't be more than two indices greater than following numeral
		if (i > 0 && numeral_indexes[i] > numeral_indexes[i - 1] + 2)
			return false;
		// numeral can't precede and follow equal numerals
		if (i > 0 && i < numerals.size() - 1 &&
			numeral_indexes[i] > numeral_indexes[i - 1] &&
			numeral_indexes[i - 1] == numeral_indexes[i + 1])
			return false;
		// numeral can't precede numeral greater than following numeral
		if (i > 0 && i < numerals.size() - 1 &&
			numeral_indexes[i] < numeral_indexes[i + 1] &&
			numeral_indexes[i + 1] > numeral_indexes[i - 1])
			return false;
		// numeral can't repeat more than twice
		if (numerals.size() > i + max_repeating_numerals &&
			numeral_indexes[i] == numeral_indexes[i + 1] &&
			numeral_indexes[i] == numeral_indexes[i + 2] &&
			numeral_indexes[i] == numeral_indexes[i + max_repeating_numerals])
			return false;
	}
	return true;
}

// find corresponding index of numeral
int find_numeral_index(char numeral) {
	for (int i = 0; i < roman_numerals.size(); ++i)
		if (toupper(numeral) == roman_numerals[i])
			return i;
	throw std::exception("invalid numerals");	// character isn't numeral
}