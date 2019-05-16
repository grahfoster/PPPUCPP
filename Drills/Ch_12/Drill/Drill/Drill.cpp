#include "../Graph.h"
#include "../Simple_window.h"

int main()
try {
	using namespace Graph_lib;

	Point tl{ 200, 200 };

	Simple_window win{ tl, 600, 400, "My window" };

	Axis xa{ Axis::x, Point{20,350}, 280, 5, "x-axis" };
	xa.set_color(Color::black);

	Axis ya{ Axis::y, Point{20, 350}, 280, 5, "y-axis" };
	ya.set_color(Color::black);
	ya.notches.set_color(Color::red);

	Function sine{ sin, 0, 5.6, Point{20, 300}, 1000, 50, 50 };
	sine.set_color(Color::dark_cyan);

	Graph_lib::Polygon poly;
	poly.add(Point{ 300, 200 });
	poly.add(Point{ 350, 100 });
	poly.add(Point{ 400, 200 });
	poly.set_color(Color::blue);
	poly.set_style(Line_style(Line_style::dashdot, 3));

	Graph_lib::Rectangle r{ Point{200, 200}, 100, 50 };
	r.set_color(Color::black);
	r.set_fill_color(Color::white);

	Closed_polyline poly_rect;
	poly_rect.add(Point{ 100, 50 });
	poly_rect.add(Point{ 200, 50 });
	poly_rect.add(Point{ 200, 100 });
	poly_rect.add(Point{ 100, 100 });
	poly_rect.add(Point{ 150, 75 });
	poly_rect.set_color(Color::black);
	poly_rect.set_style(Line_style(Line_style::dashdotdot, 2));
	poly_rect.set_fill_color(Color::dark_green);

	Text t{ Point{100, 150}, "Hello, graphical world!" };
	t.set_font(Font::courier_italic);
	t.set_font_size(15);
	t.set_color(Color::black);

	Image ii{ Point{100, 100}, "cloud_and_men.jpg" };
	ii.move(200, 150);

	Circle c{ Point{100, 200}, 25 };
	c.set_color(Color::black);

	Graph_lib::Ellipse e{ Point{100, 200}, 50, 20 };
	e.set_color(Color::dark_blue);

	Mark m{ Point{100, 200}, '$' };

	ostringstream oss;
	oss << "screen size: " << x_max() << '*' << y_max() <<
		"; window size: " << win.x_max() << '*' << win.y_max();
	Text sizes{ Point{200, 20}, oss.str() };
	sizes.set_color(Color::dark_magenta);
	sizes.set_font(Font::helvetica);

	Image cal{ Point{450, 100}, "cloud_and_train.gif" };
	cal.set_mask(Point{ 150, 150 }, 100, 100);

	win.attach(xa);
	win.attach(ya);
	win.attach(sine);
	win.attach(poly);
	win.attach(r);
	win.attach(poly_rect);
	win.attach(t);
	win.attach(ii);
	win.attach(c);
	win.attach(e);
	win.attach(m);
	win.attach(sizes);
	win.attach(cal);

	win.wait_for_button();
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}