#include "Reading.h"
#include <fstream>

const std::string input_file = "raw_temps.txt";

void import_readings(std::vector<Reading>&);

int main()
try {
	std::vector<Reading> readings{};

	import_readings(readings);
	std::cout << "Mean temperature: " << std::fixed << std::setprecision(1) <<
		find_mean_temperature(readings) << '\n';
	std::cout << "Median temperature: " << std::fixed << std::setprecision(1) <<
		find_median_temperature(readings) << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}

void import_readings(std::vector<Reading>& readings) {
	std::ifstream ifs{ input_file };
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	for (Reading reading; ifs >> reading;)
		readings.push_back(reading);
}