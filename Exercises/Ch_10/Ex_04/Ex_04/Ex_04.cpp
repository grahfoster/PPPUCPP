#include "Reading.h"
#include <fstream>

const int num_readings = 50;
const int max_hour = 24;
const int max_temperature = 100;
const char fahrenheit_char = 'f';
const char celsius_char = 'c';
const double celsius_conversion = 1.8;
const int celsius_offset = 32;
const std::string output_file = "raw_temps.txt";
const std::string input_file = "raw_temps.txt";

void generate_readings(std::vector<Reading>&);
void export_readings(std::vector<Reading>&);
void import_readings(std::vector<Reading>&);

int main()
try {
	std::vector<Reading> output_readings{};
	std::vector<Reading> input_readings{};

	generate_readings(output_readings);
	export_readings(output_readings);
	import_readings(input_readings);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}

void generate_readings(std::vector<Reading>& output_readings) {
	for (int i = 0; i < num_readings; ++i) {
		int random_hour = rand() % max_hour;
		double random_temperature = rand() % max_temperature +
			rand() % max_temperature / double(max_temperature);
		char random_unit = rand() % 2 == 0 ? fahrenheit_char : celsius_char;

		output_readings.push_back(Reading{ random_hour, random_temperature, random_unit });
	}
}

void export_readings(std::vector<Reading>& output_readings) {
	std::ofstream ofs{ output_file };

	for (Reading reading : output_readings)
		ofs << reading << '\n';
}

void import_readings(std::vector<Reading> & input_readings) {
	std::ifstream ifs{ input_file };
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	for (Reading reading; ifs >> reading;) {
		if (reading.unit == celsius_char) {
			reading.temperature = reading.temperature * celsius_conversion + celsius_offset;
			reading.unit = fahrenheit_char;
		}

		input_readings.push_back(reading);
	}
}