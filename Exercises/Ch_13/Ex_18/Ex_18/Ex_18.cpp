#include "../Graph.h"
#include "../Simple_window.h"

namespace Graph_lib {

class Poly : public Polygon {
public:
	Poly(initializer_list<Point>);
};

Poly::Poly(initializer_list<Point> lst)
{
	for (Point p : lst)
		add(p);
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

	Poly tri{ { 100, 100 }, { 200, 100 }, { 100, 200 } };
	tri.set_color(Color::black);

	Poly sqr{ { 300, 100 }, { 400, 100 }, { 400, 200 }, { 300, 200 } };
	sqr.set_color(Color::blue);

	s_win.attach(tri);
	s_win.attach(sqr);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}