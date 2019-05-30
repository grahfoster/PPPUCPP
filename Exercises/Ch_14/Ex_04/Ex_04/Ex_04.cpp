#include "../Graph.h"
#include "../Simple_window.h"

namespace Graph_lib {

class Immobile_circle : public Circle {
public:
	using Circle::Circle;

	void move(int, int) override {}
};
}

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 4, y_max() / 4 };
	const int win_width = x_max() / 2;
	const int win_height = y_max() / 2;
	const string win_name{ "My window" };
	Simple_window s_win{ win_tl, win_width, win_height, win_name };

	Immobile_circle i_c{ { 100, 100 }, 50 };
	i_c.set_color(Color::black);
	i_c.move(100, 100);

	s_win.attach(i_c);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}