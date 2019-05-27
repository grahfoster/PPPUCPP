#include "../Graph.h"
#include "../Simple_window.h"

const double pi = atan(1) * 4; 

namespace Graph_lib {

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

	Arrow arw1{ { 0, 0 }, { 100, 100 }, 30 * pi / 180, 10 };
	arw1.set_color(Color::black);
	arw1.set_fill_color(Color::red);
	arw1.move(200, 50);

	Arrow arw2{ { 10, 100 }, { 400, 40 }, 45 * pi / 180, 50 };
	arw2.set_color(Color::blue);
	arw2.set_style(Line_style{ Line_style::dash, 2 });
	arw2.set_fill_color(Color::blue);

	s_win.attach(arw1);
	s_win.attach(arw2);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}