#include "../Graph.h"
#include "../Simple_window.h"

namespace Graph_lib {

class Arc : public Ellipse {
public:
	Arc(Point p, int w, int h, int a1, int a2) : a1{ a1 }, a2{ a2 }, Ellipse{ p, w, h } {}

	void draw_lines() const;
private:
	int a1;
	int a2;
};

void Arc::draw_lines() const
{
	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		fl_pie(point(0).x, point(0).y, major() + major(), minor() + minor(), a1, a2);
		fl_color(color().as_int());
	}

	if (color().visibility()) {
		fl_color(color().as_int());
		fl_arc(point(0).x, point(0).y, major() + major(), minor() + minor(), a1, a2);
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

	Graph_lib::Arc arc1{ { 100, 100}, 50, 75, 180, 270 };
	arc1.set_color(Color::black);
	arc1.set_fill_color(Color::green);

	Graph_lib::Arc arc2{ { 300, 300}, 100, 100, 10, 350 };
	arc2.set_color(Color::blue);

	s_win.attach(arc1);
	s_win.attach(arc2);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}