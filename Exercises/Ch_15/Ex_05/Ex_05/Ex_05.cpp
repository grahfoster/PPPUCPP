#include "../Graph.h"
#include "../Simple_window.h"
#include <functional>

namespace Graph_lib {

using Fctn = function<double(double)>;

struct Funct : Shape {
	// the function parameters are not stored
	Funct(Fctn f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25);
	//Function(Point orig, Fct f, double r1, double r2, int count, double xscale = 1, double yscale = 1);	
};

Funct::Funct(Fctn f, double r1, double r2, Point xy, int count, double xscale, double yscale)
// graph f(x) for x in [r1:r2) using count line segments with (0,0) displayed at xy
// x coordinates are scaled by xscale and y coordinates scaled by yscale
{
	if (r2 - r1 <= 0) error("bad graphing range");
	if (count <= 0) error("non-positive graphing count");
	double dist = (r2 - r1) / count;
	double r = r1;
	for (int i = 0; i < count; ++i) {
		add(Point(xy.x + int(r * xscale), xy.y - int(f(r) * yscale)));
		r += dist;
	}
}

double fct(int n) {
	double sum = 0;
	for (int i = 0; i < n; ++i)
		sum += i % 2 == 0 ? 1 / (i * 2.0 + 1.0) : -1 / (i * 2.0 + 1.0);
	return sum;
}
}

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 8, y_max() / 8 };
	const int win_width = x_max() * 3 / 4;
	const int win_height = y_max() * 3 / 4;
	const string win_name{ "My window" };
	Simple_window s_win{ win_tl, win_width, win_height, win_name };

	const Point origin{ s_win.x_max() / 2, s_win.y_max() / 2 };
	const Point x_origin{ s_win.x_max() / 8, origin.y };
	const Point y_origin{ origin.x, s_win.y_max() * 7 / 8 };
	const int x_length = s_win.x_max() * 3 / 4;
	const int y_length = s_win.y_max() * 3 / 4;
	const double x_scale = 50;
	const double y_scale = 50;
	const int x_notches = x_length / x_scale;
	const int y_notches = y_length / y_scale;
	const string x_label{ "x" };
	const string y_label{ "y" };

	Axis x_axis{ Axis::Orientation::x, x_origin, x_length, x_notches, x_label };
	x_axis.label.move(x_origin.x - x_length / 3 - 25, 0);
	x_axis.set_color(Color::black);

	Axis y_axis{ Axis::Orientation::y, y_origin, y_length, y_notches, y_label };
	y_axis.set_color(Color::black);

	const double range_min = -x_length / x_scale / 2;
	const double range_max = -range_min;
	const int count = 100;

	s_win.attach(x_axis);
	s_win.attach(y_axis);

	for (int i = 0; i < 10; ++i) {
		Funct funct{ [i](double x) { return fct(i); }, range_min, range_max, origin, count, x_scale, y_scale };
		funct.set_color(Color::black);
		s_win.attach(funct);
		s_win.wait_for_button();
		s_win.detach(funct);
	}
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}