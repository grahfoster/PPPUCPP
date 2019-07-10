#include "../GUI.h"
#include "../Window.h"

void do_action();

namespace Graph_lib {

class My_out_box : public Out_box {
public:
	using Out_box::Out_box;

	void put(const string&);
	void attach(Window&);
};

class My_window : Window {
public:
	My_window(Point, int, int, const string&);
	~My_window();

	void print(const string&);
	string read() {	return in_box.get_string(); }
	void clear() { out_box_text.clear(); }
	void hide_enter_button() { enter_button.hide(); }
	void set_cave_labels(const vector<int>&);
private:
	const int num_adjs = 3;
	const double pi = atan(1) * 4;

	My_out_box out_box;
	string out_box_text;
	In_box in_box;
	Button enter_button;
	Circle cave_map;
	Text cave_label;
	vector<Text*> adj_labels;

	void act() { do_action(); }
};
}