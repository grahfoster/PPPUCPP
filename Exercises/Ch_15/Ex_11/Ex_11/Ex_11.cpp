#include "../Graph.h"
#include "../Simple_window.h"

namespace Graph_lib {

struct Data_point {
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
	char c3;
	double xv;
	double yv;

	is >> c1 >> xv >> c2 >> yv >> c3;
	if (is.eof())
		return is;
	if (is.fail() || c1 != '(' || c2 != ',' || c3 != ')')
		throw exception("operator>>() - invalid Data_point format");

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
	const int num_notches = 11;
	const string x_label{ "Month" };
	const string y_label{ "Average High (°F)" };
	const string graph_text{ "Average High Temperature by Month in Rochester, NY, and Rochester, MN" };

	Axis x_axis{ Axis::Orientation::x, origin, x_length, num_notches, x_label };
	x_axis.set_color(Color::black);
	x_axis.label.move(origin.x + x_length / 6, 50);

	Axis y_axis{ Axis::Orientation::y, origin, y_length, num_notches, y_label };
	y_axis.set_color(Color::black);
	y_axis.label.move(-150, y_length / 2 + 10);

	Text graph_label{ { origin.x + x_length / 2, origin.y - y_length }, graph_text };
	graph_label.set_color(Color::black);
	graph_label.set_font_size(20);
	graph_label.move(-int(graph_text.size() * graph_label.font_size() / 4), 0);

	const double x_min = 1;
	const double x_max = 12;
	const double y_min = 20;
	const double y_max = 90;
	const double x_scale = double(x_length) / (x_max - x_min);
	const double y_scale = double(y_length) / (y_max - y_min);
	const Scaler x_scaler{ origin.x, x_min, x_scale };
	const Scaler y_scaler{ origin.y, y_min, -y_scale };

	const string input_file1{ "Ex_11_input1.txt" };
	ifstream ifs{ input_file1 };
	if (!ifs)
		throw exception("couldn't open file");
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);

	vector<Data_point> data_points1;
	Marked_polyline temps1{ "x" };
	for (Data_point data_point; ifs >> data_point;) {
		data_points1.push_back(data_point);
		temps1.add({ x_scaler(data_point.x_value), y_scaler(data_point.y_value) });
	}
	temps1.set_color(Color::red);

	const string input_file2{ "Ex_11_input2.txt" };
	ifs.close();
	ifs.open(input_file2);
	if (!ifs)
		throw exception("couldn't open file");

	vector<Data_point> data_points2;
	Marked_polyline temps2{ "x" };
	for (Data_point data_point; ifs >> data_point;) {
		data_points2.push_back(data_point);
		temps2.add({ x_scaler(data_point.x_value), y_scaler(data_point.y_value) });
	}
	temps2.set_color(Color::blue);

	const vector<string> months{
		"January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November", "December"
	};

	vector<Text*> y_labels;
	for (int i = 0; i <= num_notches; ++i) {
		const int y_value = i * (y_max - y_min) / num_notches + y_min;
		string y_text{ to_string(y_value) };
		y_labels.push_back(new Text{ { origin.x - 25, origin.y - i * y_length / num_notches },
			y_text });
		y_labels.back()->set_color(Color::black);
		s_win.attach(*y_labels.back());
	}

	vector<Text*> x_labels;
	for (int i = 0; i <= num_notches; ++i) {
		string x_text{ months[i] };
		x_labels.push_back(new Text{ { origin.x + i * x_length / num_notches, origin.y + 25 },
			x_text });
		x_labels.back()->set_color(Color::black);
		s_win.attach(*x_labels.back());
	}

	s_win.attach(x_axis);
	s_win.attach(y_axis);
	s_win.attach(graph_label);
	s_win.attach(temps1);
	s_win.attach(temps2);

	s_win.wait_for_button();

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