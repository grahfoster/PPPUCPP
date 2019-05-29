#include "../Graph.h"
#include "../Simple_window.h"

const double pi = atan(1) * 4;

namespace Graph_lib {

class Right_triangle : public Polygon {
public:
	Right_triangle(Point, int, int);

	int width() { return w; }
	int height() { return h; }
private:
	int w;
	int h;

	void add(Point p) { Polygon::add(p); }
};

Right_triangle::Right_triangle(Point p, int width, int height) :
	w{ width }, h{ height }
{
	add(p);
	add({ p.x + width, p.y });
	add({ p.x, p.y + height });
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

	const double a1 = 22.5;
	const double a2 = 67.5;
	const int width1 = 100;
	const int height = 100 * tan(67.5 * pi / 180);
	const int width2 = (height - width1) / 2;
	Vector_ref<Right_triangle> r_tris;
	r_tris.push_back(new Right_triangle{ { 200, 200 }, width1, height });
	r_tris.push_back(new Right_triangle{ { 300, 200 + height }, -width1, -height });
	r_tris.push_back(new Right_triangle{ { 200 - width2, 200 + width2 }, height, width1 });
	r_tris.push_back(new Right_triangle{ { 200 - width2 + height, 200 + width2 + width1 }, -height, -width1 });
	r_tris.push_back(new Right_triangle{ { 200, 200 + width2 }, -width2, -width2 });
	r_tris.push_back(new Right_triangle{ { 200 + width1, 200 + width2 }, width2, -width2 });
	r_tris.push_back(new Right_triangle{ { 200 + width1, 200 + height - width2 }, width2, width2 });
	r_tris.push_back(new Right_triangle{ { 200, 200 + height - width2 }, -width2, width2 });

	for (int i = 0; i < r_tris.size(); ++i) {
		r_tris[i].set_color(Color(i));
		s_win.attach(r_tris[i]);
	}

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}