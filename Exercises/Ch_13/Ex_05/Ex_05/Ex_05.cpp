#include "../Graph.h"
#include "../Simple_window.h"

const double pi = atan(1) * 4;

Point n(Graph_lib::Ellipse& ell)
{
	return { ell.center().x, ell.center().y - ell.minor() };
}

Point n(Graph_lib::Circle& circ)
{
	Graph_lib::Ellipse ell{ circ.center(), circ.radius(), circ.radius() };
	return n(ell);
}

Point s(Graph_lib::Ellipse& ell)
{
	return { ell.center().x, ell.center().y + ell.minor() };
}

Point s(Graph_lib::Circle& circ)
{
	Graph_lib::Ellipse ell{ circ.center(), circ.radius(), circ.radius() };
	return s(ell);
}

Point e(Graph_lib::Ellipse& ell)
{
	return { ell.center().x + ell.major(), ell.center().y };
}

Point e(Graph_lib::Circle& circ)
{
	Graph_lib::Ellipse ell{ circ.center(), circ.radius(), circ.radius() };
	return e(ell);
}

Point w(Graph_lib::Ellipse& ell)
{
	return { ell.center().x - ell.major(), ell.center().y };
}

Point w(Graph_lib::Circle& circ)
{
	Graph_lib::Ellipse ell{ circ.center(), circ.radius(), circ.radius() };
	return w(ell);
}

Point center(Graph_lib::Ellipse& ell)
{
	return ell.center();
}

Point center(Graph_lib::Circle& circ)
{
	Graph_lib::Ellipse ell{ circ.center(), circ.radius(), circ.radius() };
	return center(ell);
}

Point ne(Graph_lib::Ellipse& ell)
{
	return { int(ell.center().x + ell.major() * cos(45 * pi / 180)), 
		int(ell.center().y - ell.minor() * sin(45 * pi / 180)) };
}

Point ne(Graph_lib::Circle& circ)
{
	Graph_lib::Ellipse ell{ circ.center(), circ.radius(), circ.radius() };
	return ne(ell);
}

Point se(Graph_lib::Ellipse& ell)
{
	return { int(ell.center().x + ell.major() * cos(315 * pi / 180)),
		int(ell.center().y - ell.minor() * sin(315 * pi / 180)) };
}

Point se(Graph_lib::Circle& circ)
{
	Graph_lib::Ellipse ell{ circ.center(), circ.radius(), circ.radius() };
	return se(ell);
}

Point sw(Graph_lib::Ellipse& ell)
{
	return { int(ell.center().x + ell.major() * cos(225 * pi / 180)),
		int(ell.center().y - ell.minor() * sin(225 * pi / 180)) };
}

Point sw(Graph_lib::Circle& circ)
{
	Graph_lib::Ellipse ell{ circ.center(), circ.radius(), circ.radius() };
	return sw(ell);
}

Point nw(Graph_lib::Ellipse& ell)
{
	return { int(ell.center().x + ell.major() * cos(135 * pi / 180)),
		int(ell.center().y - ell.minor() * sin(135 * pi / 180)) };
}

Point nw(Graph_lib::Circle& circ)
{
	Graph_lib::Ellipse ell{ circ.center(), circ.radius(), circ.radius() };
	return nw(ell);
}

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 4, y_max() / 4 };
	const int win_width = x_max() / 2;
	const int win_height = y_max() / 2;
	const string win_name{ "My window" };
	Simple_window s_win{ win_tl, win_width, win_height, win_name };

	Graph_lib::Ellipse ell{ { s_win.x_max() / 2, s_win.y_max() / 2 }, s_win.x_max() / 4, s_win.y_max() / 4 };
	ell.set_color(Color::black);

	Circle circ{ { s_win.x_max() / 4, s_win.y_max() / 4 }, s_win.y_max() / 4 };
	circ.set_color(Color::black);

	Mark mark1{ n(ell), '1' };
	mark1.set_color(Color::black);

	Mark mark2{ s(circ), '2' };
	mark2.set_color(Color::black);

	Mark mark3{ e(ell), '3' };
	mark3.set_color(Color::black);

	Mark mark4{ w(circ), '4' };
	mark4.set_color(Color::black);

	Mark mark5{ center(ell), '5' };
	mark5.set_color(Color::black);

	Mark mark6{ ne(circ), '6' };
	mark6.set_color(Color::black);

	Mark mark7{ se(ell), '7' };
	mark7.set_color(Color::black);

	Mark mark8{ sw(circ), '8' };
	mark8.set_color(Color::black);

	Mark mark9{ nw(ell), '9' };
	mark9.set_color(Color::black);

	s_win.attach(ell);
	s_win.attach(circ);
	s_win.attach(mark1);
	s_win.attach(mark2);
	s_win.attach(mark3);
	s_win.attach(mark4);
	s_win.attach(mark5);
	s_win.attach(mark6);
	s_win.attach(mark7);
	s_win.attach(mark8);
	s_win.attach(mark9);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}