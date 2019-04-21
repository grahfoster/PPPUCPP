#include <vector>
#include <iostream>
#include <iomanip>

struct Reading {
	int hour;
	double temperature;
};

std::istream& operator>>(std::istream&, Reading&);
std::ostream& operator<<(std::ostream&, const Reading&);
double find_mean_temperature(std::vector<Reading>&);
double find_median_temperature(std::vector<Reading>&);