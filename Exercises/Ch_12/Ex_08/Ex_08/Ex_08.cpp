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

	const int ring_radius = s_win.x_max() / 8;

	Circle ring1{ Point{ s_win.x_max() / 5, s_win.y_max() / 3 }, ring_radius };
	ring1.set_style(Line_style{ Line_style::solid, 12 });
	ring1.set_color(Color::blue);

	Circle ring2{ Point{ s_win.x_max() / 2,
		s_win.y_max() / 3 }, ring_radius };
	ring2.set_style(Line_style{ Line_style::solid, 12 });
	ring2.set_color(Color::black);

	Circle ring3{ Point{ s_win.x_max() * 4 / 5,
		s_win.y_max() / 3 }, ring_radius };
	ring3.set_style(Line_style{ Line_style::solid, 12 });
	ring3.set_color(Color::red);

	Circle ring4{ Point{ s_win.x_max() / 5 + ring_radius * 6 / 5,
		s_win.y_max() / 3 + ring_radius }, ring_radius };
	ring4.set_style(Line_style{ Line_style::solid, 12 });
	ring4.set_color(Color::yellow);

	Circle ring5{ Point{ s_win.x_max() / 2 + ring_radius * 6 / 5,
		s_win.y_max() / 3 + ring_radius }, ring_radius };
	ring5.set_style(Line_style{ Line_style::solid, 12 });
	ring5.set_color(Color::green);

	s_win.attach(ring1);
	s_win.attach(ring2);
	s_win.attach(ring3);
	s_win.attach(ring4);
	s_win.attach(ring5);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}