#include "Rational.h"
#include <iostream>

int main()
try {
	Rational rational1{ 1, 4 };
	Rational rational2{ 1, 8 };
	rational2 = Rational{ 2, 8 };
	Rational rational3{ rational1 + rational2 };
	Rational rational4{ rational1 * rational2 };
	Rational rational5{ rational1 / rational2 };
	Rational rational6{ 5, 10 };

	std::cout << rational3.get_numerator() << '/' << rational3.get_denominator() <<
		" = " << rational3.convert_to_double() << '\n';

	std::cout << rational4.get_numerator() << '/' << rational4.get_denominator() <<
		" = " << rational4.convert_to_double() << '\n';

	std::cout << rational5.get_numerator() << '/' << rational5.get_denominator() <<
		" = " << rational5.convert_to_double() << '\n';

	std::cout << rational3.get_numerator() << '/' << rational3.get_denominator() <<
		(rational3 == rational6 ? " = " : " != ") <<
		rational6.get_numerator() << '/' << rational6.get_denominator() << '\n';
}
catch (std::exception & e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}