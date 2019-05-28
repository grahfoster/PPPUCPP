#include "../Graph.h"
#include "../Simple_window.h"

const double pi = atan(1) * 4;

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 4, y_max() / 4 };
	const int win_width = x_max() / 2;
	const int win_height = y_max() / 2;
	const string win_name{ "My window" };
	Simple_window s_win{ win_tl, win_width, win_height, win_name };

	Circle circ{ { s_win.x_max() / 2, s_win.y_max() / 2 }, 100 };
	circ.set_color(Color::black);

	Mark mark{ { circ.center().x + circ.radius(), circ.center().y }, 'o' };
	mark.set_color(Color::red);

	s_win.attach(circ);
	s_win.attach(mark);

	for (int i = 0; i < 360; i += 10) {
		Point temp{ int(circ.center().x + circ.radius() * cos(i * pi / 180)),
			int(circ.center().y - circ.radius() * sin(i * pi / 180)) };
		mark.move(temp.x - mark.point(0).x, temp.y - mark.point(0).y);
		s_win.wait_for_button();
	}
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}