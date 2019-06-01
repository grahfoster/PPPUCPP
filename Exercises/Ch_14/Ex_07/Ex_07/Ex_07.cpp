#include "../Graph.h"
#include "../Simple_window.h"

namespace Graph_lib {

class Striped_closed_polyline : public Closed_polyline {
public:
	using Closed_polyline::Closed_polyline;

	void draw_lines() const override;
private:
	vector<Line*> find_intersections(Line&) const;
	Point line_intersect(Point, Point, Point, Point) const;
};

void Striped_closed_polyline::draw_lines() const
{
	int min_x = 0;
	int max_x = 0;
	int min_y = 0;
	int max_y = 0;
	for (int i = 0; i < number_of_points(); ++i) {
		if (i == 0) {
			min_x = point(i).x;
			max_x = min_x;
			min_y = point(i).y;
			max_y = min_y;
		}
		if (point(i).x < min_x)
			min_x = point(i).x;
		if (point(i).x > max_x)
			max_x = point(i).x;
		if (point(i).y < min_y)
			min_y = point(i).y;
		if (point(i).y > max_y)
			max_y = point(i).y;
	}

	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		fl_begin_complex_polygon();
		for (int i = 0; i < max_y - min_y - 1; i += 2) {
			Line line{ { min_x, min_y + i }, { max_x, min_y + i } };
			vector<Line*> i_lines{ find_intersections(line) };
			for (Line* i_line : i_lines) {
				fl_line(i_line->point(0).x, i_line->point(0).y, i_line->point(1).x, i_line->point(1).y);
				delete i_line;
			}
		}
		fl_end_complex_polygon();
		fl_color(color().as_int());
	}

	if (color().visibility())
		Shape::draw_lines();

	if (color().visibility())
		fl_line(point(number_of_points() - 1).x, point(number_of_points() - 1).y, point(0).x, point(0).y);
}

vector<Line*> Striped_closed_polyline::find_intersections(Line& line) const
{
	vector<Line*> i_lines;
	vector<int> xs;
	for (int i = 0; i < number_of_points(); ++i) {
		Point temp = line_intersect(line.point(0), line.point(1), point(i),
			point((i + 1) % number_of_points()));
		if (temp.x >= 0)
			xs.push_back(temp.x);
		sort(xs.begin(), xs.end());
	}

	for (int i = 0; i < xs.size(); i += 2)
		i_lines.push_back(new Line{ { line.point(0).x + xs[i], line.point(0).y },
			{ line.point(0).x + xs[i + 1], line.point(0).y } });
	return i_lines;
}

Point Striped_closed_polyline::line_intersect(Point p1, Point p2, Point p3, Point p4) const
{
	int x1 = p1.x;
	int x2 = p2.x;
	int x3 = p3.x;
	int x4 = p4.x;
	int y1 = p1.y;
	int y2 = p2.y;
	int y3 = p3.y;
	int y4 = p4.y;
	double denom = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
	if ((y1 > y3 && y1 > y4) || (y1 < y3 && y1 < y4))
		return { -1, -1 };
	return { int(((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denom * (x2 - x1)), 0 };
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

	Striped_closed_polyline s_c_pl;
	s_c_pl.add({ 200, 200 });
	s_c_pl.add({ 450, 250 });
	s_c_pl.add({ 400, 100 });
	s_c_pl.add({ 200, 400 });
	s_c_pl.set_color(Color::black);
	s_c_pl.set_fill_color(Color::blue);

	s_win.attach(s_c_pl);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}