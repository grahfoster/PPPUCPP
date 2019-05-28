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

	const int radius = 50;
	const double x_incr = radius * sqrt(3) / 2;
	const double y_incr = radius + sin(30 * pi / 180) * radius;
	const Point origin{ int(x_incr), s_win.y_max() / 2 };

	Vector_ref<Regular_hexagon> hexes;

	for (int i = 0; i * x_incr + x_incr * 2 < s_win.x_max(); ++i) {
		hexes.push_back(new Regular_hexagon{ { int(origin.x + i * x_incr),
			int(origin.y + i % 2 * y_incr) }, radius });
		hexes[hexes.size() - 1].set_color(Color::red);
		hexes[hexes.size() - 1].set_fill_color(Color::yellow);
		hexes[hexes.size() - 1].set_style(Line_style{ Line_style::solid, 2 });
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