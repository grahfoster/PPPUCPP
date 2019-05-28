#include "../Graph.h"
#include "../Simple_window.h"

const double pi = atan(1) * 4;

namespace Graph_lib {

class Regular_polygon : public Polygon {
public:
	Regular_polygon(Point, int, int);

	Point center() const { return c; }
	int num_sides() const { return n; }
	int radius() const { return r; }
private:
	Point c;
	int n;
	int r;

	void add(Point p) { Polygon::add(p); }
};

Regular_polygon::Regular_polygon(Point center, int num_sides, int radius) :
	c{ center }, n{ num_sides }, r{ radius }
{
	for (int i = 0; i < num_sides; ++i) {
		add({ int(center.x + radius * cos(i * 360 / num_sides * pi / 180)),
		int(center.y - radius * sin(i * 360 / num_sides * pi / 180)) });
	}
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

	Regular_polygon tri{ { 200, 200 }, 3, 100 };
	tri.set_color(Color::black);
	tri.set_fill_color(Color::green);

	Regular_polygon hex{ { 400, 100 }, 6, 50 };
	hex.set_color(Color::blue);

	Regular_polygon dec{ { 600, 200 }, 10, 150 };
	dec.set_color(Color::black);
	dec.set_style(Line_style{ Line_style::dashdotdot, 3 });

	s_win.attach(tri);
	s_win.attach(hex);
	s_win.attach(dec);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}