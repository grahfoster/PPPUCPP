#include "../Graph.h"
#include "../GUI.h"
#include "../Window.h"

const double pi = atan(1) * 4;

namespace Graph_lib {

class Regular_polygon : public Closed_polyline {
public:
	Regular_polygon(Point, int, int);

	Point center() const { return c; }
	int num_sides() const { return n; }
	int radius() const { return r; }
private:
	Point c;
	int n;
	int r;

	void add(Point p) { Closed_polyline::add(p); }
};

Regular_polygon::Regular_polygon(Point center, int num_sides, int radius) :
	c{ center }, n{ num_sides }, r{ radius }
{
	for (int i = 0; i < num_sides; ++i) {
		add({ center.x + int(radius * cos(i * 360 / num_sides * pi / 180)),
		center.y - int(radius * sin(i * 360 / num_sides * pi / 180)) });
	}
}

class Shape_window : Window {
public:
	Shape_window(Point, int, int, const string&);
	~Shape_window() { delete current_shape; }

	void wait_for_button();
private:
	bool next_button_pushed;
	Button next_button;
	Button quit_button;
	Menu shape_menu;
	Regular_polygon* current_shape;
	In_box x_in;
	In_box y_in;

	void next() { next_button_pushed = true; }
	void quit() { hide(); }
	void draw_shape(int);
};

Shape_window::Shape_window(Point tl, int width, int height, const string& label) :
	Window{ tl, width, height, label }, next_button_pushed{ false },
	next_button{ { x_max() * 18 / 20, 0 }, x_max() / 20, y_max() / 20, "Next",
		[](Address, Address addr) { reference_to<Shape_window>(addr).next(); } },
	quit_button{ { x_max() * 19 / 20, 0 }, x_max() / 20, y_max() / 20, "Quit",
		[](Address, Address addr) { reference_to<Shape_window>(addr).quit(); } },
	shape_menu{ { 0, 0 }, 100, 100, Menu::vertical, "Shapes" },
	x_in{ { x_max() * 15 / 20, 0 }, x_max() / 20, y_max() / 20, "x coord" },
	y_in{ { x_max() * 17 / 20, 0 }, x_max() / 20, y_max() / 20, "y coord" }
{
	attach(next_button);
	attach(quit_button);
	shape_menu.attach(new Button{ { 0, 0 }, 0, 0, "Circle",
		[](Address, Address addr) { reference_to<Shape_window>(addr).draw_shape(360); } });
	shape_menu.attach(new Button{ { 0, 0 }, 0, 0, "Square",
		[](Address, Address addr) { reference_to<Shape_window>(addr).draw_shape(4); } });
	shape_menu.attach(new Button{ { 0, 0 }, 0, 0, "Triangle",
		[](Address, Address addr) { reference_to<Shape_window>(addr).draw_shape(3); } });
	shape_menu.attach(new Button{ { 0, 0 }, 0, 0, "Hexagon",
		[](Address, Address addr) { reference_to<Shape_window>(addr).draw_shape(6); } });
	attach(shape_menu);
	attach(x_in);
	attach(y_in);
}

void Shape_window::wait_for_button()
{
	while (!next_button_pushed)
		Fl::wait();
	next_button_pushed = false;
	Fl::redraw();
}

void Shape_window::draw_shape(int num_sides)
{
	const Point shape_origin = { x_in.get_int(), y_in.get_int() };
	static const int shape_radius = 100;

	detach(*current_shape);
	delete current_shape;
	current_shape = new Regular_polygon{ shape_origin, num_sides, shape_radius };
	attach(*current_shape);
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

	Shape_window s_win{ win_tl, win_width, win_height, win_name };

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}