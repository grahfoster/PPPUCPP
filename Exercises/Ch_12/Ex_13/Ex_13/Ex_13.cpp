#include "../Graph.h"
#include "../Simple_window.h"

const double pi = atan(1) * 4;

void set_points(vector<Point>&, Point, double, double, double, double);

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 4, y_max() / 4 };
	const int win_width = x_max() / 4;
	const string win_name{ "My window" };
	Simple_window s_win{ win_tl, win_width, win_width, win_name };

	vector<Point> points;
	const Point origin{ s_win.x_max() / 2, s_win.y_max() / 2 };
	const double a = 1;
	const double b = 1;
	const double m = 0.5;
	const double n = 0.5;
	set_points(points, origin, a, b, m, n);

	Open_polyline superellipse;
	for (Point point : points)
		superellipse.add(point);
	superellipse.set_color(Color::black);

	const int N = 25;
	const int increment = 1 + points.size() / N;
	const int num_colors = 14;
	vector<Line*> lines;
	for (int i = 0; i < N; ++i) {
		Line* line = new Line{ points[i * increment % points.size()], points[0] };
		line->set_color(Color(i % num_colors));
		lines.push_back(line);
	}

	s_win.attach(superellipse);
	for (Line* line : lines)
		s_win.attach(*line);

	s_win.wait_for_button();

	for (Line* line : lines)
		delete line;
	lines.clear();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}

int sign(double d)
{
	if (d < 0)
		return -1;
	if (d == 0)
		return 0;
	return 1;
}

void set_points(vector<Point>& points, Point origin, double a, double b, double m, double n)
{
	Point point;
	const double increment = 0.01;
	for (double d = -1; d < 1; d += increment) {
		double t = d * pi;
		double x = pow((abs(cos(t))), 2 / m) * a * sign(cos(t));
		double y = pow((abs(sin(t))), 2 / n) * b * sign(sin(t));
		point = Point{ origin.x + int(x * origin.x), origin.y + int(y * origin.y) };

		bool duplicate = false;
		for (Point temp : points)
			if (point == temp)
				duplicate = true;
		if (!duplicate)
			points.push_back(point);
	}
}