#include "Chrono.h"

using namespace Chrono;
using std::cout;
using std::cerr;

int main()
try {
	Date date{ 2020, Month::dec, 31 };
	cout << "Days in year so far: " << find_days_so_far(date) <<
		"\nWeek of the year: " << find_week_of_year(date) <<
		"\nDay of the week: " << int(find_day_of_week(date)) <<
		"\nNext workday: " << find_next_workday(date) <<
		"\nNext sunday: " << find_next_sunday(date) << '\n';
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}