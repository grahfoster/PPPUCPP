#include "../Graph.h"
#include "../GUI.h"
#include "../Window.h"
#include <chrono>
#include <thread>

namespace Graph_lib {

class Airplane_window : Window {
public:
	Airplane_window(Point, int, int, const string&);

	void wait_for_button();
	void fly();
private:
	const int img_side = 200;

	bool start_button_pushed = false;
	bool next_button_pushed = false;
	int velocity = 1;
	Button start_button;
	Button stop_button;
	Button next_button;
	Button quit_button;
	Image airplane_img;

	void start() { start_button_pushed = true; }
	void stop() { start_button_pushed = false; };
	void next() { next_button_pushed = true; }
	void quit() { hide(); }
};

Airplane_window::Airplane_window(Point tl, int width, int height, const string& label) :
	Window{ tl, width, height, label },
	start_button{ { x_max() * 16 / 20, 0 }, x_max() / 20, y_max() / 20, "Start",
		[](Address, Address addr) { reference_to<Airplane_window>(addr).start(); } },
	stop_button{ { x_max() * 17 / 20, 0 }, x_max() / 20, y_max() / 20, "Stop",
		[](Address, Address addr) { reference_to<Airplane_window>(addr).stop(); } },
	next_button{ { x_max() * 18 / 20, 0 }, x_max() / 20, y_max() / 20, "Next",
		[](Address, Address addr) { reference_to<Airplane_window>(addr).next(); } },
	quit_button{ { x_max() * 19 / 20, 0 }, x_max() / 20, y_max() / 20, "Quit",
		[](Address, Address addr) { reference_to<Airplane_window>(addr).quit(); } },
	airplane_img{ { (width - img_side) / 2, (height - img_side) / 2 }, "Airplane.jpg" }
{
	attach(start_button);
	attach(stop_button);
	attach(next_button);
	attach(quit_button);
	attach(airplane_img);
}

void Airplane_window::wait_for_button()
{
	while (!next_button_pushed) {
		Fl::wait();
		if (start_button_pushed)
			fly();
	}
	next_button_pushed = false;
	Fl::redraw();
}

void Airplane_window::fly()
{
	if (airplane_img.point(0).x + img_side >= this->x_max())
		velocity = -1;
	if (airplane_img.point(0).x <= 0)
		velocity = 1;
	airplane_img.move(velocity, 0);
	redraw();
	this_thread::sleep_for(chrono::milliseconds(1));
}
}

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 8, y_max() / 8 };
	const int win_width = x_max() * 3 / 4;
	const int win_height = y_max() * 3 / 4;
	const string win_name{ "My window" };

	Airplane_window a_win{ win_tl, win_width, win_height, win_name };

	a_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}