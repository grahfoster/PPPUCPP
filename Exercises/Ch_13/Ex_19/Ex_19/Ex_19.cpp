#include "../Graph.h"
#include "../Simple_window.h"

const double pi = atan(1) * 4;

namespace Graph_lib {

class Star : public Closed_polyline {
public:
	Star(Point, int, int, int);

	Point center() const { return c; }
	int radius1() const { return r1; }
	int radius2() const { return r2; }
	int num_points() const { return n; }
private:
	Point c;
	int r1;
	int r2;
	int n;
};

Star::Star(Point center, int radius1, int radius2, int num_points) :
	c{ center }, r1{ radius1 }, r2{ radius2 }, n{ num_points }
{
	if (n <= 1)
		error("too few sides on star");

	for (int i = 0; i < num_points; ++i) {
		add({ int(center.x + radius1 * cos(i * 360 / num_points * pi / 180)),
		int(center.y - radius1 * sin(i * 360 / num_points * pi / 180)) });
		add({ int(center.x + radius2 * cos((i + .5) * 360 / num_points * pi / 180)),
		int(center.y - radius2 * sin((i + .5) * 360 / num_points * pi / 180)) });
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

	Star star1{ { 200, 200 }, 50, 100, 5 };
	star1.set_color(Color::black);
	star1.set_fill_color(Color::green);

	Star star2{ { 500, 300 }, 70, 100, 6 };
	star2.set_color(Color::blue);

	Star star3{ { 100, 400 }, 25, 100, 9 };
	star3.set_color(Color::red);
	star3.set_fill_color(Color::yellow);

	s_win.attach(star1);
	s_win.attach(star2);
	s_win.attach(star3);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}