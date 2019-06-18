#include "../Graph.h"
#include "../GUI.h"
#include "../Window.h"

namespace Graph_lib {

class Img_window : Window {
public:
	Img_window(Point, int, int, const string&);

	void wait_for_button();
private:
	const int img_button_side = 200;

	bool next_button_pushed;
	Button next_button;
	Button quit_button;
	Button img_button;
	Image img;

	void next() { next_button_pushed = true; }
	void quit() { hide(); }
	void move_img();
};

Img_window::Img_window(Point tl, int width, int height, const string& label) :
	Window{ tl, width, height, label }, next_button_pushed{ false },
	next_button{ { x_max() * 18 / 20, 0 }, x_max() / 20, y_max() / 20, "Next",
		[](Address, Address addr) { reference_to<Img_window>(addr).next(); } },
	quit_button{ { x_max() * 19 / 20, 0 }, x_max() / 20, y_max() / 20, "Quit",
		[](Address, Address addr) { reference_to<Img_window>(addr).quit(); } },
	img_button{ { 0, 0 }, img_button_side, img_button_side, "",
		[](Address, Address addr) { reference_to<Img_window>(addr).move_img(); } },
	img{ { 0 , 0 }, "Cyan_Hammer.jpg" }
{
	attach(next_button);
	attach(quit_button);
	attach(img_button);
	attach(img);
}

void Img_window::wait_for_button()
{
	while (!next_button_pushed)
		Fl::wait();
	next_button_pushed = false;
	Fl::redraw();
}

void Img_window::move_img()
{
	const int dx = rand() % (this->x_max() - img_button_side)  - img_button.loc.x;
	const int dy = rand() % (this->y_max() - img_button_side) - img_button.loc.y;
	img_button.move(dx, dy);
	img.move(dx, dy);
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

	Img_window i_win{ win_tl, win_width, win_height, win_name };

	i_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}