#include "../Graph.h"
#include "../GUI.h"
#include "../Window.h"

namespace Graph_lib {

class Graphing_window : Window {
public:
	Graphing_window(Point, int, int, const string&);
	~Graphing_window() { delete function; }

	void wait_for_button();
private:
	bool next_button_pushed = false;
	Button next_button;
	Button quit_button;
	Axis x_axis;
	Axis y_axis;
	Function* function = 0;
	Menu function_menu;
	In_box min_range_in;
	In_box max_range_in;
	In_box count_in;
	In_box x_scale_in;
	In_box y_scale_in;

	void next() { next_button_pushed = true; }
	void quit() { hide(); }
	void draw_function(Fct);
};

Graphing_window::Graphing_window(Point tl, int width, int height, const string& label) :
	Window{ tl, width, height, label },
	next_button{ { x_max() * 18 / 20, 0 }, x_max() / 20, y_max() / 20, "Next",
		[](Address, Address addr) { reference_to<Graphing_window>(addr).next(); } },
	quit_button{ { x_max() * 19 / 20, 0 }, x_max() / 20, y_max() / 20, "Quit",
		[](Address, Address addr) { reference_to<Graphing_window>(addr).quit(); } },
	x_axis{ Axis::x, { width * 5 / 16, height / 2 }, width * 5 / 8, 10, "X" },
	y_axis{ Axis::y, { width * 5 / 8, height * 15 / 16 }, height * 7 / 8, 10, "Y" },
	function_menu{ { width / 16, height / 16 }, width / 8, height * 3 / 8 / 5, Menu::vertical, "Function" },
	min_range_in{ { width / 16, height * 9 / 16 }, width / 8, height * 3 / 8 / 5, "Min Range"},
	max_range_in{ { width / 16, height * 9 / 16 + height * 3 / 8 / 5 }, width / 8, height * 3 / 8 / 5, "Max Range" },
	count_in{ { width / 16, height * 9 / 16 + height * 3 / 8 * 2 / 5 }, width / 8, height * 3 / 8 / 5, "Count" },
	x_scale_in{ { width / 16, height * 9 / 16 + height * 3 / 8 * 3 / 5 }, width / 8, height * 3 / 8 / 5, "X Scale" },
	y_scale_in{ { width / 16, height * 9 / 16 + height * 3 / 8 * 4 / 5 }, width / 8, height * 3 / 8 / 5, "Y Scale" }
{
	attach(next_button);
	attach(quit_button);
	x_axis.set_color(Color::black);
	x_axis.label.move(x_axis.point(0).x - width * 5 / 8 / 3, 0);
	attach(x_axis);
	y_axis.set_color(Color::black);
	attach(y_axis);
	function_menu.attach(new Button{ { 0, 0 }, 0, 0, "Sine",
		[](Address, Address addr) { reference_to<Graphing_window>(addr).draw_function(sin); } });
	function_menu.attach(new Button{ { 0, 0 }, 0, 0, "Cosine",
		[](Address, Address addr) { reference_to<Graphing_window>(addr).draw_function(cos); } });
	function_menu.attach(new Button{ { 0, 0 }, 0, 0, "Tangent",
		[](Address, Address addr) { reference_to<Graphing_window>(addr).draw_function(tan); } });
	function_menu.attach(new Button{ { 0, 0 }, 0, 0, "Exponent",
		[](Address, Address addr) { reference_to<Graphing_window>(addr).draw_function(exp); } });
	function_menu.attach(new Button{ { 0, 0 }, 0, 0, "Logarithm",
		[](Address, Address addr) { reference_to<Graphing_window>(addr).draw_function(log); } });
	attach(function_menu);
	attach(min_range_in);
	attach(max_range_in);
	attach(count_in);
	attach(x_scale_in);
	attach(y_scale_in);
}

void Graphing_window::wait_for_button()
{
	while (!next_button_pushed)
		Fl::wait();
	next_button_pushed = false;
	Fl::redraw();
}

void Graphing_window::draw_function(Fct fct)
{
	const Point origin{ this->x_max() * 5 / 8, this->y_max() / 2 };
	const double min_range = min_range_in.get_string().empty() ? 
		-(x_axis.point(1).x - x_axis.point(0).x) / 2 / 25 : stod(min_range_in.get_string());
	const double max_range = max_range_in.get_string().empty() ?
		(x_axis.point(1).x - x_axis.point(0).x) / 2 / 25 : stod(max_range_in.get_string());
	const int count = count_in.get_string().empty() ? 100 : stoi(count_in.get_string());
	const double x_scale = x_scale_in.get_string().empty() ? 25 : stod(x_scale_in.get_string());
	const double y_scale = y_scale_in.get_string().empty() ? 25 : stod(y_scale_in.get_string());

	detach(*function);
	delete function;
	function = new Function{ fct, min_range, max_range, origin, count, x_scale, y_scale };
	function->set_color(Color::blue);
	attach(*function);
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

	Graphing_window g_win{ win_tl, win_width, win_height, win_name };

	g_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}