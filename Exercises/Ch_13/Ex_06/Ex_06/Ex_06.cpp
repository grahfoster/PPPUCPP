#include "../Graph.h"
#include "../Simple_window.h"

const double pi = atan(1) * 4;

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
	Box(Point p, int w, int h, int arc_curve, const string& label) :
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
			{ line1.point(0).x - w / arc_curve, line2.point(0).y } },
		text{ { line4.point(0).x + w / arc_curve, line4.point(0).y - h / arc_curve }, label }
	{
		if (w <= 0 || h <= 0) error("Bad box: non-positive side");
		add(p);
	}
	Box(Point p, Point p2, int arc_curve, const string& label) :
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
			{ line1.point(0).x - w / arc_curve, line2.point(0).y } },
		text{ { line4.point(0).x + w / arc_curve, line4.point(0).y - h / arc_curve }, label }
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
	void set_label(const string&);
	void set_font(Font);
	void set_font_size(int);
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
	Text text;
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
	text.move(dx, dy);
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
	text.set_color(col);
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
	text.set_style(ls);
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
	text.set_fill_color(col);
}

void Box::set_label(const string& s)
{
	text.set_label(s);
}

void Box::set_font(Font f)
{
	text.set_font(f);
}

void Box::set_font_size(int s)
{
	text.set_font_size(s);
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
	text.draw_lines();
}

class Arrow : public Line {
public:
	Arrow(Point, Point, double, int);

	void move(int, int);
	void set_color(Color);
	void set_style(Line_style);
	void set_fill_color(Color);
	void draw_lines() const;
private:
	Polygon head;
};

Arrow::Arrow(Point p1, Point p2, double head_angle, int head_size) :
	Line{ p1, p2 }
{
	const double line_angle = atan2(p2.y - p1.y, p2.x - p1.x);

	head.add(p2);
	head.add({ int(p2.x - head_size * cos(line_angle + head_angle)),
		int(p2.y - head_size * sin(line_angle + head_angle)) });
	head.add({ int(p2.x - head_size * cos(line_angle - head_angle)),
		int(p2.y - head_size * sin(line_angle - head_angle)) });
}

void Arrow::move(int dx, int dy)
{
	Line::move(dx, dy);

	head.move(dx, dy);
}

void Arrow::set_color(Color col)
{
	Line::set_color(col);

	head.set_color(col);
}

void Arrow::set_style(Line_style ls)
{
	Line::set_style(ls);

	head.set_style(ls);
}

void Arrow::set_fill_color(Color col)
{
	head.set_fill_color(col);
}

void Arrow::draw_lines() const
{
	Line::draw_lines();

	head.draw_lines();
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

	const int box_height = 30;
	const int box_curve = 10;

	Box box_win{ { 175, 50 }, 120, box_height, box_curve, "Window" };
	Box box_s_win{ { 125, 200 }, 225, box_height, box_curve, "Simple_window" };
	Box box_shape{ { 450, 175}, 90, box_height, box_curve, "Shape" };
	Box box_line{ { 100, 400 }, 75, box_height, box_curve, "Line" };
	Box box_lines{ { 200, 400 }, 75, box_height, box_curve, "Lines" };
	Box box_poly{ { 300, 400 }, 120, box_height, box_curve, "Polygon" };
	Box box_axis{ { 450, 400 }, 60, box_height, box_curve, "Axis" };
	Box box_rect{ { 535, 400 }, 140, box_height, box_curve, "Rectangle" };
	Box box_text{ { 700, 400 }, 65, box_height, box_curve, "Text" };
	Box box_image{ { 790, 400 }, 85, box_height, box_curve, "Image" };

	Vector_ref<Box> boxes;
	boxes.push_back(box_win);
	boxes.push_back(box_s_win);
	boxes.push_back(box_shape);
	boxes.push_back(box_line);
	boxes.push_back(box_lines);
	boxes.push_back(box_poly);
	boxes.push_back(box_axis);
	boxes.push_back(box_rect);
	boxes.push_back(box_text);
	boxes.push_back(box_image);
	boxes.push_back(new Box{ {400, 50}, 150, box_height, box_curve, "Line_style" });
	boxes.push_back(new Box{ {650, 50}, 80, box_height, box_curve, "Color" });
	boxes.push_back(new Box{ {700, 200}, 75, box_height, box_curve, "Point" });

	for (int i = 0; i < boxes.size(); ++i) {
		boxes[i].set_color(Color::black);
		boxes[i].set_fill_color(Color::dark_green);
		boxes[i].set_font(Font::helvetica_bold);
		boxes[i].set_font_size(24);
		s_win.attach(boxes[i]);
	}

	const double head_angle = 30 * pi / 180;
	const int head_size = 5;

	Vector_ref<Arrow> arws;
	arws.push_back(new Arrow{ { box_s_win.point(0).x + box_s_win.width() / 2, box_s_win.point(0).y },
		{ box_win.point(0).x + box_win.width() / 2, box_win.point(0).y + box_win.height() }, head_angle,
		head_size });
	arws.push_back(new Arrow{ { box_line.point(0).x + box_line.width() / 2, box_line.point(0).y },
		{ box_shape.point(0).x + box_shape.width() / 8, box_shape.point(0).y + box_shape.height() }, head_angle,
		head_size });
	arws.push_back(new Arrow{ { box_lines.point(0).x + box_lines.width() / 2, box_lines.point(0).y },
		{ box_shape.point(0).x + box_shape.width() / 4, box_shape.point(0).y + box_shape.height() }, head_angle,
		head_size });
	arws.push_back(new Arrow{ { box_poly.point(0).x + box_poly.width() / 2, box_poly.point(0).y },
		{ box_shape.point(0).x + box_shape.width() * 3 / 8, box_shape.point(0).y + box_shape.height() }, head_angle,
		head_size });
	arws.push_back(new Arrow{ { box_axis.point(0).x + box_axis.width() / 2, box_axis.point(0).y },
		{ box_shape.point(0).x + box_shape.width() / 2, box_shape.point(0).y + box_shape.height() }, head_angle,
		head_size });
	arws.push_back(new Arrow{ { box_rect.point(0).x + box_rect.width() / 2, box_rect.point(0).y },
		{ box_shape.point(0).x + box_shape.width() * 5 / 8, box_shape.point(0).y + box_shape.height() }, head_angle,
		head_size });
	arws.push_back(new Arrow{ { box_text.point(0).x + box_text.width() / 2, box_text.point(0).y },
		{ box_shape.point(0).x + box_shape.width() * 3 / 4, box_shape.point(0).y + box_shape.height() }, head_angle,
		head_size });
	arws.push_back(new Arrow{ { box_image.point(0).x + box_image.width() / 2, box_image.point(0).y },
		{ box_shape.point(0).x + box_shape.width() * 7 / 8, box_shape.point(0).y + box_shape.height() }, head_angle,
		head_size });

	for (int i = 0; i < arws.size(); ++i) {
		arws[i].set_color(Color::black);
		arws[i].set_fill_color(Color::black);
		s_win.attach(arws[i]);
	}

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}