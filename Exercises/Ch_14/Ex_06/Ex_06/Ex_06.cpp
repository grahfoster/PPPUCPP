#include "../Graph.h"
#include "../Simple_window.h"

namespace Graph_lib {

class Striped_circle : public Circle {
public:
	using Circle::Circle;

	void draw_lines() const override;
};

void Striped_circle::draw_lines() const
{
	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		for (int i = 0; i < radius() * 2; i += 2) {
			double dy = point(0).y + i - center().y;
			double dx = sqrt(1 - dy / radius() * dy / radius()) * radius();
			fl_line(int(center().x - dx), center().y + dy, int(center().x + dx), center().y + dy);
		}
		fl_color(color().as_int());
	}

	if (color().visibility()) {
		fl_color(color().as_int());
		fl_arc(point(0).x, point(0).y, radius() + radius(), radius() + radius(), 0, 360);
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

	Striped_circle s_c{ { 200, 200 }, 100 };
	s_c.set_color(Color::black);
	s_c.set_fill_color(Color::blue);

	s_win.attach(s_c);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}