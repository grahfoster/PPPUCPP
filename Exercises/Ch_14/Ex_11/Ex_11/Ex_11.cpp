#include "../Graph.h"
#include "../Simple_window.h"

namespace Graph_lib {

class Binary_tree : public Shape {
public:
	Binary_tree(Point, int, int, int);
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
	vector<Line*> lines;
};

Binary_tree::Binary_tree(Point tl, int w, int h, int nl) :
	width{ w }, height{ h }, num_levels{ nl }
{
	if (num_levels < 1)
		throw exception("Binary_tree() - invalid constructor argument");

	Shape::add(tl);

	const int node_height = height / num_levels;
	const int node_radius = node_height / 2;

	for (int i = 0; i < num_levels; ++i) {
		vector<Circle*> level_nodes;
		for (int j = 0; j < pow(2, i); ++j) {
			level_nodes.push_back(new Circle{ { int(point(0).x + (j + 1) * width / (pow(2, i) + 1)),
				point(0).y + i * node_height + node_radius }, node_radius / (i + 1) });
			if (i > 0)
				lines.push_back(new Line{ { level_nodes.back()->center().x,
					level_nodes.back()->center().y - node_radius / (i + 1)},
					{ nodes[i - 1][j / 2]->center().x, nodes[i - 1][j / 2]->center().y + node_radius / i } });
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

	for (Line* line : lines)
		delete line;
	lines.clear();
}

void Binary_tree::draw_lines() const
{
	for (vector<Circle*> level_nodes : nodes)
		for (Circle* node : level_nodes)
			node->draw();

	for (Line* line : lines)
		line->draw();
}

void Binary_tree::move(int dx, int dy)
{
	for (vector<Circle*> level_nodes : nodes)
		for (Circle* node : level_nodes)
			node->move(dx, dy);

	for (Line* line : lines)
		line->move(dx, dy);
}

void Binary_tree::set_color(Color col)
{
	Shape::set_color(col);

	for (vector<Circle*> level_nodes : nodes)
		for (Circle* node : level_nodes)
			node->set_color(col);

	for (Line* line : lines)
		line->set_color(col);
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

	for (Line* line : lines)
		line->set_style(ls);
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

	Binary_tree b_tree{ { 0, 0 }, s_win.x_max(), s_win.y_max(), 5 };
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