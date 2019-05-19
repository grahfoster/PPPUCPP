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

	const int roof_width = s_win.x_max() / 2;
	const int roof_height = s_win.y_max() / 4;
	Graph_lib::Polygon roof;
	roof.add(Point{ s_win.x_max() / 4, s_win.y_max() / 2 });
	roof.add(Point{ roof.point(0).x + roof_width / 2,
		roof.point(0).y - roof_height });
	roof.add(Point{ roof.point(0).x + roof_width, roof.point(0).y });
	roof.set_color(Color::black);
	roof.set_fill_color(Color::red);

	const int base_offset = 48;
	const int base_width = roof_width - base_offset * 2;
	const int base_height = s_win.y_max() / 2;
	Graph_lib::Rectangle base{ Point{ roof.point(0).x + base_offset,
		roof.point(0).y }, base_width, base_height };
	base.set_color(Color::black);
	base.set_fill_color(Color::blue);

	const int door_width = base_width / 4;
	const int door_height = base_height / 2;
	Graph_lib::Rectangle door{
		Point{ base.point(0).x + base_width * 3 / 8,
		roof.point(0).y + base_height / 2}, door_width, door_height };
	door.set_color(Color::black);
	door.set_fill_color(Color::yellow);

	const int knob_radius = 5;
	Circle knob{ Point{ door.point(0).x + door_width * 3 / 4,
		door.point(0).y + door_height / 2 }, knob_radius };
	knob.set_color(Color::black);

	const int chimney_width = roof_width / 8;
	const int chimney_height = roof_height / 2;
	Graph_lib::Polygon chimney;
	chimney.add(Point{ roof.point(0).x + roof_width * 3 / 16,
		roof.point(0).y - roof_height / 3 });
	chimney.add(Point{ chimney.point(0).x,
		chimney.point(0).y - chimney_height });
	chimney.add(Point{ chimney.point(1).x + chimney_width,
		chimney.point(1).y });
	chimney.add(Point{ chimney.point(2).x,
		chimney.point(2).y + roof_height / 4 });
	chimney.set_color(Color::black);
	chimney.set_fill_color(Color::black);

	const int window_width = base_width / 4;

	Graph_lib::Rectangle window1{ Point{ base.point(0).x + base_width / 16,
		base.point(0).y + base_height / 8 }, window_width, window_width };
	window1.set_color(Color::black);
	window1.set_fill_color(Color::white);

	Graph_lib::Rectangle window2{ Point{ base.point(0).x + base_width * 11 / 16,
		base.point(0).y + base_height / 8 }, window_width, window_width };
	window2.set_color(Color::black);
	window2.set_fill_color(Color::white);

	Line window1_bar1{ Point{ window1.point(0).x + window_width / 2,
		window1.point(0).y}, Point{ window1.point(0).x + window_width / 2,
		window1.point(0).y + window_width} };
	window1_bar1.set_color(Color::black);

	Line window1_bar2{ Point{ window1.point(0).x,
		window1.point(0).y + window_width / 2},
		Point{ window1.point(0).x + window_width,
		window1.point(0).y + window_width / 2} };
	window1_bar2.set_color(Color::black);

	Line window2_bar1{ Point{ window2.point(0).x + window_width / 2,
		window2.point(0).y}, Point{ window2.point(0).x + window_width / 2,
		window2.point(0).y + window_width} };
	window2_bar1.set_color(Color::black);

	Line window2_bar2{ Point{ window2.point(0).x,
		window2.point(0).y + window_width / 2},
		Point{ window2.point(0).x + window_width,
		window2.point(0).y + window_width / 2} };
	window2_bar2.set_color(Color::black);

	s_win.attach(roof);
	s_win.attach(base);
	s_win.attach(door);
	s_win.attach(knob);
	s_win.attach(chimney);
	s_win.attach(window1);
	s_win.attach(window2);
	s_win.attach(window1_bar1);
	s_win.attach(window1_bar2);
	s_win.attach(window2_bar1);
	s_win.attach(window2_bar2);

	s_win.wait_for_button();
}
catch (exception & e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}