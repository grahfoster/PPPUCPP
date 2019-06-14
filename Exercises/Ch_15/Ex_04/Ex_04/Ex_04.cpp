#include "../Graph.h"
#include "../Simple_window.h"

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

	Function fctn1{ sin, range_min, range_max, origin, count, x_scale, y_scale };
	fctn1.set_color(Color::dark_red);

	Function fctn2{ cos, range_min, range_max, origin, count, x_scale, y_scale };
	fctn2.set_color(Color::dark_green);

	Function fctn3{ [](double x) { return sin(x) + cos(x); }, range_min, range_max, origin, count, x_scale, 
		y_scale };
	fctn3.set_color(Color::dark_blue);

	Function fctn4{ [](double x) { return sin(x) * sin(x) + cos(x) * cos(x); }, range_min, range_max, origin,
		count, x_scale,	y_scale };
	fctn4.set_color(Color::dark_yellow);

	s_win.attach(x_axis);
	s_win.attach(y_axis);
	s_win.attach(fctn1);
	s_win.attach(fctn2);
	s_win.attach(fctn3);
	s_win.attach(fctn4);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}