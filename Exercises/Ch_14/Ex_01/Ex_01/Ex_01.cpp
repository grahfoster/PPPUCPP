#include "../Graph.h"
#include "../Simple_window.h"

const double pi = atan(1) * 4;

namespace Graph_lib {

class Arc : public Ellipse {
public:
	Arc(Point c, int w, int h, int a1, int a2) : angle1{ a1 }, angle2{ a2 }, Ellipse{ c, w, h } {}

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

class Smiley : public Circle {
public:
	Smiley(Point c, int r) : Circle{ c, r },
		eye1{ { int(c.x + r / 2 * cos(45 * pi / 180)), int(c.y - r / 2 * sin(45 * pi / 180)) }, 'o' },
		eye2{ { int(c.x + r / 2 * cos(135 * pi / 180)), int(c.y - r / 2 * sin(135 * pi / 180)) }, 'o' },
		smile{ { c.x, c.y + r / 4 }, r / 2, r / 4, 180, 360 } {}

	void draw_lines() const override;

	void set_color(Color);
private:
	Mark eye1;
	Mark eye2;
	Arc smile;
};

void Smiley::draw_lines() const
{
	Circle::draw_lines();

	eye1.draw_lines();
	eye2.draw_lines();
	smile.draw_lines();
}

void Smiley::set_color(Color col)
{
	Circle::set_color(col);

	eye1.set_color(col);
	eye2.set_color(col);
	smile.set_color(col);
}

class Smiley_hat : public Smiley {
public:
	Smiley_hat(Point, int);

	void draw_lines() const override;

	void set_color(Color);
private:
	Open_polyline hat;
};

Smiley_hat::Smiley_hat(Point c, int r) :
	Smiley{ c, r }
{
	hat.add({ int(c.x + r * cos(45 * pi / 180)), int(c.y - r * sin(45 * pi / 180)) });
	hat.add({ c.x, c.y - r * 2 });
	hat.add({ int(c.x + r * cos(135 * pi / 180)), int(c.y - r * sin(135 * pi / 180)) });
}

void Smiley_hat::draw_lines() const
{
	Smiley::draw_lines();

	hat.draw_lines();
}

void Smiley_hat::set_color(Color col)
{
	Smiley::set_color(col);

	hat.set_color(col);
}

class Frowny : public Circle {
public:
	Frowny(Point c, int r) : Circle{ c, r },
		eye1{ { int(c.x + r / 2 * cos(45 * pi / 180)), int(c.y - r / 2 * sin(45 * pi / 180)) }, 'o' },
		eye2{ { int(c.x + r / 2 * cos(135 * pi / 180)), int(c.y - r / 2 * sin(135 * pi / 180)) }, 'o' },
		smile{ { c.x, c.y + r / 2 }, r / 2, r / 4, 0, 180 } {}

	void draw_lines() const override;

	void set_color(Color);
private:
	Mark eye1;
	Mark eye2;
	Arc smile;
};

void Frowny::draw_lines() const
{
	Circle::draw_lines();

	eye1.draw_lines();
	eye2.draw_lines();
	smile.draw_lines();
}

void Frowny::set_color(Color col)
{
	Circle::set_color(col);

	eye1.set_color(col);
	eye2.set_color(col);
	smile.set_color(col);
}

class Frowny_hat : public Frowny {
public:
	Frowny_hat(Point, int);

	void draw_lines() const override;

	void set_color(Color);
private:
	Open_polyline hat;
};

Frowny_hat::Frowny_hat(Point c, int r) :
	Frowny{ c, r }
{
	hat.add({ int(c.x + r * cos(45 * pi / 180)), int(c.y - r * sin(45 * pi / 180)) });
	hat.add({ hat.point(0).x, hat.point(0).y - r });
	hat.add({ int(c.x + r * cos(135 * pi / 180)), hat.point(1).y });
	hat.add({ hat.point(2).x, int(c.y - r * sin(135 * pi / 180)) });
}

void Frowny_hat::draw_lines() const
{
	Frowny::draw_lines();

	hat.draw_lines();
}

void Frowny_hat::set_color(Color col)
{
	Frowny::set_color(col);

	hat.set_color(col);
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

	Smiley_hat smiley_hat{ { s_win.x_max() / 4, s_win.y_max() / 2 }, 100 };
	smiley_hat.set_color(Color::black);

	Frowny_hat frowny_hat{ { s_win.x_max() * 3 / 4, s_win.y_max() / 2 }, 100 };
	frowny_hat.set_color(Color::black);

	s_win.attach(smiley_hat);
	s_win.attach(frowny_hat);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}