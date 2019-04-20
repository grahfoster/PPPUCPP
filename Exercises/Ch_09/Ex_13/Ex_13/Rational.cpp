#include "Rational.h"

Rational::Rational() :
	numerator(0), denominator(1) {}

Rational::Rational(int numerator, int denominator) :
	numerator(numerator), denominator(denominator) {
	if (!is_valid())
		throw std::exception("Rational() - invalid constructor argument");
};

void Rational::operator=(const Rational& rational) {
	numerator = rational.get_numerator();
	denominator = rational.get_denominator();
}

double Rational::convert_to_double() const {
	return double(numerator) / denominator;
}

bool Rational::is_valid() {
	return denominator != 0;
}

Rational operator+(const Rational& rational1, const Rational& rational2) {
	int numerator = rational1.get_numerator() * rational2.get_denominator() +
		rational2.get_numerator() * rational1.get_denominator();
	int denominator = rational1.get_denominator() * rational2.get_denominator();

	return Rational{ numerator, denominator };
}

Rational operator-(const Rational& rational1, const Rational& rational2) {
	int numerator = rational1.get_numerator() * rational2.get_denominator() -
		rational2.get_numerator() * rational1.get_denominator();
	int denominator = rational1.get_denominator() * rational2.get_denominator();

	return Rational{ numerator, denominator };
}

Rational operator*(const Rational& rational1, const Rational& rational2) {
	int numerator = rational1.get_numerator() * rational2.get_numerator();
	int denominator = rational1.get_denominator() * rational2.get_denominator();

	return Rational{ numerator, denominator };
}

Rational operator/(const Rational& rational1, const Rational& rational2) {
	Rational rational2_r{ rational2.get_denominator(), rational2.get_numerator() };
	return rational1 * rational2_r;
}

bool operator==(const Rational& rational1, const Rational& rational2) {
	return rational1.convert_to_double() == rational2.convert_to_double();
}

bool operator!=(const Rational& rational1, const Rational& rational2) {
	return !(rational1 == rational2);
}