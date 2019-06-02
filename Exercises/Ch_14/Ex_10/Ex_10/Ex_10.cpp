#include "../Graph.h"
#include "../Simple_window.h"

namespace Graph_lib {

class Arc : public Ellipse {
public:
	Arc(Point p, int w, int h, int a1, int a2) : angle1{ a1 }, angle2{ a2 }, Ellipse{ p, w, h } {}

	void draw_lines() const override;
private:
	int angle1;
	int angle2;
};

void Arc::draw_lines() const
{
	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		fl_pie(point(0).x, point(0).y, major() + major(), minor() + minor(), angle1, angle2);
		fl_color(color().as_int());
	}

	if (color().visibility()) {
		fl_color(color().as_int());
		fl_arc(point(0).x, point(0).y, major() + major(), minor() + minor(), angle1, angle2);
	}
}

class Box : public Shape {
public:
	Box(Point, int, int, int);

	int get_width() const { return width; }
	int get_height() const { return height; }
	void draw_lines() const override;

	void move(int, int) override;
	void set_color(Color);
	void set_style(Line_style);
	void set_fill_color(Color);
private:
	int width;
	int height;
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

Box::Box(Point p, int w, int h, int c) :
	width{ w }, height{ h }, curve{ c },
	arc1{ { p.x + w / c, p.y + h / c }, w / c, h / c, 90, 180 },
	arc2{ { p.x + w - w / c, p.y + h / c }, w / c, h / c, 0, 90 },
	arc3{ { p.x + w - w / c, p.y + h - h / c }, w / c, h / c, 270, 0 },
	arc4{ { p.x + w / c, p.y + h - h / c }, w / c, h / c, 180, 270 },
	line1{ { p.x + w / c, p.y }, { p.x + w - w / c, p.y } },
	line2{ { line1.point(1).x + w / c, line1.point(1).y + h / c },
		{ line1.point(1).x + w / c, line1.point(1).y + h - h / c } },
	line3{ { line2.point(1).x - w / c, line2.point(1).y + h / c },
		{ line1.point(0).x, line2.point(1).y + h / c } },
	line4{ { line1.point(0).x - w / c, line2.point(1).y },
		{ line1.point(0).x - w / c, line2.point(0).y } }
{
	add(p);
}

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
}

void Box::draw_lines() const
{
	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		fl_rectf(point(0).x + width / curve, point(0).y, width - 2 * width / curve, height);
		fl_rectf(point(0).x, point(0).y + height / curve, width, height - 2 * height / curve);
		fl_color(color().as_int());
	}

	arc1.draw();
	arc2.draw();
	arc3.draw();
	arc4.draw();
	line1.draw();
	line2.draw();
	line3.draw();
	line4.draw();
}

class Pseudo_window : public Shape {
public:
	Pseudo_window(Point, int, int, string);

	void draw_lines() const override;
	int get_width() const { return width; }
	int get_height() const { return height; }
private:
	const int box_curve = 100;
	const int icon_curve = 10;
	const int icon_ratio = 40;
	const int padding_ratio = 5;
	const int radius_ratio = 5;
	const int frame_line_width = 3;
	const int icon_line_width = 2;

	int width;
	int height;
	Box frame;
	Box bar;
	Rectangle app_icon;
	Text label;
	Box min_icon;
	Box max_icon;
	Box close_icon;
	Lines min_lines;
	Lines max_lines;
	Lines close_lines;
	Circle circ;
};

Pseudo_window::Pseudo_window(Point tl, int w, int h, string s) :
	width{ w }, height{ h }, frame{ tl, w, h, box_curve },
	bar{ { tl.x + frame_line_width / 2, tl.y + frame_line_width / 2 }, width - 2 * (frame_line_width / 2),
		width / icon_ratio + 2 * width / icon_ratio / padding_ratio, box_curve },
	label{ tl, s }, app_icon{ tl, width / icon_ratio, width / icon_ratio * 3 / 4 },
	min_icon{ tl, width / icon_ratio, width / icon_ratio, icon_curve },
	max_icon{ tl, width / icon_ratio, width / icon_ratio, icon_curve },
	close_icon{ tl, width / icon_ratio, width / icon_ratio, icon_curve },
	circ{ tl, height / radius_ratio }
{
	add(tl);

	const Fl_Color win_col{ fl_rgb_color(0, 84, 227) };
	const int icon_width = width / icon_ratio;
	const int padding = icon_width / padding_ratio;

	frame.set_color(win_col);
	frame.set_style(Line_style{ Line_style::solid, frame_line_width});

	bar.set_color(Color::invisible);
	bar.set_fill_color(win_col);

	app_icon.set_color(Color::dark_blue);
	app_icon.set_fill_color(Color::white);
	app_icon.move(2 * padding, 2 * padding);

	label.set_color(Color::white);
	label.set_font(Font::helvetica_bold);
	label.set_font_size(16);
	label.move(app_icon.point(0).x + padding, icon_width);

	min_icon.set_color(Color::white);
	min_icon.move(width - 2 * padding - 3 * icon_width - 2 * padding, padding);

	max_icon.set_color(Color::white);
	max_icon.move(width - padding - 2 * icon_width - 2 * padding, padding);

	close_icon.set_color(Color::white);
	close_icon.set_fill_color(Color::red);
	close_icon.move(width - icon_width - 2 * padding, padding);

	min_lines.add({ padding, icon_width - padding }, { icon_width * 3 / 4, icon_width - padding });
	min_lines.move(min_icon.point(0).x, min_icon.point(0).y);
	min_lines.set_color(Color::white);
	min_lines.set_style(Line_style{ Line_style::solid, icon_line_width });

	max_lines.add({ padding, padding }, { icon_width - padding, padding });
	max_lines.add({ icon_width - padding, padding }, { icon_width - padding, icon_width - padding });
	max_lines.add({ icon_width - padding, icon_width - padding }, { padding, icon_width - padding });
	max_lines.add({ padding, icon_width - padding }, { padding, padding });
	max_lines.move(max_icon.point(0).x, max_icon.point(0).y);
	max_lines.set_color(Color::white);
	max_lines.set_style(Line_style{ Line_style::solid, icon_line_width });

	close_lines.add({ padding, padding }, { icon_width - padding, icon_width - padding });
	close_lines.add({ padding, icon_width - padding }, { icon_width - padding, padding });
	close_lines.move(close_icon.point(0).x, close_icon.point(0).y);
	close_lines.set_color(Color::white);
	close_lines.set_style(Line_style{ Line_style::solid, icon_line_width });

	circ.set_color(Color::black);
	circ.move(width / 2, height / 2);
}

void Pseudo_window::draw_lines() const
{
	frame.draw();
	bar.draw();
	label.draw();
	app_icon.draw();
	min_icon.draw();
	max_icon.draw();
	close_icon.draw();
	min_lines.draw();
	max_lines.draw();
	close_lines.draw();
	circ.draw();
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

	Pseudo_window p_win{ { 25, 25 }, s_win.x_max() - 50, s_win.y_max() - 50, "circle" };

	s_win.attach(p_win);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}