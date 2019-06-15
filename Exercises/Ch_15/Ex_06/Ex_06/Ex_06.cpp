#include "../Graph.h"
#include "../Simple_window.h"

namespace Graph_lib {

class Bar_graph : public Shape {
public:
	Bar_graph(Point, int, int, double, double, const vector<double>&);
	~Bar_graph();

	void draw_lines() const override;
	int get_width() const { return width; }
	int get_height() const { return height; }

	void move(int, int) override;
private:
	int width;
	int height;
	vector<Rectangle*> bars;
};

Bar_graph::Bar_graph(Point origin, int w, int h, double min_value, double max_value,
	const vector<double>& values) :
	width{ w }, height{ h }
{
	if (values.empty())
		throw exception("Bar_graph() - empty bar data vector");

	add(origin);

	const int bar_width = width / values.size();

	for (int i = 0; i < values.size(); ++i) {
		if (values[i] < min_value)
			throw exception("Bar_graph() - value less than specified min");
		if (values[i] > max_value)
			throw exception("Bar_graph() - value greater than specified max");

		int bar_height = (values[i] - min_value) / (max_value - min_value) * height;
		if (bar_height == 0)
			bar_height = 1;
		bars.push_back(new Rectangle{ { origin.x + i * bar_width, origin.y - bar_height },
			bar_width, bar_height });
		bars.back()->set_color(Color::black);
	}
}

Bar_graph::~Bar_graph()
{
	for (Rectangle* bar : bars)
		delete bar;
	bars.clear();
}

void Bar_graph::draw_lines() const
{
	for (Rectangle* bar : bars)
		bar->draw();
}

void Bar_graph::move(int dx, int dy)
{
	Shape::move(dx, dy);

	for (Rectangle* bar : bars)
		bar->move(dx, dy);
}
}

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 8, y_max() / 8 };
	const int win_width = x_max() * 3 / 4;
	const int win_height = y_max() * 3 / 4;
	const string win_name{ "My window" };
	Simple_window s_win{ win_tl, win_width, win_height, win_name };

	const Point origin{ s_win.x_max() / 8, s_win.y_max() * 7 / 8 };
	const int width = s_win.x_max() * 3 / 4;
	const int height = s_win.y_max() * 3 / 4;
	const vector<double> values{ 1, -2.5, 33, -45, 95.3, 17.77, -3, -4, 55.5, 10, 11, -42.9 };
	Bar_graph b_graph{ origin, width, height, -100, 100, values };

	s_win.attach(b_graph);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}