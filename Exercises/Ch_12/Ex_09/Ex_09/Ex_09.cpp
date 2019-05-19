#include "../Graph.h"
#include "../Simple_window.h"

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 4, y_max() / 4 };
	const int win_width = x_max() / 2;
	const int win_height = y_max() / 2;
	const string win_name{ "Grendel" };
	Simple_window s_win{ win_tl, win_width, win_height, win_name };

	Image image{ Point{ 0, 0 }, "grendel.jpg" };
	image.set_mask(Point{ 144, 48 }, s_win.x_max(), s_win.y_max() * 7 / 8);

	Text caption{ Point{ 24, s_win.y_max() * 61 / 64 },
		"An illustration of Grendel by J. R. Skelton from Stories of Beowulf." };
	caption.set_color(Color::black);
	caption.set_font(Font::helvetica_italic);
	caption.set_font_size(16);

	s_win.attach(image);
	s_win.attach(caption);

	s_win.wait_for_button();
}
catch (exception & e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}