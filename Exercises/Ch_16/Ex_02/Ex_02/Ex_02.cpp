#include "../Graph.h"
#include "../GUI.h"
#include "../Window.h"

namespace Graph_lib {

class Checker_window : Window {
public:
	Checker_window(Point, int, int, const string&);
	~Checker_window();

	void wait_for_button();
private:
	const int num_rows = 4;

	vector<Button*> checker_buttons;
	Rectangle tile;
	bool next_button_pushed;
	Button next_button;
	Button quit_button;

	void move_tile(int, int);
	void next() { next_button_pushed = true; }
	void quit() { hide(); }
};

Checker_window::Checker_window(Point tl, int width, int height, const string& label) :
	Window{ tl, width, height, label }, next_button_pushed{ false },
	tile{ { 0, 0 }, height / num_rows, height / num_rows },
	next_button{ { x_max() * 18 / 20, 0 }, x_max() / 20, y_max() / 20, "Next",
		[](Address, Address addr) { reference_to<Checker_window>(addr).next(); } },
	quit_button{ { x_max() * 19 / 20, 0 }, x_max() / 20, y_max() / 20, "Quit",
		[](Address, Address addr) { reference_to<Checker_window>(addr).quit(); } }
{
	tile.set_color(Color::invisible);
	attach(tile);

	const int num_rows = 4;
	const int checker_side = height / num_rows;

	for (int i = 0; i < num_rows; ++i)
		for (int j = 0; j < num_rows; ++j) {
			checker_buttons.push_back(new Button{ { j * checker_side, i * checker_side }, checker_side,
				checker_side, "",
				[](Address addr1, Address addr2) {
					reference_to<Checker_window>(addr2).move_tile(reference_to<Fl_Widget>(addr1).x(),
						reference_to<Fl_Widget>(addr1).y());
				} });
			attach(*checker_buttons.back());
		}

	attach(next_button);
	attach(quit_button);
}

Checker_window::~Checker_window()
{
	for (Button* checker_button : checker_buttons)
		delete checker_button;
}

void Checker_window::wait_for_button()
{
	while (!next_button_pushed)
		Fl::wait();
	next_button_pushed = false;
	Fl::redraw();
}

void Checker_window::move_tile(int dx, int dy)
{
	tile.set_fill_color(Color::green);
	tile.move(-tile.point(0).x, -tile.point(0).y);
	tile.move(dx, dy);
	redraw();
}
}

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 8, y_max() / 8 };
	const int win_width = x_max() * 3 / 4;
	const int win_height = y_max() * 3 / 4;
	const string win_name{ "My window" };

	Checker_window c_win{ win_tl, win_width, win_height, win_name };

	c_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}