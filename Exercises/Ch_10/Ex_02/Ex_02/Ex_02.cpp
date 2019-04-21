#include "Reading.h"
#include <vector>
#include <fstream>

const int num_readings = 50;
const int max_hour = 24;
const int max_temperature = 100;
const std::string output_file = "raw_temps.txt";

void generate_readings(std::vector<Reading>&);
void export_readings(std::vector<Reading>&);

int main()
try {
	std::vector<Reading> readings{};

	generate_readings(readings);
	export_readings(readings);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}

void generate_readings(std::vector<Reading>& readings ) {
	for (int i = 0; i < num_readings; ++i) {
		int random_hour = rand() % max_hour;
		double random_temperature = rand() % max_temperature +
			rand() % max_temperature / double(max_temperature);

		readings.push_back(Reading{ random_hour, random_temperature });
	}
}

void export_readings(std::vector<Reading>& readings) {
	std::ofstream ofs{ output_file };
	
	for (Reading reading : readings)
		ofs << reading << '\n';
}