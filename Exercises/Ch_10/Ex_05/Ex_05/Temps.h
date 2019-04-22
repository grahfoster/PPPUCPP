#include <vector>
#include <iostream>

const int invalid = -7777;

struct Reading {
	int day;
	int hour;
	double temperature;
};

std::istream& operator>>(std::istream&, Reading&);
bool is_valid(const Reading&);

struct Day {
	std::vector<double> hour{ std::vector<double>(24, invalid) };
};

struct Month {
	int month = invalid;
	std::vector<Day> day{ 32 };
};

std::istream& operator>>(std::istream&, Month&);
std::ostream& operator<<(std::ostream&, const Month&);
int month_to_int(std::string);
std::string int_to_month(int);

struct Year {
	int year;
	std::vector<Month> month{ 12 };
};

std::istream& operator>>(std::istream&, Year&);
std::ostream& operator<<(std::ostream&, const Year&);

void end_of_loop(std::istream&, char, const std::string&);