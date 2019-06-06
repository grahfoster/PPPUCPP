#include "../Graph.h"
#include "../Simple_window.h"

namespace Graph_lib {

class Arrow : public Line {
public:
	Arrow(Point, Point, double, int);

	void draw_lines() const override;

	void move(int, int) override;
	void set_color(Color);
	void set_style(Line_style);
private:
	Polygon head;
};

Arrow::Arrow(Point p1, Point p2, double head_angle, int head_size) :
	Line{ p1, p2 }
{
	const double line_angle = atan2(p2.y - p1.y, p2.x - p1.x);
	head.add(p1);
	head.add({ int(p1.x + head_size * cos(line_angle + head_angle)),
		int(p1.y + head_size * sin(line_angle + head_angle)) });
	head.add({ int(p1.x + head_size * cos(line_angle - head_angle)),
		int(p1.y + head_size * sin(line_angle - head_angle)) });
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
	head.set_fill_color(col);
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

class Modular_tree : public Shape {
public:
	Modular_tree(Point, int, int, int);
	~Modular_tree();

	void draw_lines() const override;

	void add_nodes(int, int, int, int);
	void put_label(int, int, const string&);
	void move(int, int) override;
	void set_color(Color);
	void set_fill_color(Color);
	void set_style(Line_style);
private:
	const double pi = atan(1) * 4;
	const double head_angle = 30 * pi / 180;
	const int head_size = 10;

	int width;
	int height;
	int num_levels;
	vector<vector<Circle*>> nodes;
	vector<vector<Arrow*>> arrows;
	vector<vector<Text*>> labels;
};

Modular_tree::Modular_tree(Point tl, int w, int h, int nl) :
	width{ w }, height{ h }, num_levels{ nl }
{
	if (num_levels < 1)
		throw exception("Modular_tree() - invalid constructor argument");

	Shape::add(tl);

	nodes = vector<vector<Circle*>>(num_levels, vector<Circle*>{});
	arrows = vector<vector<Arrow*>>(num_levels, vector<Arrow*>{});
	labels = vector<vector<Text*>>(num_levels, vector<Text*>{});

	const int node_radius = height / num_levels / 2;
	nodes[0].push_back(new Circle{ { int(point(0).x + width / 2),
			point(0).y + node_radius }, node_radius });
}

Modular_tree::~Modular_tree()
{
	for (vector<Circle*> level_nodes : nodes)
		for (Circle* node : level_nodes)
			delete node;
	nodes.clear();

	for (vector<Arrow*> level_arrows : arrows)
		for (Arrow* arrow : level_arrows)
			delete arrow;
	arrows.clear();

	for (vector<Text*> level_labels : labels)
		for (Text* label : level_labels)
			delete label;
	labels.clear();
}

void Modular_tree::add_nodes(int i, int j, int num_nodes, int nodes_width)
{
	const int x_orig = nodes[i][j]->center().x - nodes_width / 2;
	const int node_spacing = nodes_width / (num_nodes + 1);
	const int node_radius = height / num_levels / (i + 2) / 2;
	for (int k = 0; k < num_nodes; ++k) {
		nodes[i + 1].push_back(new Circle{ { x_orig + (k + 1) * node_spacing,
			nodes[i][j]->center().y + height / num_levels }, node_radius });
		arrows[i + 1].push_back(new Arrow{ { nodes[i + 1].back()->center().x,
			nodes[i + 1].back()->center().y - node_radius },
			{ nodes[i][j]->center().x, nodes[i][j]->center().y + nodes[i][j]->radius() }, head_angle,
			head_size });
	}
}

void Modular_tree::put_label(int i, int j, const string& label)
{
	const int node_height = height / num_levels / (i + 1);
	const int node_radius = node_height / 2;
	int font_size = 128 / num_levels / (i + 1);
	if (font_size < 10)
		font_size = 10;
	const int label_width = font_size * label.size() / 2;
	labels[i].push_back(new Text{ { nodes[i][j]->center().x - label_width / 2, nodes[i][j]->center().y },
		label });
	labels[i].back()->set_font_size(font_size);
}

void Modular_tree::draw_lines() const
{
	for (vector<Circle*> level_nodes : nodes)
		for (Circle* node : level_nodes) {
			node->set_color(fl_rgb_color(150, 150, 150));
			node->set_style(Line_style{ Line_style::dash, 3 });
			node->draw();
		}

	for (vector<Arrow*> level_arrows : arrows)
		for (Arrow* arrow : level_arrows)
			arrow->draw();

	for (vector<Text*> level_labels : labels)
		for (Text* label : level_labels)
			label->draw();
}

void Modular_tree::move(int dx, int dy)
{
	for (vector<Circle*> level_nodes : nodes)
		for (Circle* node : level_nodes)
			node->move(dx, dy);

	for (vector<Arrow*> level_arrows : arrows)
		for (Arrow* arrow : level_arrows)
			arrow->move(dx, dy);

	for (vector<Text*> level_labels : labels)
		for (Text* label : level_labels)
			label->move(dx, dy);
}

void Modular_tree::set_color(Color col)
{
	Shape::set_color(col);

	for (vector<Circle*> level_nodes : nodes)
		for (Circle* node : level_nodes)
			node->set_color(col);

	for (vector<Arrow*> level_arrows : arrows)
		for (Arrow* arrow : level_arrows)
			arrow->set_color(col);

	for (vector<Text*> level_labels : labels)
		for (Text* label : level_labels)
			label->set_color(col);
}

void Modular_tree::set_fill_color(Color col)
{
	Shape::set_fill_color(col);

	for (vector<Circle*> level_nodes : nodes)
		for (Circle* node : level_nodes)
			node->set_fill_color(col);
}

void Modular_tree::set_style(Line_style ls)
{
	Shape::set_style(ls);

	for (vector<Circle*> level_nodes : nodes)
		for (Circle* node : level_nodes)
			node->set_style(ls);

	for (vector<Arrow*> level_arrows : arrows)
		for (Arrow* arrow : level_arrows)
			arrow->set_style(ls);

	for (vector<Text*> level_labels : labels)
		for (Text* label : level_labels)
			label->set_style(ls);
}
}

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 32, y_max() / 32 };
	const int win_width = x_max() * 15 / 16;
	const int win_height = y_max() * 15 / 16;
	const string win_name{ "My window" };
	Simple_window s_win{ win_tl, win_width, win_height, win_name };

	const int padding = 10;
	Modular_tree m_tree{ { padding, padding }, s_win.x_max() - 2 * padding, s_win.y_max() - 2 * padding, 4 };
	m_tree.add_nodes(0, 0, 10, s_win.x_max());
	m_tree.add_nodes(1, 1, 5, s_win.x_max() / 3);
	m_tree.add_nodes(1, 5, 8, s_win.x_max() / 2);
	m_tree.add_nodes(1, 8, 1, s_win.x_max() / 4);
	m_tree.add_nodes(1, 9, 1, s_win.x_max() / 4);
	m_tree.add_nodes(2, 2, 2, s_win.x_max() / 4);
	m_tree.put_label(0, 0, "exception");
	m_tree.put_label(1, 0, "bad_optional_access");
	m_tree.put_label(1, 1, "logic_error");
	m_tree.put_label(1, 2, "bad_typeid");
	m_tree.put_label(1, 3, "bad_weak_ptr");
	m_tree.put_label(1, 4, "bad_function_call");
	m_tree.put_label(1, 5, "runtime_error");
	m_tree.put_label(1, 6, "bad_exception");
	m_tree.put_label(1, 7, "bad_variant_access");
	m_tree.put_label(1, 8, "bad_cast");
	m_tree.put_label(1, 9, "bad_alloc");
	m_tree.put_label(2, 0, "invalid_argument");
	m_tree.put_label(2, 1, "domain_error");
	m_tree.put_label(2, 2, "length_error");
	m_tree.put_label(2, 3, "out_of_range");
	m_tree.put_label(2, 4, "future_error");
	m_tree.put_label(2, 5, "range_error");
	m_tree.put_label(2, 6, "overflow_error");
	m_tree.put_label(2, 7, "underflow_error");
	m_tree.put_label(2, 8, "regex_error");
	m_tree.put_label(2, 9, "nonexistent_local_time");
	m_tree.put_label(2, 10, "tx_exception");
	m_tree.put_label(2, 11, "ambiguous_local_time");
	m_tree.put_label(2, 12, "system_error");
	m_tree.put_label(2, 13, "bad_any_cast");
	m_tree.put_label(2, 14, "bad_array_new_length");
	m_tree.put_label(3, 0, "ios_base::failure");
	m_tree.put_label(3, 1, "filesystem::filesystem_error");
	m_tree.set_color(Color::dark_blue);

	s_win.attach(m_tree);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}