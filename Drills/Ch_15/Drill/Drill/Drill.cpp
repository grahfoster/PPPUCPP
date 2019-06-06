#include "../Graph.h"
#include "../Simple_window.h"

//double one(double x) { return 1; }
//double slope(double x) { return x / 2; }
//double square(double x) { return x * x; }
//double sloping_cos(double x) { return cos(x) + slope(x); }

struct Person {
	Person() {}
	Person(string, string, int);

	string first_name() const { return fn; }
	string second_name() const { return sn; }
	int age() const { return a; }
private:
	string fn;
	string sn;
	int a = 0;
};

Person::Person(string fn, string sn, int a) : 
	fn{ fn }, sn{ sn }, a{ a }
{
	const string bad_chars{ ";:\"'[]*&^%$#@!" };
	for (char bad_char : bad_chars) {
		if (fn.find(bad_char) != string::npos)
			error("Person() - invalid first name");
		if (sn.find(bad_char) != string::npos)
			error("Person() - invalid second name");
	}

	if (0 > a || a >= 150)
		error("Person() - invalid age");
}

istream& operator>>(istream& is, Person& pers)
{
	string fn;
	string sn;
	int a = 0;
	is >> fn >> sn >> a;
	if (is.fail() && !is.eof())
		error("operator>>() - invalid Person format");

	pers = Person{ fn, sn, a };

	return is;
}

ostream& operator<<(ostream& os, const Person& pers)
{
	os << pers.first_name() << ' ' << pers.second_name() << " (" << pers.age() << ')';

	return os;
}

int main()
try {
	using namespace Graph_lib;

	/*const Point win_tl{ x_max() / 4, y_max() / 4 };
	const int win_width = 600;
	const int win_height = 600;
	const string win_name{ "Function graphs" };
	Graph_lib::Window win{ win_tl, win_width, win_height, win_name };*/

	/*const int length = 400;
	const int notch_dist = 20;
	const string label{ "1 = = " + to_string(notch_dist) + " pixels" };
	const int num_notches = length / notch_dist;
	const Point origin{ win_width / 2, win_width / 2 };

	Axis x_axis{ Axis::Orientation::x, { origin.x - length / 2, origin.y }, length, num_notches, label };
	x_axis.set_color(Color::red);

	Axis y_axis{ Axis::Orientation::y, { origin.x, origin.y + length / 2 }, length, num_notches, label };
	y_axis.set_color(Color::red);

	const int l_range = -10;
	const int u_range = 11;
	const int count = 400;
	const int x_scale = 20;
	const int y_scale = 20;
	const string f_slope_label{ "x / 2" };

	Function f_one{ one, l_range, u_range, origin, count, x_scale, y_scale };
	f_one.set_color(Color::black);

	Function f_slope{ slope, l_range, u_range, origin, count, x_scale, y_scale };
	f_slope.set_color(Color::black);

	Text f_slope_text{ f_slope.point(0), f_slope_label };
	f_slope_text.set_color(Color::black);

	Function f_square{ square, l_range, u_range, origin, count, x_scale, y_scale };
	f_square.set_color(Color::black);

	Function f_cos{ cos, l_range, u_range, origin, count, x_scale, y_scale };
	f_cos.set_color(Color::blue);

	Function f_sloping_cos{ sloping_cos, l_range, u_range, origin, count, x_scale, y_scale };
	f_sloping_cos.set_color(Color::black);

	win.attach(x_axis);
	win.attach(y_axis);
	win.attach(f_one);
	win.attach(f_slope);
	win.attach(f_slope_text);
	win.attach(f_square);
	win.attach(f_cos);
	win.attach(f_sloping_cos);

	gui_main();*/

	/*Person pers{ "Goofy", 63 };
	cout << pers.name << " (" << pers.age << ")\n";*/

	/*Person pers;
	cin >> pers;
	cout << pers << '\n';*/

	Person pers;
	vector<Person> persns;
	while (cin >> pers)
		persns.push_back(pers);
	for (Person pers : persns)
		cout << pers << '\n';
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}