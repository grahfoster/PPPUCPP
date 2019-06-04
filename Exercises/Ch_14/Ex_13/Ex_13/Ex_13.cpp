#include "../Graph.h"
#include "../Simple_window.h"

const double pi = atan(1) * 4;

namespace Graph_lib {

class Arrow : public Line {
public:
	Arrow(Point, Point, double, int, bool, Color);

	void move(int, int);
	void set_color(Color);
	void set_style(Line_style);
	void draw_lines() const;
private:
	Polygon head;
};

Arrow::Arrow(Point p1, Point p2, double head_angle, int head_size, bool is_down, Color col) :
	Line{ p1, p2 }
{
	const double line_angle = atan2(p2.y - p1.y, p2.x - p1.x);

	if (is_down) {
		head.add(p1);
		head.add({ int(p1.x + head_size * cos(line_angle + head_angle)),
			int(p1.y + head_size * sin(line_angle + head_angle)) });
		head.add({ int(p1.x + head_size * cos(line_angle - head_angle)),
			int(p1.y + head_size * sin(line_angle - head_angle)) });
	}
	else {
		head.add(p2);
		head.add({ int(p2.x - head_size * cos(line_angle + head_angle)),
			int(p2.y - head_size * sin(line_angle + head_angle)) });
		head.add({ int(p2.x - head_size * cos(line_angle - head_angle)),
			int(p2.y - head_size * sin(line_angle - head_angle)) });
	}

	set_color(col);
	head.set_fill_color(col);
}

void Arrow::move(int dx, int dy)
{
	Line::move(dx, dy);

	head.move(dx, dy);
}

void Arrow::set_color(Color col)
{
	Line::set_color(col);

	head.set_color(col);
}

void Arrow::set_style(Line_style ls)
{
	Line::set_style(ls);

	head.set_style(ls);
}

void Arrow::draw_lines() const
{
	Line::draw_lines();

	head.draw();
}

class Binary_tree : public Shape {
public:
	Binary_tree(Point, int, int, int, bool, Color);
	~Binary_tree();

	void draw_lines() const override;

	void move(int, int);
	void set_color(Color);
	void set_fill_color(Color);
	void set_style(Line_style);
private:
	int width;
	int height;
	int num_levels;
	vector<vector<Circle*>> nodes;
	vector<Arrow*> arrows;
};

Binary_tree::Binary_tree(Point tl, int w, int h, int nl, bool is_down, Color arrow_col) :
	width{ w }, height{ h }, num_levels{ nl }
{
	if (num_levels < 1)
		throw exception("Binary_tree() - invalid constructor argument");

	Shape::add(tl);

	const int node_height = height / num_levels;
	const int node_radius = node_height / 2;
	const double head_angle = 15 * pi / 180;
	const int head_size = 10;

	for (int i = 0; i < num_levels; ++i) {
		vector<Circle*> level_nodes;
		for (int j = 0; j < pow(2, i); ++j) {
			level_nodes.push_back(new Circle{ { int(point(0).x + (j + 1) * width / (pow(2, i) + 1)),
				point(0).y + i * node_height + node_radius }, node_radius / (i + 1) });
			if (i > 0)
				arrows.push_back(new Arrow{ { level_nodes.back()->center().x,
					level_nodes.back()->center().y - node_radius / (i + 1)},
					{ nodes[i - 1][j / 2]->center().x, nodes[i - 1][j / 2]->center().y + node_radius / i },
					head_angle, head_size, is_down, arrow_col });
		}
		nodes.push_back(level_nodes);
	}
}

Binary_tree::~Binary_tree()
{
	for (vector<Circle*> level_nodes : nodes)
		for (Circle* node : level_nodes)
			delete node;
	nodes.clear();

	for (Arrow* arrow : arrows)
		delete arrow;
	arrows.clear();
}

void Binary_tree::draw_lines() const
{
	for (vector<Circle*> level_nodes : nodes)
		for (Circle* node : level_nodes)
			node->draw();

	for (Arrow* arrow : arrows)
		arrow->draw();
}

void Binary_tree::move(int dx, int dy)
{
	for (vector<Circle*> level_nodes : nodes)
		for (Circle* node : level_nodes)
			node->move(dx, dy);

	for (Arrow* arrow : arrows)
		arrow->move(dx, dy);
}

void Binary_tree::set_color(Color col)
{
	Shape::set_color(col);

	for (vector<Circle*> level_nodes : nodes)
		for (Circle* node : level_nodes)
			node->set_color(col);
}

void Binary_tree::set_fill_color(Color col)
{
	Shape::set_fill_color(col);

	for (vector<Circle*> level_nodes : nodes)
		for (Circle* node : level_nodes)
			node->set_fill_color(col);
}

void Binary_tree::set_style(Line_style ls)
{
	Shape::set_style(ls);

	for (vector<Circle*> level_nodes : nodes)
		for (Circle* node : level_nodes)
			node->set_style(ls);

	for (Arrow* arrow : arrows)
		arrow->set_style(ls);
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

	Binary_tree b_tree{ { 0, 0 }, s_win.x_max(), s_win.y_max(), 5, true, Color::blue };
	b_tree.set_color(Color::black);

	s_win.attach(b_tree);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}