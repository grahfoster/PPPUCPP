#include "Reading.h"
#include <algorithm>

std::istream& operator>>(std::istream& is, Reading& reading) {
	int hour = 0;
	double temperature = 0;

	is >> hour >> temperature;
	if (is.eof())
		return is;
	if (is.fail())
		throw std::exception("operator>>() - invalid input");

	reading.hour = hour;
	reading.temperature = temperature;

	return is;
}

std::ostream& operator<<(std::ostream& os, const Reading& reading) {
	return os << reading.hour << ' ' << std::fixed << std::setprecision(1) << reading.temperature;
}

double find_mean_temperature(std::vector<Reading>& readings) {
	double sum = 0;

	for (Reading reading : readings)
		sum += reading.temperature;

	return sum / readings.size();
}

double find_median_temperature(std::vector<Reading>& readings) {
	std::vector<double> temperatures;

	for (Reading reading : readings)
		temperatures.push_back(reading.temperature);

	std::sort(temperatures.begin(), temperatures.end());

	if (temperatures.size() % 2 == 0)
		return (temperatures[temperatures.size() / 2] + 
			temperatures[temperatures.size() / 2 - 1]) / 2;
	else
		return temperatures[temperatures.size() / 2];
}