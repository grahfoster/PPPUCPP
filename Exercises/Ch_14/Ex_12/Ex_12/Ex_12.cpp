#include "../Graph.h"
#include "../Simple_window.h"

const double pi = atan(1) * 4;

namespace Graph_lib {

class Regular_polygon : public Polygon {
public:
	Regular_polygon(Point, int, int);
private:
	void add(Point p) { Polygon::add(p); }
};

Regular_polygon::Regular_polygon(Point center, int radius, int num_sides)
{
	if (num_sides < 3)
		throw exception("Regular_polygon() - invalid constructor argument");

	for (int i = 0; i < num_sides; ++i) {
		add({ int(center.x + radius * cos(i * 360 / num_sides * pi / 180)),
			int(center.y - radius * sin(i * 360 / num_sides * pi / 180)) });
	}
}

class Binary_tree : public Shape {
public:
	Binary_tree(Point, int, int, int);
	~Binary_tree();

	virtual void set_nodes();

	void draw_lines() const override;
	int get_width() const { return width; }
	int get_height() const { return height; }
	int get_num_levels() const { return num_levels; }
	Shape* get_node(int i, int j) const { return nodes[i][j]; }
	Line* get_line(int i) const { return lines[i]; }

	void move(int, int);
	void set_color(Color);
	void set_fill_color(Color);
	void set_style(Line_style);
	void add_level_nodes(const vector<Shape*>& level_nodes) { nodes.push_back(level_nodes); }
	void add_line(Line* line) { lines.push_back(line); }
private:
	int width;
	int height;
	int num_levels;
	vector<vector<Shape*>> nodes;
	vector<Line*> lines;
};

Binary_tree::Binary_tree(Point tl, int w, int h, int nl) :
	width{ w }, height{ h }, num_levels{ nl }
{
	if (num_levels < 1)
		throw exception("Binary_tree() - invalid constructor argument");

	Shape::add(tl);
}

Binary_tree::~Binary_tree()
{
	for (int i = 0; i < nodes.size(); ++i)
		for (int j = 0; j < nodes[i].size(); ++j)
			delete nodes[i][j];
	nodes.clear();

	for (Line* line : lines)
		delete line;
	lines.clear();
}

void Binary_tree::set_nodes()
{
	const int node_height = height / num_levels;
	const int node_radius = node_height / 2;

	for (int i = 0; i < num_levels; ++i) {
		vector<Shape*> level_nodes;
		for (int j = 0; j < pow(2, i); ++j) {
			level_nodes.push_back(new Circle{ { int(point(0).x + (j + 1) * width / (pow(2, i) + 1)),
				point(0).y + i * node_height + node_radius }, node_radius / (i + 1) });
			if (i > 0)
				lines.push_back(new Line{ { level_nodes.back()->point(0).x + node_radius / (i + 1),
					level_nodes.back()->point(0).y }, { nodes[i - 1][j / 2]->point(0).x + node_radius / i,
					nodes[i - 1][j / 2]->point(0).y + 2 * node_radius / i } });
		}
		nodes.push_back(level_nodes);
	}
}

void Binary_tree::draw_lines() const
{
	for (vector<Shape*> level_nodes : nodes)
		for (Shape* node : level_nodes)
			node->draw();

	for (Line* line : lines)
		line->draw();
}

void Binary_tree::move(int dx, int dy)
{
	for (vector<Shape*> level_nodes : nodes)
		for (Shape* node : level_nodes)
			node->move(dx, dy);

	for (Line* line : lines)
		line->move(dx, dy);
}

void Binary_tree::set_color(Color col)
{
	Shape::set_color(col);

	for (vector<Shape*> level_nodes : nodes)
		for (Shape* node : level_nodes)
			node->set_color(col);

	for (Line* line : lines)
		line->set_color(col);
}

void Binary_tree::set_fill_color(Color col)
{
	Shape::set_fill_color(col);

	for (vector<Shape*> level_nodes : nodes)
		for (Shape* node : level_nodes)
			node->set_fill_color(col);
}

void Binary_tree::set_style(Line_style ls)
{
	Shape::set_style(ls);

	for (vector<Shape*> level_nodes : nodes)
		for (Shape* node : level_nodes)
			node->set_style(ls);

	for (Line* line : lines)
		line->set_style(ls);
}

class Binary_tree_poly : public Binary_tree {
public:
	Binary_tree_poly(Point tl, int w, int h, int nl, int nns) :
		Binary_tree{ tl, w, h, nl }, num_node_sides{ nns } {}

	void set_nodes() override;
private:
	int num_node_sides;
};

void Binary_tree_poly::set_nodes()
{
	const int node_height = get_height() / get_num_levels();
	const int node_radius = node_height / 2;

	for (int i = 0; i < get_num_levels(); ++i) {
		vector<Shape*> level_nodes;
		for (int j = 0; j < pow(2, i); ++j) {
			level_nodes.push_back(
				new Regular_polygon{ { int(point(0).x + (j + 1) * get_width() / (pow(2, i) + 1)),
				point(0).y + i * node_height + node_radius }, node_radius / (i + 1), num_node_sides });
			if (i > 0)
				add_line(new Line{ { level_nodes.back()->point(0).x - node_radius / (i + 1),
					level_nodes.back()->point(0).y - node_radius / (i + 1) },
					{ get_node(i - 1, j / 2)->point(0).x - node_radius / i,
					get_node(i - 1, j / 2)->point(0).y + node_radius / i } });
		}
		add_level_nodes(level_nodes);
	}
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

	Binary_tree_poly b_tree_poly{ { 0, 0 }, s_win.x_max(), s_win.y_max(), 5, 4 };
	b_tree_poly.set_nodes();
	b_tree_poly.set_color(Color::black);

	s_win.attach(b_tree_poly);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}