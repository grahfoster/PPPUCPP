#include "Chrono.h"

using namespace Chrono;
using std::cout;
using std::cerr;

int main()
try {
	Date date{ 10000 };
	cout << "Days since epoch: " << date <<
		"\nDate: " << int(date.get_month()) << '/' << date.get_day() << '/' << date.get_year() << '\n';
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}