#include "../Graph.h"
#include "../Simple_window.h"

namespace Graph_lib {

struct Data_point {
	string text;
	double x_value;
	double y_value;
};

class Scaler {
public:
	Scaler(int bc, double mv, double s) : base_coord{ bc }, min_value{ mv }, scale{ s } {}
	int operator()(double value) const { return base_coord + (value - min_value) * scale; }
private:
	int base_coord;
	double min_value;
	double scale;
};

istream& operator>>(istream& is, Data_point& data_point)
{
	char c1;
	char c2;
	string t;
	double xv;
	double yv;

	is >> c1 >> t >> xv >> yv >> c2;
	if (is.eof())
		return is;
	if (is.fail() || c1 != '(' || c2 != ')')
		throw exception("operator>>() - invalid Data_point format");

	data_point.text = t;
	data_point.x_value = xv;
	data_point.y_value = yv;

	return is;
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
	const int x_length = s_win.x_max() * 3 / 4;
	const int y_length = s_win.y_max() * 3 / 4;
	const int num_notches = 10;
	const string x_label{ "Population (millions)" };
	const string y_label{ "GDP (trillions USD)" };
	const string graph_text{ "GDP and Population by Country" };

	Axis x_axis{ Axis::Orientation::x, origin, x_length, num_notches, x_label };
	x_axis.set_color(Color::black);
	x_axis.label.move(origin.x + x_length / 6, 50);

	Axis y_axis{ Axis::Orientation::y, origin, y_length, num_notches, y_label };
	y_axis.set_color(Color::black);
	y_axis.label.move(-150, y_length / 2 + 10);

	Text graph_label{ { origin.x + x_length / 2, origin.y - y_length }, graph_text };
	graph_label.set_color(Color::black);
	graph_label.set_font_size(20);

	const string input_file{ "Ex_10_input.txt" };

	const double x_min = 0;
	const double x_max = 250;
	const double y_min = 0;
	const double y_max = 6;
	const double x_scale = double(x_length) / (x_max - x_min);
	const double y_scale = double(y_length) / (y_max - y_min);
	const Scaler x_scaler{ origin.x, x_min, x_scale };
	const Scaler y_scaler{ origin.y, y_min, -y_scale };

	ifstream ifs{ input_file };
	if (!ifs)
		throw exception("couldn't open file");
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);

	vector<Data_point> data_points;
	Marks points{ "x" };
	vector<Text*> point_labels;
	for (Data_point data_point; ifs >> data_point;) {
		data_points.push_back(data_point);
		points.add({ x_scaler(data_point.x_value), y_scaler(data_point.y_value) });
		point_labels.push_back(new Text{ { points.point(points.number_of_points() - 1).x + 5,
			points.point(points.number_of_points() - 1).y - 5 }, data_point.text });
		point_labels.back()->set_color(Color::black);
		s_win.attach(*point_labels.back());
	}

	vector<Text*> y_labels;
	for (int i = 0; i <= num_notches; ++i) {
		const double y_value = i * (y_max - y_min) / num_notches;
		string y_text{ to_string(y_value) };
		y_labels.push_back(new Text{ { origin.x - 25, origin.y - i * y_length / num_notches },
			y_text.substr(0, 3) });
		y_labels.back()->set_color(Color::black);
		s_win.attach(*y_labels.back());
	}

	vector<Text*> x_labels;
	for (int i = 0; i <= num_notches; ++i) {
		const int x_value = i * (x_max - x_min) / num_notches;
		string x_text{ to_string(x_value) };
		x_labels.push_back(new Text{ { origin.x + i * x_length / num_notches, origin.y +25 },
			x_text });
		x_labels.back()->set_color(Color::black);
		s_win.attach(*x_labels.back());
	}

	s_win.attach(x_axis);
	s_win.attach(y_axis);
	s_win.attach(graph_label);
	s_win.attach(points);

	s_win.wait_for_button();

	for (Text* point_label : point_labels)
		delete point_label;
	point_labels.clear();

	for (Text* y_label : y_labels)
		delete y_label;
	y_labels.clear();

	for (Text* x_label : x_labels)
		delete x_label;
	x_labels.clear();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}