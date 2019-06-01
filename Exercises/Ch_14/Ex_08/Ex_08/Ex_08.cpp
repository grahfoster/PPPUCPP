#include "../Graph.h"
#include "../Simple_window.h"

const double pi = atan(1) * 4;

namespace Graph_lib {

class Octagon : public Polygon {
public:
	Octagon(Point, int);

	Point center() const { return { point(0).x - r, point(0).y }; }
	int radius() const { return r; }
private:
	int r;

	void add(Point p) { Polygon::add(p); }
};

Octagon::Octagon(Point center, int radius) :
	r{ radius }
{
	const int num_sides = 8;

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

	Octagon oct{ { 200, 200 }, 100 };
	oct.set_color(Color::black);
	oct.set_fill_color(Color::blue);
	oct.set_style(Line_style{ Line_style::dashdotdot, 2 });
	oct.move(100, 200);
	cout << "Center: (" << oct.center().x << ", " << oct.center().y << ")\n";

	s_win.attach(oct);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}