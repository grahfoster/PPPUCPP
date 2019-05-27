#include "../Graph.h"
#include "../Simple_window.h"

namespace Graph_lib {

class Arc : public Ellipse {
public:
	Arc(Point p, int w, int h, int a1, int a2) : a1{ a1 }, a2{ a2 }, Ellipse{ p, w, h } {}

	void draw_lines() const;
private:
	int a1;
	int a2;
};

void Arc::draw_lines() const
{
	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		fl_pie(point(0).x, point(0).y, major() + major(), minor() + minor(), a1, a2);
		fl_color(color().as_int());
	}

	if (color().visibility()) {
		fl_color(color().as_int());
		fl_arc(point(0).x, point(0).y, major() + major(), minor() + minor(), a1, a2);
	}
}

class Box : public Shape {
public:
	Box(Point p, int w, int h, int arc_curve) :
		w{ w }, h{ h }, curve{ arc_curve },
		arc1{ { p.x + w / arc_curve, p.y + h / arc_curve },
			w / arc_curve, h / arc_curve, 90, 180 },
		arc2{ { p.x + w - w / arc_curve, p.y + h / arc_curve },
			w / arc_curve, h / arc_curve, 0, 90 },
		arc3{ { p.x + w - w / arc_curve, p.y + h - h / arc_curve },
			w / arc_curve, h / arc_curve, 270, 0 },
		arc4{ { p.x + w / arc_curve, p.y + h - h / arc_curve },
			w / arc_curve, h / arc_curve, 180, 270 },
		line1{ { p.x + w / arc_curve, p.y },
			{ p.x + w - w / arc_curve, p.y } },
		line2{ { line1.point(1).x + w / arc_curve, line1.point(1).y + h / arc_curve },
			{ line1.point(1).x + w / arc_curve, line1.point(1).y + h - h / arc_curve } },
		line3{ { line2.point(1).x - w / arc_curve, line2.point(1).y + h / arc_curve },
			{ line1.point(0).x, line2.point(1).y + h / arc_curve } },
		line4{ { line1.point(0).x - w / arc_curve, line2.point(1).y },
			{ line1.point(0).x - w / arc_curve, line2.point(0).y } }
	{
		if (w <= 0 || h <= 0) error("Bad box: non-positive side");
		add(p);
	}
	Box(Point p, Point p2, int arc_curve) :
		w{ p2.x - p.x }, h{ p2.y - p.y }, curve{ arc_curve },
		arc1{ { p.x + w / arc_curve, p.y + h / arc_curve },
			w / arc_curve, h / arc_curve, 90, 180 },
		arc2{ { p.x + w - w / arc_curve, p.y + h / arc_curve },
			w / arc_curve, h / arc_curve, 0, 90 },
		arc3{ { p.x + w - w / arc_curve, p.y + h - h / arc_curve },
			w / arc_curve, h / arc_curve, 270, 0 },
		arc4{ { p.x + w / arc_curve, p.y + h - h / arc_curve },
			w / arc_curve, h / arc_curve, 180, 270 },
		line1{ { p.x + w / arc_curve, p.y },
			{ p.x + w - w / arc_curve, p.y } },
		line2{ { line1.point(1).x + w / arc_curve, line1.point(1).y + h / arc_curve },
			{ line1.point(1).x + w / arc_curve, line1.point(1).y + h - h / arc_curve } },
		line3{ { line2.point(1).x - w / arc_curve, line2.point(1).y + h / arc_curve },
			{ line1.point(0).x, line2.point(1).y + h / arc_curve } },
		line4{ { line1.point(0).x - w / arc_curve, line2.point(1).y },
			{ line1.point(0).x - w / arc_curve, line2.point(0).y } }
	{
		if (w <= 0 || h <= 0) error("Bad box: non-positive side");
		add(p);
	}

	int height() const { return h; }
	int width() const { return w; }
	void draw_lines() const;

	void move(int, int);
	void set_color(Color);
	void set_style(Line_style);
	void set_fill_color(Color);
private:
	int h;
	int w;
	int curve;
	Arc arc1;
	Arc arc2;
	Arc arc3;
	Arc arc4;
	Line line1;
	Line line2;
	Line line3;
	Line line4;
};

void Box::move(int dx, int dy)
{
	Shape::move(dx, dy);

	arc1.move(dx, dy);
	arc2.move(dx, dy);
	arc3.move(dx, dy);
	arc4.move(dx, dy);
	line1.move(dx, dy);
	line2.move(dx, dy);
	line3.move(dx, dy);
	line4.move(dx, dy);
}

void Box::set_color(Color col)
{
	arc1.set_color(col);
	arc2.set_color(col);
	arc3.set_color(col);
	arc4.set_color(col);
	line1.set_color(col);
	line2.set_color(col);
	line3.set_color(col);
	line4.set_color(col);
}

void Box::set_style(Line_style ls)
{
	arc1.set_style(ls);
	arc2.set_style(ls);
	arc3.set_style(ls);
	arc4.set_style(ls);
	line1.set_style(ls);
	line2.set_style(ls);
	line3.set_style(ls);
	line4.set_style(ls);
}

void Box::set_fill_color(Color col)
{
	Shape::set_fill_color(col);

	arc1.set_fill_color(col);
	arc2.set_fill_color(col);
	arc3.set_fill_color(col);
	arc4.set_fill_color(col);
	line1.set_fill_color(col);
	line2.set_fill_color(col);
	line3.set_fill_color(col);
	line4.set_fill_color(col);
}

void Box::draw_lines() const
{
	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		fl_rectf(point(0).x + w / curve, point(0).y, w - 2 * w / curve, h);
		fl_rectf(point(0).x, point(0).y + h / curve, w, h - 2 * h / curve);
		fl_color(color().as_int());
	}
	
	arc1.draw_lines();
	arc2.draw_lines();
	arc3.draw_lines();
	arc4.draw_lines();
	line1.draw();
	line2.draw();
	line3.draw();
	line4.draw();
}
}

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 4, y_max() / 4 };
	const int win_width = x_max() / 2;
	const int win_height = y_max() / 2;
	const string win_name{ "My window" };
	Simple_window s_win{ win_tl, win_width, win_height, win_name };

	Box box1{ {100, 100}, 100, 75, 5 };
	box1.set_color(Color::black);
	box1.set_fill_color(Color::green);
	box1.move(100, 100);

	Box box2{ {150, 175}, { 400, 325 }, 10 };
	box2.set_color(Color::blue);
	box2.set_style(Line_style::dashdot);
	
	s_win.attach(box1);
	s_win.attach(box2);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}