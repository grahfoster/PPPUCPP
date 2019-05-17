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

	const Point rect_tl{ s_win.x_max() / 4, s_win.y_max() / 4 };
	const int rect_width = 100;
	const int rect_height = 30;
	Graph_lib::Rectangle rect{ rect_tl, rect_width, rect_height };
	rect.set_color(Color::black);

	const string greeting{ "Howdy!" };
	Text text{ Point{ rect_tl.x + rect_width / 4, rect_tl.y + rect_height / 2 }, greeting };
	text.set_color(Color::black);

	s_win.attach(rect);
	s_win.attach(text);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}