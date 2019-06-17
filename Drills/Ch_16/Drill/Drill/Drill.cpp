#include "../Graph.h"
#include "../GUI.h"
#include "../Window.h"

namespace Graph_lib {

struct Lines_window : Window {
	Lines_window(Point xy, int w, int h, const string& title);
private:
	Open_polyline lines;
	Button next_button;
	Button quit_button;
	In_box next_x;
	In_box next_y;
	Out_box xy_out;
	Menu color_menu;
	Button menu_button;
	Menu style_menu;
	Button style_menu_button;

	static void cb_next(Address, Address pw) { reference_to<Lines_window>(pw).next(); }
	static void cb_quit(Address, Address pw) { reference_to<Lines_window>(pw).quit(); }
	static void cb_red(Address, Address pw) { reference_to<Lines_window>(pw).red_pressed(); }
	static void cb_blue(Address, Address pw) { reference_to<Lines_window>(pw).blue_pressed(); }
	static void cb_black(Address, Address pw) { reference_to<Lines_window>(pw).black_pressed(); }
	static void cb_menu(Address, Address pw) { reference_to<Lines_window>(pw).menu_pressed(); }
	static void cb_solid(Address, Address pw) { reference_to<Lines_window>(pw).solid_pressed(); }
	static void cb_dash(Address, Address pw) { reference_to<Lines_window>(pw).dash_pressed(); }
	static void cb_dot(Address, Address pw) { reference_to<Lines_window>(pw).dot_pressed(); }
	static void cb_style_menu(Address, Address pw) { reference_to<Lines_window>(pw).style_menu_pressed(); }

	void change(Color c) { lines.set_color(c); }
	void change_style(Line_style ls) { lines.set_style(ls); }
	void hide_menu();
	void hide_style_menu();

	void next();
	void quit() { hide(); }
	void red_pressed();
	void blue_pressed();
	void black_pressed();
	void menu_pressed();
	void solid_pressed();
	void dash_pressed();
	void dot_pressed();
	void style_menu_pressed();
};

Lines_window::Lines_window(Point xy, int w, int h, const string& title) :
	Window{ xy, w, h, title },
	next_button{ Point{ x_max() - 150, 0 }, 70, 20, "Next point", cb_next },
	quit_button{ Point{ x_max() - 70, 0 }, 70, 20, "Quit", cb_quit },
	next_x{ Point{ x_max() - 310, 0 }, 50, 20, "next_x" },
	next_y{ Point{ x_max() - 210, 0 }, 50, 20, "next_y" },
	xy_out{ Point{ 100, 0 }, 100, 20, "current (x,y)" },
	color_menu{ Point{ x_max() - 70, 30 }, 70, 20, Menu::vertical, "color" },
	menu_button{ Point{ x_max() - 80, 30 }, 80, 20, "color menu", cb_menu },
	style_menu{ Point{ 0, 30 }, 70, 20, Menu::vertical, "style" },
	style_menu_button{ Point{ 0, 30 }, 80, 20, "style menu", cb_style_menu }
{
	attach(lines);
	lines.set_color(Color::black);
	attach(next_button);
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(xy_out);
	xy_out.put("no point");
	color_menu.attach(new Button{ Point{ 0, 0 }, 0, 0, "red", cb_red });
	color_menu.attach(new Button{ Point{ 0, 0 }, 0, 0, "blue", cb_blue });
	color_menu.attach(new Button{ Point{ 0, 0 }, 0, 0, "black", cb_black });
	attach(color_menu);
	color_menu.hide();
	attach(menu_button);
	style_menu.attach(new Button{ Point{ 0, 0 }, 0, 0, "solid", cb_solid });
	style_menu.attach(new Button{ Point{ 0, 0 }, 0, 0, "dash", cb_dash });
	style_menu.attach(new Button{ Point{ 0, 0 }, 0, 0, "dot", cb_dot });
	attach(style_menu);
	style_menu.hide();
	attach(style_menu_button);
}

void Lines_window::hide_menu()
{
	color_menu.hide();
	menu_button.show();
}

void Lines_window::hide_style_menu()
{
	style_menu.hide();
	style_menu_button.show();
}

void Lines_window::next()
{
	int x = next_x.get_int();
	int y = next_y.get_int();
	lines.add(Point{ x, y });
	cout << lines.point(lines.number_of_points() - 1).x;
	cout << lines.point(lines.number_of_points() - 1).y;

	ostringstream ss;
	ss << '(' << x << ',' << y << ')';
	xy_out.put(ss.str());

	redraw();
}

void Lines_window::red_pressed()
{
	change(Color::red);
	hide_menu();
}

void Lines_window::blue_pressed()
{
	change(Color::blue);
	hide_menu();
}

void Lines_window::black_pressed()
{
	change(Color::black);
	hide_menu();
}

void Lines_window::menu_pressed()
{
	menu_button.hide();
	color_menu.show();
}

void Lines_window::solid_pressed()
{
	change_style(Line_style::solid);
	hide_style_menu();
}

void Lines_window::dash_pressed()
{
	change_style(Line_style::dash);
	hide_style_menu();
}

void Lines_window::dot_pressed()
{
	change_style(Line_style::dot);
	hide_style_menu();
}

void Lines_window::style_menu_pressed()
{
	style_menu_button.hide();
	style_menu.show();
}
}

int main()
try {
	using namespace Graph_lib;

	Lines_window win{ Point{ 100, 100 }, 600, 400, "lines" };
	return gui_main();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}