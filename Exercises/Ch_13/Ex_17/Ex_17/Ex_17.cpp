#include "../Graph.h"
#include "../Simple_window.h"

const double pi = atan(1) * 4;

namespace Graph_lib {

class Regular_hexagon : public Polygon {
public:
	Regular_hexagon(Point, int);

	Point center() { return c; }
	int radius() { return r; }
private:
	Point c;
	int r;

	void add(Point p) { Polygon::add(p); }
};

Regular_hexagon::Regular_hexagon(Point center, int radius) :
	c{ center }, r{ radius }
{
	add(Point{ center.x, center.y - radius });
	add(Point{ int(center.x + radius * sqrt(3) / 2),
		int(center.y - sin(30 * pi / 180) * radius) });
	add(Point{ point(1).x, point(1).y + radius });
	add(Point{ center.x, center.y + radius });
	add(Point{ int(center.x - radius * sqrt(3) / 2), point(2).y });
	add(Point{ point(4).x, point(1).y });
}
}

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 4, y_max() / 4 };
	const int win_width = x_max() / 2;
	const int win_height = y_max() / 2;
	const string win_name{ "My window" };
	Simple_window s_win{ win_tl, win_width, win_height, win_name };

	const int radius = 20;
	const int x_incr = radius * sqrt(3) / 2;
	const int y_incr = radius + sin(30 * pi / 180) * radius;
	const Point origin{ x_incr, radius };

	Vector_ref<Regular_hexagon> hexes;

	for (int i = 0; (i + 3) * x_incr < s_win.x_max(); i += 2)
		for (int j = 0; (j + 2) * y_incr + radius < s_win.y_max(); j += 2) {
			hexes.push_back(new Regular_hexagon{ { origin.x + i * x_incr, origin.y + j * y_incr }, radius });
			hexes.push_back(new Regular_hexagon{ { origin.x + (i + 1) * x_incr, origin.y + (j + 1) * y_incr }, radius });
			hexes[hexes.size() - 2].set_fill_color(Color(i % 3));
			hexes[hexes.size() - 1].set_fill_color(Color((i + 1) % 3));
			s_win.attach(hexes[hexes.size() - 2]);
			s_win.attach(hexes[hexes.size() - 1]);
		}

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}