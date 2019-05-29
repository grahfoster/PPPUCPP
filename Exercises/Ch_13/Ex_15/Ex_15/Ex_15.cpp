#include "../Graph.h"
#include "../Simple_window.h"

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

	const int width = 25;

	Vector_ref<Right_triangle> r_tris;
	for (int i = 0; (i + 1) * width < s_win.x_max(); ++i)
		for (int j = 0; (j + 1) * width < s_win.y_max(); ++j) {
			r_tris.push_back(new Right_triangle{ { i * width, j * width }, width, width });
			r_tris.push_back(new Right_triangle{ { (i + 1) * width, (j + 1) * width }, -width, -width });
			r_tris[r_tris.size() - 2].set_color(Color::black);
			r_tris[r_tris.size() - 1].set_color(Color::black);
			s_win.attach(r_tris[r_tris.size() - 2]);
			s_win.attach(r_tris[r_tris.size() - 1]);
			
		}

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}