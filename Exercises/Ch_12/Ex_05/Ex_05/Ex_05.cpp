#include "../Graph.h"
#include "../Simple_window.h"

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 12, y_max() / 16 };
	const int win_width = x_max() * 5 / 6;
	const int win_height = y_max() * 7 / 8;
	const string win_name{ "My window" };
	Simple_window s_win{ win_tl, win_width, win_height, win_name };

	const int qrtr_inch_pixels = 24;

	Graph_lib::Rectangle rect{ Point{ s_win.x_max() / 12 - qrtr_inch_pixels / 2,
		s_win.y_max() / 16 - qrtr_inch_pixels / 2 },
		x_max() * 2 / 3 + qrtr_inch_pixels, y_max() * 3 / 4 + qrtr_inch_pixels };
	rect.set_color(Color::red);
	rect.set_style(Line_style(Line_style::solid, qrtr_inch_pixels));

	s_win.attach(rect);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}