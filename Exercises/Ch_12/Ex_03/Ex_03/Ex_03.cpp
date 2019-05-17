#include "../Graph.h"
#include "../Simple_window.h"

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 4, y_max() / 4 };
	const int win_width = x_max() / 2;
	const int win_height = y_max() / 2;
	const string win_name{ "My window" };
	Simple_window s_win{ win_tl, win_width, win_height, win_name };

	const int init_height = 150;

	Line g_line1{ Point{ s_win.x_max() / 4, s_win.y_max() / 4 },
		Point{ s_win.x_max() / 4 + init_height / 2, s_win.y_max() / 4 } };
	g_line1.set_style(Line_style(Line_style::solid, 10));
	g_line1.set_color(Color::red);

	Line g_line2{ g_line1.point(0),
		Point{ s_win.x_max() / 4, s_win.y_max() / 4 + init_height } };
	g_line2.set_style(Line_style(Line_style::solid, 10));
	g_line2.set_color(Color::red);

	Line g_line3{ g_line2.point(1),
		Point{ g_line2.point(1).x + init_height / 2, g_line2.point(1).y } };
	g_line3.set_style(Line_style(Line_style::solid, 10));
	g_line3.set_color(Color::red);

	Line g_line4{ g_line3.point(1),
		Point{ g_line3.point(1).x, g_line3.point(1).y - init_height / 2 } };
	g_line4.set_style(Line_style(Line_style::solid, 10));
	g_line4.set_color(Color::red);

	Line g_line5{ g_line4.point(1),
		Point{ g_line4.point(1).x - init_height / 4, g_line4.point(1).y } };
	g_line5.set_style(Line_style(Line_style::solid, 10));
	g_line5.set_color(Color::red);

	Graph_lib::Rectangle r_rect{ Point{ s_win.x_max() / 2, s_win.y_max() / 4 },
		init_height / 2, init_height / 2 };
	r_rect.set_style(Line_style(Line_style::solid, 10));
	r_rect.set_color(Color::green);

	Line r_line1{ Point {r_rect.point(0).x, r_rect.point(0).y + init_height / 2 },
		Point{ r_rect.point(0).x, r_rect.point(0).y + init_height } };
	r_line1.set_style(Line_style(Line_style::solid, 10));
	r_line1.set_color(Color::green);

	Line r_line2{ r_line1.point(0),
		Point{ r_line1.point(0).x + init_height / 2, r_line1.point(1).y } };
	r_line2.set_style(Line_style(Line_style::solid, 10));
	r_line2.set_color(Color::green);

	Line f_line1{ Point{ 3 * s_win.x_max() / 4, s_win.y_max() / 4 },
		Point{ 3 * s_win.x_max() / 4 + init_height / 2, s_win.y_max() / 4 } };
	f_line1.set_style(Line_style(Line_style::solid, 10));
	f_line1.set_color(Color::blue);

	Line f_line2{ f_line1.point(0),
		Point{ 3 * s_win.x_max() / 4, s_win.y_max() / 4 + init_height } };
	f_line2.set_style(Line_style(Line_style::solid, 10));
	f_line2.set_color(Color::blue);

	Line f_line3{ Point{ f_line1.point(0).x, f_line1.point(0).y + init_height / 2 },
		Point{ f_line1.point(0).x + init_height / 2, f_line1.point(0).y + init_height / 2 } };
	f_line3.set_style(Line_style(Line_style::solid, 10));
	f_line3.set_color(Color::blue);

	s_win.attach(g_line1);
	s_win.attach(g_line2);
	s_win.attach(g_line3);
	s_win.attach(g_line4);
	s_win.attach(g_line5);
	s_win.attach(r_rect);
	s_win.attach(r_line1);
	s_win.attach(r_line2);
	s_win.attach(f_line1);
	s_win.attach(f_line2);
	s_win.attach(f_line3);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}