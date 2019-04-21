#include <iostream>

struct Point {
	int x_coord;
	int y_coord;
};

bool operator==(const Point&, const Point&);
bool operator!=(const Point&, const Point&);
std::istream& operator>>(std::istream&, Point&);
std::ostream& operator<<(std::ostream&, const Point&);
