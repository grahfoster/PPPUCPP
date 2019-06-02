#include "../Graph.h"
#include "../Simple_window.h"

namespace Graph_lib {

class Group {
public:
	Group() {}

	int size() const { return shapes.size(); }

	Shape& get(int i) { return shapes[i]; }
	void put(Shape& shape) { shapes.push_back(shape); }
	void put(Shape* shape) { shapes.push_back(shape); }
	void move(int, int);
	void set_color(Color);
	void set_fill_color(Color);
	void set_style(Line_style);
private:
	Vector_ref<Shape> shapes;
};

void Group::move(int dx, int dy)
{
	for (int i = 0; i < shapes.size(); ++i)
		shapes[i].move(dx, dy);
}

void Group::set_color(Color col)
{
	for (int i = 0; i < shapes.size(); ++i)
		shapes[i].set_color(col);
}

void Group::set_fill_color(Color col)
{
	for (int i = 0; i < shapes.size(); ++i)
		shapes[i].set_fill_color(col);
}

void Group::set_style(Line_style ls)
{
	for (int i = 0; i < shapes.size(); ++i)
		shapes[i].set_style(ls);
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

	const int num_rows = 8;
	const int num_columns = num_rows;
	const int square_width = s_win.y_max() / num_rows;
	Group board;
	for (int i = 0; i < num_rows; ++i)
		for (int j = 0; j < num_columns; ++j) {
			board.put(new Graph_lib::Rectangle{ { j * square_width, i * square_width }, square_width,
				square_width });
			board.get(board.size() - 1).set_fill_color((j + i) % 2 == 0 ? Color::white : Color::black);
		}
	board.set_color(Color::black);

	const int piece_radius = square_width / 2;
	Circle piece{ { piece_radius, piece_radius }, piece_radius };
	piece.set_color(Color::black);
	piece.set_fill_color(Color::white);
	piece.move(board.get(10).point(0).x, board.get(10).point(0).y);

	for (int i = 0; i < board.size(); ++i)
		s_win.attach(board.get(i));
	s_win.attach(piece);

	s_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}