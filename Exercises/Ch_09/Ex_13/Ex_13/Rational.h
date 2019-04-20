#include <exception>

class Rational {
public:
	Rational();
	Rational(int, int);

	int get_numerator() const { return numerator; }
	int get_denominator() const { return denominator; }
	double convert_to_double() const;

	void operator=(const Rational&);
private:
	int numerator;
	int denominator;

	bool is_valid();
};

Rational operator+(const Rational&, const Rational&);
Rational operator-(const Rational&, const Rational&);
Rational operator*(const Rational&, const Rational&);
Rational operator/(const Rational&, const Rational&);
bool operator==(const Rational&, const Rational&);
bool operator!=(const Rational&, const Rational&);