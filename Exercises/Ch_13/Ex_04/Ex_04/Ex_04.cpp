#include "../Graph.h"
#include "../Simple_window.h"

Point n(Graph_lib::Rectangle& rect)
{
	return { rect.point(0).x + rect.width() / 2, rect.point(0).y };
}

Point s(Graph_lib::Rectangle& rect)
{
	return { rect.point(0).x + rect.width() / 2, rect.point(0).y + rect.height() };
}

Point e(Graph_lib::Rectangle& rect)
{
	return { rect.point(0).x + rect.width(), rect.point(0).y + rect.height() / 2 };
}

Point w(Graph_lib::Rectangle& rect)
{
	return { rect.point(0).x, rect.point(0).y + rect.height() / 2 };
}

Point center(Graph_lib::Rectangle& rect)
{
	return { rect.point(0).x + rect.width() / 2, rect.point(0).y + rect.height() / 2 };
}

Point ne(Graph_lib::Rectangle& rect)
{
	return { rect.point(0).x + rect.width(), rect.point(0).y };
}

Point se(Graph_lib::Rectangle& rect)
{
	return { rect.point(0).x + rect.width(), rect.point(0).y + rect.height() };
}

Point sw(Graph_lib::Rectangle& rect)
{
	return { rect.point(0).x, rect.point(0).y + rect.height() };
}

Point nw(Graph_lib::Rectangle& rect)
{
	return rect.point(0);
}

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 4, y_max() / 4 };
	const int win_width = x_max() / 2;
	const int win_height = y_max() / 2;
	const string win_name{ "My window" };
	Simple_window s_win{ win_tl, win_width, win_height, win_name };

	Graph_lib::Rectangle rect{ { s_win.x_max() / 4, s_win.y_max() / 4 }, s_win.x_max() / 2, s_win.y_max() / 2 };
	rect.set_color(Color::black);

	Mark mark1{ n(rect), '1' };
	mark1.set_color(Color::black);

	Mark mark2{ s(rect), '2' };
	mark2.set_color(Color::black);

	Mark mark3{ e(rect), '3' };
	mark3.set_color(Color::black);

	Mark mark4{ w(rect), '4' };
	mark4.set_color(Color::black);

	Mark mark5{ center(rect), '5' };
	mark5.set_color(Color::black);

	Mark mark6{ ne(rect), '6' };
	mark6.set_color(Color::black);

	Mark mark7{ se(rect), '7' };
	mark7.set_color(Color::black);

	Mark mark8{ sw(rect), '8' };
	mark8.set_color(Color::black);

	Mark mark9{ nw(rect), '9' };
	mark9.set_color(Color::black);

	s_win.attach(rect);
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