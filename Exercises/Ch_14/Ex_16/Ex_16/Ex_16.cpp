#include "../Graph.h"
#include "../Simple_window.h"

namespace Graph_lib {

class Controller {
public:
	virtual void show() const = 0;

	virtual void on() = 0;
	virtual void off() = 0;
	virtual void set_level(int) = 0;
};

class Controller1 : public Controller {
public:
	void show() const override;

	void on() override { is_on = true; }
	void off() override { is_on = false; }
	void set_level(int l) { level = l; }
private:
	bool is_on = false;
	int level = 0;
};

void Controller1::show() const
{
	cout << "Status: " << (is_on ? "On" : "Off") <<
		"\nLevel: " << level << '\n';
}

class Controller2 : public Controller {
public:
	Controller2(Shape* s) : shape{ s } {}
	~Controller2() { delete shape; }

	void show() const override;

	void on() override;
	void off() override;
	void set_level(int);
private:
	Shape* shape;
	bool is_visible;
	Color col = Color::invisible;
};

void Controller2::show() const
{
	cout << "Status: " << (is_visible ? "Visible" : "Invisible") <<
		"\nColor: " << col.as_int() << '\n';
}

void Controller2::on()
{
	is_visible = true;
	shape->set_color(col);
}

void Controller2::off()
{
	is_visible = false;
	shape->set_color(Color::invisible);
}

void Controller2::set_level(int c)
{
	col = c;
	if (is_visible)
		on();
}

class Controller3 : public Controller {
public:
	Controller3(Circle* c) : circ{ c }, orig_radius{ c->radius() } {}
	~Controller3() { delete circ; }

	void show() const override;

	void on() override;
	void off() override;
	void set_level(int);
private:
	Circle* circ;
	bool is_mag = false;
	int orig_radius;
	int mag_level = 1;
};

void Controller3::show() const
{
	cout << "Status: " << (is_mag ? "Magnifying" : "Not Magnifying") <<
		"\nMagnification Level: " << mag_level << '\n';
}

void Controller3::on()
{
	is_mag = true;
	circ->set_radius(mag_level * orig_radius);
}

void Controller3::off()
{
	is_mag = false;
	circ->set_radius(orig_radius);
}

void Controller3::set_level(int ml)
{
	mag_level = ml;
	if (is_mag)
		on();
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

	Circle circ{ { 100, 100 }, 50 };

	Controller1 c1;
	c1.on();
	c1.set_level(11);
	cout << "Controller1:\n";
	c1.show();

	Controller2 c2{ &circ };
	c2.on();
	c2.set_level(Color::black);
	cout << "Controller2:\n";
	c2.show();

	Controller3 c3{ &circ };
	c3.on();
	c3.set_level(4);
	cout << "Controller3:\n";
	c3.show();

	s_win.attach(circ);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}