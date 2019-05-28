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

	const int num_rows = 16;
	const int rect_width = s_win.y_max() / num_rows;

	Vector_ref<Graph_lib::Rectangle> rects;
	for (int i = 0; i < num_rows; ++i)
		for (int j = 0; j < num_rows; ++j) {
			rects.push_back(new Graph_lib::Rectangle{ { i * rect_width, j * rect_width }, rect_width,
				rect_width });
			rects[rects.size() - 1].set_color(Color::Transparency::invisible);
			rects[rects.size() - 1].set_fill_color(i * num_rows + j);
			s_win.attach(rects[rects.size() - 1]);
		}

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}