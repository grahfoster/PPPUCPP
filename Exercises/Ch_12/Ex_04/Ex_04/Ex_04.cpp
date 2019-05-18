#include "../Graph.h"
#include "../Simple_window.h"

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 4, y_max() / 4 };
	const int win_width = y_max() / 2;
	const int win_height = win_width;
	const string win_name{ "My window" };
	Simple_window s_win{ win_tl, win_width, win_height, win_name };

	const int num_columns = 3;
	const int rect_width = s_win.x_max() / num_columns;

	vector<Graph_lib::Rectangle*> rects;
	for (int i = 0, j = 0; i < num_columns * num_columns; ++i) {
		if (i > 0 && i % num_columns == 0)
			++j;

		Graph_lib::Rectangle * rect = new Graph_lib::Rectangle{
			Point {rect_width * (i % num_columns), rect_width * j }, rect_width,
			rect_width };
		rect->set_fill_color(i % 2 == 0 ? Color::white : Color::red);

		rects.push_back(rect);
	}

	for (Graph_lib::Rectangle* rect : rects)
		s_win.attach(*rect);

	s_win.wait_for_button();

	for (Graph_lib::Rectangle* rect : rects)
		delete rect;
	rects.clear();
}
catch (exception & e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}