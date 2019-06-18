#include "../Graph.h"
#include "../GUI.h"
#include "../Window.h"

namespace Graph_lib {

class Circle_window : Window {
public:
	Circle_window(Point, int, int, const string&);

	void wait_for_button();
private:
	bool next_button_pushed;
	Button next_button;
	Button quit_button;
	Circle circ;

	void next();
	void quit() { hide(); }
};

Circle_window::Circle_window(Point tl, int width, int height, const string& label) :
	Window{ tl, width, height, label }, next_button_pushed{ false },
	next_button{ { x_max() * 18 / 20, 0 }, x_max() / 20, y_max() / 20, "Next",
		[](Address, Address addr) { reference_to<Circle_window>(addr).next(); } },
	quit_button{ { x_max() * 19 / 20, 0 }, x_max() / 20, y_max() / 20, "Quit",
		[](Address, Address addr) { reference_to<Circle_window>(addr).quit(); } },
	circ{ { width / 2, height / 2 }, 100 }
{
	attach(next_button);
	attach(quit_button);
	circ.set_color(Color::black);
	attach(circ);
}

void Circle_window::wait_for_button()
{
	while (!next_button_pushed)
		Fl::wait();
	next_button_pushed = false;
	Fl::redraw();
}

void Circle_window::next()
{
	cout << "Enter new coordinates:\n";

	int x;
	int y;
	cin >> x >> y;
	if (!cin && !cin.eof())
		throw exception("next() - invalid input");

	circ.move(x - circ.point(0).x, y - circ.point(0).y);
	redraw();
	next_button_pushed = true;
}
}

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 8, y_max() / 8 };
	const int win_width = x_max() * 3 / 4;
	const int win_height = y_max() * 3 / 4;
	const string win_name{ "My window" };

	Circle_window c_win{ win_tl, win_width, win_height, win_name };

	while (true)
		c_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}