#include "../Graph.h"
#include "../GUI.h"
#include "../Window.h"

namespace Graph_lib {

class My_window : Window {
public:
	My_window(Point, int, int, const string&);

	void wait_for_button();
private:
	bool next_button_pushed;
	Button next_button;
	Button quit_button;

	void next() { next_button_pushed = true; }
	void quit() { hide(); }
};

My_window::My_window(Point tl, int width, int height, const string& label) :
	Window{ tl, width, height, label }, next_button_pushed{ false },
	next_button{ { x_max() * 18 / 20, 0 }, x_max() / 20, y_max() / 20, "Next",
		[](Address, Address addr) { reference_to<My_window>(addr).next(); } },
	quit_button{ { x_max() * 19 / 20, 0 }, x_max() / 20, y_max() / 20, "Quit",
		[](Address, Address addr) { reference_to<My_window>(addr).quit(); } }
{
	attach(next_button);
	attach(quit_button);
}

void My_window::wait_for_button()
{
	while (!next_button_pushed)
		Fl::wait();
	next_button_pushed = false;
	Fl::redraw();
}
}

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 8, y_max() / 8 };
	const int win_width = x_max() * 3 / 4;
	const int win_height = y_max() * 3 / 4;
	const string win_name{ "My window" };

	My_window m_win{ win_tl, win_width, win_height, win_name };

	m_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}