#include "../Graph.h"
#include "../Simple_window.h"

namespace Graph_lib {

struct Bar_data {
	double value;
	string text;
};

istream& operator>>(istream& is, Bar_data& bar_data)
{
	char c1;
	char c2;
	char c3;
	string text;
	double value;

	is >> c1 >> text >> c2 >> value >> c3;
	if (is.eof())
		return is;
	if (is.fail() || c1 != '(' || c2 != ',' || c3 != ')')
		throw exception("operator>>() - invalid Bar_data format");

	bar_data.value = value;
	bar_data.text = text;

	return is;
}

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
	const double min_value = 0;
	const double max_value = 20;
	const string input_file{ "Ex_09_input.txt" };

	ifstream ifs{ input_file };
	if (!ifs)
		throw exception("couldn't open file");
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);

	vector<Bar_data> bar_datas;
	for (Bar_data bar_data; ifs >> bar_data;)
		bar_datas.push_back(bar_data);

	Bar_graph b_graph{ origin, width, height, min_value, max_value, bar_datas,
		"Distribution of U.S. Middle-Aged Male Heights" };
	b_graph.set_color(Color::black);

	const int x_length = width + 25;

	Axis x_axis{ Axis::Orientation::x, origin, x_length, 0, "Height (in)" };
	x_axis.set_color(Color::black);
	x_axis.label.move(origin.x + x_length / 6, 50);

	const int y_length = height + 25;

	Axis y_axis{ Axis::Orientation::y, origin, y_length, 0, "Percent" };
	y_axis.set_color(Color::black);
	y_axis.label.move(-140, y_length / 2 + 10);

	const int num_y_labels = 10;

	vector<Text*> y_labels;
	for (int i = 0; i <= num_y_labels; ++i) {
		const int y_value = i * (max_value - min_value) / num_y_labels;
		string y_text{ to_string(y_value) };
		y_labels.push_back(new Text{ { origin.x - 25, origin.y - i * y_length / num_y_labels }, y_text });
		y_labels.back()->set_color(Color::black);
		s_win.attach(*y_labels.back());
	}

	s_win.attach(b_graph);
	s_win.attach(x_axis);
	s_win.attach(y_axis);

	s_win.wait_for_button();

	for (Text* y_label : y_labels)
		delete y_label;
	y_labels.clear();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}