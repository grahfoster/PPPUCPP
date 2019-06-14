#include "../Graph.h"
#include "../Simple_window.h"

namespace Graph_lib {

template <class T>
class Funct : public Shape {
public:
	Funct(Fct, double, double, Point, int = 100, double = 25, double = 25);

	void reset_all(Fct, double, double, Point, double, double);
	void reset_fct(Fct f) { reset_all(f, range1, range2, origin, xscale, yscale); }
	void reset_range1(double r1) { reset_all(fct, r1, range2, origin, xscale, yscale); }
	void reset_range2(double r2) { reset_all(fct, range1, r2, origin, xscale, yscale); }
	void reset_origin(Point o) { reset_all(fct, range1, range2, o, xscale, yscale); }
	void reset_xscale(double xs) { reset_all(fct, range1, range2, origin, xs, yscale); }
	void reset_yscale(double ys) { reset_all(fct, range1, range2, origin, xscale, ys); }
private:
	Fct* fct;
	double range1;
	double range2;
	Point origin;
	int count;
	double xscale;
	double yscale;
};

template<class T>
Funct<T>::Funct(Fct f, double r1, double r2, Point o, int c, double xs, double ys) :
	count{ c }
{
	reset_all(f, r1, r2, o, xs, ys);
}

template<class T>
void Funct<T>::reset_all(Fct f, double r1, double r2, Point o, double xs, double ys)
{
	fct = f;
	range1 = r1;
	range2 = r2;
	origin = o;
	xscale = xs;
	yscale = ys;

	if (range2 - range1 <= 0) error("bad graphing range");
	if (count <= 0) error("non-positive graphing count");
	double dist = (range2 - range1) / count;
	double r = range1;

	if (number_of_points() == count)
		for (int i = 0; i < count; ++i) {
			set_point(i, Point(origin.x + int(r * xscale), origin.y - int(T(fct(r)) * yscale)));
			r += dist;
		}
	else
		for (int i = 0; i < count; ++i) {
			add(Point(origin.x + int(r * xscale), origin.y - int(T(fct(r)) * yscale)));
			r += dist;
		}
}

double fct(double x) { return sqrt(x); }
}

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 4, y_max() / 4 };
	const int win_width = x_max() / 2;
	const int win_height = y_max() / 2;
	const string win_name{ "My window" };
	Simple_window s_win{ win_tl, win_width, win_height, win_name };

	Funct<int> funct{ fct, -10, 10, { s_win.x_max() / 2, s_win.y_max() / 2 } };
	funct.set_color(Color::black);

	s_win.attach(funct);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}