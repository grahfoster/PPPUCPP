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
const int max_numeral_value = 3999;

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

// check if character is numeral
bool is_numeral(char numeral) {
	for (char c : roman_numerals)
		if (numeral == c)
			return true;
	return false;
}

// convert integer to numerals
std::string to_numerals(int i) {
	std::string numerals;

	if (i == 0)
		return roman_zero;

	// indicate if number is negative
	if (i < 0) {
		numerals += '-';
		i = abs(i);
	}

	if (i > max_numeral_value)
		throw std::exception("can't represent with numerals");

	// track values for each index
	int num_i = 0;
	bool iv = false;
	int num_v = 0;
	bool ix = false;
	int num_x = 0;
	bool xl = false;
	int num_l = 0;
	bool xc = false;
	int num_c;
	bool cd = false;
	int num_d;
	bool cm = false;
	int num_m;

	// find values for each index
	num_m = i / arabic_numerals[6];
	i %= arabic_numerals[6];
	num_d = i / arabic_numerals[5];
	i %= arabic_numerals[5];
	num_c = i / arabic_numerals[4];
	i %= arabic_numerals[4];
	num_l = i / arabic_numerals[3];
	i %= arabic_numerals[3];
	num_x = i / arabic_numerals[2];
	i %= arabic_numerals[2];
	num_v = i / arabic_numerals[1];
	i %= arabic_numerals[1];
	num_i = i;

	// account for "less-than" numeral combinations
	if (num_d > 0 && num_c > max_repeating_numerals) {
		num_d = 0;
		num_c = 0;
		cm = true;
	}
	if (num_d == 0 && num_c > max_repeating_numerals) {
		num_c = 0;
		cd = true;
	}
	if (num_l > 0 && num_x > max_repeating_numerals) {
		num_l = 0;
		num_x = 0;
		xc = true;
	}
	if (num_l == 0 && num_x > max_repeating_numerals) {
		num_x = 0;
		xl = true;
	}
	if (num_v > 0 && num_i > max_repeating_numerals) {
		num_v = 0;
		num_i = 0;
		ix = true;
	}
	if (num_v == 0 && num_i > max_repeating_numerals) {
		num_i = 0;
		iv = true;
	}

	// form numerals string
	for (int i = 0; i < num_m; ++i)
		numerals += roman_numerals[6];
	if (cm) {
		numerals += roman_numerals[4];
		numerals += roman_numerals[6];
	}
	for (int i = 0; i < num_d; ++i)
		numerals += roman_numerals[5];
	if (cd) {
		numerals += roman_numerals[4];
		numerals += roman_numerals[5];
	}
	for (int i = 0; i < num_c; ++i)
		numerals += roman_numerals[4];
	if (xc) {
		numerals += roman_numerals[2];
		numerals += roman_numerals[4];
	}
	for (int i = 0; i < num_l; ++i)
		numerals += roman_numerals[3];
	if (xl) {
		numerals += roman_numerals[2];
		numerals += roman_numerals[3];
	}
	for (int i = 0; i < num_x; ++i)
		numerals += roman_numerals[2];
	if (ix) {
		numerals += roman_numerals[0];
		numerals += roman_numerals[2];
	}
	for (int i = 0; i < num_v; ++i)
		numerals += roman_numerals[1];
	if (iv) {
		numerals += roman_numerals[0];
		numerals += roman_numerals[1];
	}
	for (int i = 0; i < num_i; ++i)
		numerals += roman_numerals[0];

	return numerals;
}