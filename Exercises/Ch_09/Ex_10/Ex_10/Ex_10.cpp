#include "Chrono.h"

using namespace Chrono;
using std::cout;
using std::cerr;

int main()
try {
	Date date{ 2020, Month::jan, 1 };
	if (is_leap_year(date.get_year()))
		cout << "That's a leap year.\n";
	else
		cout << "That's not a leap year.\n";
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}