#include "Reading.h"
#include <iomanip>

std::ostream& operator<<(std::ostream& os, const Reading& reading) {
	return os << reading.hour << ' ' << std::fixed << std::setprecision(1) << reading.temperature;
}