#include "Temps.h"
#include <fstream>

const std::string input_file = "Ex_05_input.txt";
const std::string output_file = "Ex_05_output.txt";

void import_temps(std::vector<Year>&);
void export_temps(const std::vector<Year>&);

int main()
try {
	std::vector<Year> years;

	import_temps(years);
	export_temps(years);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}

void import_temps(std::vector<Year>& years) {
	std::ifstream ifs{ input_file };
	if (!ifs)
		throw std::exception("could not open input file");
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	while (true) {
		Year year;
		if (!(ifs >> year))
			break;
		years.push_back(year);
	}

	std::cout << "Read " << years.size() << " years of readings.\n";
}

void export_temps(const std::vector<Year>& years) {
	std::ofstream ofs{ output_file };
	if (!ofs)
		throw std::exception("could not open output file");

	for (Year year : years)
		ofs << year << '\n';
}