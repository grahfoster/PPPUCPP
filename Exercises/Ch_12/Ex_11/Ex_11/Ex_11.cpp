#include "../Graph.h"
#include "../Simple_window.h"

double to_radians(int degrees) { return degrees * atan(1) * 4 / 180; }

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 4, y_max() / 4 };
	const int win_width = x_max() / 4;
	const string win_name{ "My window" };
	Simple_window s_win{ win_tl, win_width, win_width, win_name };

	const int hex_width = s_win.x_max() * cos(to_radians(30));
	const int hex_side = hex_width / 2 / sin(to_radians(60));
	Graph_lib::Polygon hex;
	hex.add(Point{ s_win.x_max() / 2, 0 });
	hex.add(Point{ hex.point(0).x + hex_width / 2,
		int(tan(to_radians(30)) * hex_width / 2) });
	hex.add(Point{ hex.point(1).x, hex.point(1).y + hex_side });
	hex.add(Point{ hex.point(0).x, s_win.y_max() });
	hex.add(Point{ hex.point(0).x - hex_width / 2, hex.point(2).y });
	hex.add(Point{ hex.point(4).x, hex.point(1).y });
	hex.set_color(Color::dark_red);

	const int pnt_side = s_win.x_max() * sin(to_radians(36));
	Graph_lib::Polygon pnt;
	pnt.add(hex.point(0));
	pnt.add(Point{ pnt.point(0).x + hex_width / 2,
		int(tan(to_radians(36)) * hex_width / 2) });
	pnt.add(Point{ pnt.point(0).x + pnt_side / 2,
		int(pnt.point(1).y + pnt_side * cos(to_radians(30))) });
	pnt.add(Point{ pnt.point(0).x - pnt_side / 2, pnt.point(2).y });
	pnt.add(Point{ pnt.point(0).x - hex_width / 2, pnt.point(1).y });
	pnt.set_color(Color::dark_green);

	Graph_lib::Polygon sqr;
	sqr.add(Point{ pnt.point(3).x, pnt.point(3).y - pnt_side });
	sqr.add(Point{ pnt.point(2).x, pnt.point(3).y - pnt_side });
	sqr.add(pnt.point(2));
	sqr.add(pnt.point(3));
	sqr.set_color(Color::dark_blue);

	const int tri_height = pnt_side / 2 / tan(to_radians(30));
	Graph_lib::Polygon tri;
	tri.add(Point{ sqr.point(0).x + pnt_side / 2, sqr.point(0).y });
	tri.add(Point{ sqr.point(1).x, tri.point(0).y + tri_height});
	tri.add(Point{ sqr.point(0).x, tri.point(0).y + tri_height });
	tri.set_color(Color::dark_yellow);

	s_win.attach(hex);
	s_win.attach(pnt);
	s_win.attach(sqr);
	s_win.attach(tri);

	s_win.wait_for_button();
}
catch (exception & e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}