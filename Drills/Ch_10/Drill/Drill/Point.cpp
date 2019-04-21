#include "Point.h"

const char begin_char = '(';
const char separate_char = ',';
const char	end_char = ')';

bool operator==(const Point& point1, const Point& point2) {
	return point1.x_coord == point2.x_coord && point1.y_coord == point2.y_coord;
}

bool operator!=(const Point& point1, const Point& point2) {
	return !(point1 == point2);
}

std::istream& operator>>(std::istream & is, Point & point) {

	char begin;
	char separate;
	char end;
	int x_coord;
	int y_coord;

	if (is >> begin && begin != begin_char) {
		while (begin != begin_char && is >> begin);
		if (!is)
			throw std::exception("operator>>() - not enough valid input");
	}

	is >> x_coord >> separate >> y_coord >> end;
	if (separate != separate_char || end != end_char)
		throw std::exception("operator>>() - bad format");
	if (!is)
		throw std::exception("operator>>() - invalid input");

	point.x_coord = x_coord;
	point.y_coord = y_coord;

	return is;
}

std::ostream& operator<<(std::ostream & os, const Point & point) {
	return os << begin_char << point.x_coord << separate_char << ' ' << point.y_coord << end_char;
}
