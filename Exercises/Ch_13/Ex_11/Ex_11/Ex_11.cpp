#include "../Graph.h"
#include "../Simple_window.h"

const double pi = atan(1) * 4;

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 4, y_max() / 4 };
	const int win_width = x_max() / 2;
	const int win_height = y_max() / 2;
	const string win_name{ "My window" };
	Simple_window s_win{ win_tl, win_width, win_height, win_name };

	const Point origin{ s_win.x_max() / 2, s_win.y_max() / 2 };

	Graph_lib::Ellipse ell{ origin, 150, 100 };
	ell.set_color(Color::black);

	Axis x_axis{ Axis::Orientation::x, { origin.x - 200, origin.y }, 400, 10 };
	x_axis.set_color(Color::black);

	Axis y_axis{ Axis::Orientation::y, { origin.x, origin.y + 150 }, 300, 10 };
	y_axis.set_color(Color::black);

	const int focus_dist = sqrt(ell.major() * ell.major() - ell.minor() * ell.minor());

	Mark focus1{ { origin.x + focus_dist, origin.y }, '1' };
	focus1.set_color(Color::black);

	Mark focus2{ { origin.x - focus_dist, origin.y }, '2' };
	focus2.set_color(Color::black);

	Mark mark{ { int(ell.center().x + ell.major() * cos(45 * pi / 180)),
		int(ell.center().y - ell.minor() * sin(45 * pi / 180)) }, 'o' };
	mark.set_color(Color::black);

	Line line1{ focus1.point(0), mark.point(0) };
	line1.set_color(Color::black);

	Line line2{ focus2.point(0), mark.point(0) };
	line2.set_color(Color::black);

	s_win.attach(ell);
	s_win.attach(x_axis);
	s_win.attach(y_axis);
	s_win.attach(focus1);
	s_win.attach(focus2);
	s_win.attach(mark);
	s_win.attach(line1);
	s_win.attach(line2);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}