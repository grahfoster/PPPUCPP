#include "Temps.h"

const int implausible_min = -200;
const int implausible_max = 200;

std::istream& operator>>(std::istream& is, Reading& reading) {
	char begin = 0;
	if (is >> begin && begin != '(') {
		is.unget();
		is.clear(std::ios_base::failbit);
		return is;
	}

	char end = 0;
	int day = 0;
	int hour = 0;
	double temperature = 0;
	is >> day >> hour >> temperature >> end;
	if (!is || end != ')')
		throw std::exception("operator>>() - invalid Reading format");
	reading.day = day;
	reading.hour = hour;
	reading.temperature = temperature;

	return is;
}

bool is_valid(const Reading & reading) {
	return reading.day > 1 || 31 > reading.day ||
		reading.hour > 0 || 23 > reading.hour ||
		reading.temperature > implausible_min || implausible_max > reading.temperature;
}

std::istream& operator>>(std::istream & is, Month & month) {
	char begin = 0;
	if (is >> begin && begin != '{') {
		is.unget();
		is.clear(std::ios_base::failbit);
		return is;
	}

	std::string month_marker;
	std::string month_label;
	is >> month_marker >> month_label;
	if (!is || month_marker != "month")
		throw std::exception("operator>>() - invalid Month format");
	month.month = month_to_int(month_label);

	int duplicates = 0;
	int invalids = 0;
	for (Reading reading; is >> reading;) {
		if (is_valid(reading)) {
			if (month.day[reading.day].hour[reading.hour] != invalid)
				++duplicates;
			month.day[reading.day].hour[reading.hour] = reading.temperature;
		}
		else
			++invalids;
	}

	if (invalids)
		throw std::exception("operator>>() - invalid Reading", invalids);
	if (duplicates)
		throw std::exception("operator>>() - duplicate Reading", duplicates);

	end_of_loop(is, '}', "invalid Month format");

	return is;
}

std::ostream& operator<<(std::ostream & os, const Month & month) {
	if (month.month == invalid)
		return os;
	os << "\n\t{ month " << int_to_month(month.month);
	for (int i = 0; i < month.day.size(); ++i)
		for (int j = 0; j < month.day[i].hour.size(); ++j)
			if (month.day[i].hour[j] != invalid)
				os << " ( " << i << ' ' << j << ' ' << month.day[i].hour[j] << " )";
	return os << " }";
}

int month_to_int(std::string month_label) {
	std::vector<std::string> month_input_table{
		"jan", "feb", "mar", "apr", "may", "jun",
		"jul", "aug", "sep", "oct", "nov", "dec"
	};
	for (int i = 0; i < month_input_table.size(); ++i)
		if (month_label == month_input_table[i])
			return i;

	return invalid;
}

std::string int_to_month(int month) {
	std::vector<std::string> month_output_table{
		"January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November", "December"
	};
	if (month < 0 || month_output_table.size() <= month)
		throw std::exception("int_to_month() - invalid month");

	return month_output_table[month];
}

void end_of_loop(std::istream & is, char terminator, const std::string & message) {
	std::string extended_message = "end_of_loop() - " + message;
	const char* exception_message = extended_message.c_str();

	if (is.fail()) {
		is.clear();
		char ch = 0;
		if (is >> ch && ch == terminator)
			return;
		throw std::exception(exception_message);
	}
}

std::istream& operator>>(std::istream & is, Year & year) {
	char begin = 0;
	is >> begin;
	if (begin != '{') {
		is.unget();
		is.clear(std::ios_base::failbit);
		return is;
	}

	std::string year_marker;
	int year_num = 0;
	is >> year_marker >> year_num;
	if (!is || year_marker != "year")
		throw std::exception("operator>>() - bad Year format");
	year.year = year_num;

	while (true) {
		Month month;
		if (!(is >> month))
			break;
		year.month[month.month] = month;
	}

	end_of_loop(is, '}', "bad Year format");

	return is;
}

std::ostream& operator<<(std::ostream & os, const Year & year) {
	os << "{ year " << year.year;
	for (Month month : year.month)
		os << month;
	return os << " }";
}