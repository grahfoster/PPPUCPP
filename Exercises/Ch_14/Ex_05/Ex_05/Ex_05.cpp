#include "../Graph.h"
#include "../Simple_window.h"

namespace Graph_lib {

class Striped_rectangle : public Rectangle {
public:
	using Rectangle::Rectangle;

	void draw_lines() const override;
};

void Striped_rectangle::draw_lines() const
{
	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		for (int i = 0; i < height(); i += 2)
			fl_line(point(0).x, point(0).y + i, point(0).x + width() - 1, point(0).y + i);
		fl_color(color().as_int());
	}

	if (color().visibility()) {
		fl_color(color().as_int());
		fl_rect(point(0).x, point(0).y, width(), height());
	}
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

	Striped_rectangle s_rect{ { 100, 100 }, 200, 100 };
	s_rect.set_color(Color::black);
	s_rect.set_fill_color(Color::blue);

	s_win.attach(s_rect);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}