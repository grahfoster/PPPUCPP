#include <iostream>

struct Reading {
	int hour;
	double temperature;
};

std::ostream& operator<<(std::ostream&, const Reading&);