#include "../Graph.h"
#include "../Simple_window.h"

namespace Graph_lib {

struct Bar_data {
	double value;
	string text;
};

struct Bar {
	Rectangle* rect;
	Text* label;
};

class Bar_graph : public Shape {
public:
	Bar_graph(Point, int, int, double, double, const vector<Bar_data>&, const string&);
	~Bar_graph();

	void draw_lines() const override;
	int get_width() const { return width; }
	int get_height() const { return height; }
	Bar get_bar(int i) const { return bars[i]; }
	Text* get_label() const { return label; }

	void move(int, int) override;
	void set_color(Color);
	void set_fill_color(Color);
	void set_style(Line_style);
private:
	int width;
	int height;
	vector<Bar> bars;
	Text* label;
};

Bar_graph::Bar_graph(Point origin, int w, int h, double min_value, double max_value,
	const vector<Bar_data>& bar_datas, const string& text) :
	width{ w }, height{ h }, label{ new Text{ { origin.x + width / 2, origin.y - height }, text } }
{
	if (bar_datas.empty())
		throw exception("Bar_graph() - empty bar data vector");

	add(origin);

	const int bar_width = width / bar_datas.size();

	for (int i = 0; i < bar_datas.size(); ++i) {
		if (bar_datas[i].value < min_value)
			throw exception("Bar_graph() - value less than specified min");
		if (bar_datas[i].value > max_value)
			throw exception("Bar_graph() - value greater than specified max");

		int bar_height = (bar_datas[i].value - min_value) / (max_value - min_value) * height;
		if (bar_height == 0)
			bar_height = 1;
		bars.push_back(Bar{
			new Rectangle{ { origin.x + i * bar_width, origin.y - bar_height }, bar_width, bar_height },
			new Text { { origin.x + i * bar_width + bar_width / 2, origin.y + 25 },	bar_datas[i].text } });
	}
}

Bar_graph::~Bar_graph()
{
	for (Bar bar : bars) {
		delete bar.label;
		delete bar.rect;
	}
	bars.clear();
	delete label;
}

void Bar_graph::draw_lines() const
{
	for (Bar bar : bars) {
		bar.label->draw();
		bar.rect->draw();
	}
	label->draw();
}

void Bar_graph::move(int dx, int dy)
{
	Shape::move(dx, dy);

	for (Bar bar : bars) {
		bar.label->move(dx, dy);
		bar.rect->move(dx, dy);
	}
	label->move(dx, dy);
}

void Bar_graph::set_color(Color col)
{
	for (Bar bar : bars) {
		bar.label->set_color(col);
		bar.rect->set_color(col);
	}
	label->set_color(col);
}

void Bar_graph::set_fill_color(Color col)
{
	for (Bar bar : bars)
		bar.rect->set_fill_color(col);
}

void Bar_graph::set_style(Line_style ls)
{
	for (Bar bar : bars)
		bar.rect->set_style(ls);
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
	const vector<double> values{ 1, -2.5, 33, -45, 95.3 };
	const vector<string> texts{ "value 1", "value 2", "value 3", "value 4", "value 5" };
	
	vector<Bar_data> bar_datas;
	for (int i = 0; i < values.size(); ++i)
		bar_datas.push_back(Bar_data{ values[i], texts[i] });

	Bar_graph b_graph{ origin, width, height, -100, 100, bar_datas, "Bar Graph Example" };
	b_graph.set_color(Color::black);
	b_graph.set_fill_color(Color::blue);
	b_graph.set_style(Line_style{ Line_style::solid, 2 });
	b_graph.get_bar(0).rect->set_fill_color(Color::green);
	b_graph.get_bar(2).label->set_color(Color::red);
	b_graph.get_bar(4).label->set_label("VALUE 5");
	b_graph.get_label()->set_font_size(20);

	s_win.attach(b_graph);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}