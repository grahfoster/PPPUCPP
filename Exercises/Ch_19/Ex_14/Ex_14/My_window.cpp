#include "My_window.h"
#include <FL/Fl_Multiline_Output.H>

namespace Graph_lib {

void My_out_box::put(const string& s) { reference_to<Fl_Multiline_Output>(pw).value(s.c_str()); }

void My_out_box::attach(Window& win)
{
	pw = new Fl_Multiline_Output(loc.x, loc.y, width, height, label.c_str());
	own = &win;
}

My_window::My_window(Point tl, int width, int height, const string& label) :
	Window{ tl, width, height, label },
	out_box{ { 0, 0 }, width / 2, height * 7 / 8, "" },
	in_box{ { 0, height * 7 / 8 }, width / 2, height / 8, "" },
	enter_button{ { width * 9 / 20, height * 7 / 8 }, width / 20, height / 20, "Enter",
		[](Address, Address addr) { reference_to<My_window>(addr).act(); } },
	cave_map{ { width * 3 / 4, height / 2 }, width / 8 },
	cave_label{ { width * 3 / 4, height / 2 }, "Cave 0" }
{
	attach(out_box);
	attach(in_box);
	attach(enter_button);
	attach(cave_map);
	cave_map.set_color(Color::black);
	attach(cave_label);
	cave_label.set_color(Color::black);
	cave_label.move(-int(cave_label.font_size() / 2 * cave_label.label().size() / 2), 0);

	for (int i = 0; i < num_adjs; ++i) {
		adj_labels.push_back(
			new Text{ { cave_map.center().x + int(cave_map.radius() * 5 / 4 *
					cos((i * 360 / num_adjs + 30) * pi / 180)),
				cave_map.center().y - int(cave_map.radius() * 5 / 4 *
					sin((i * 360 / num_adjs + 30) * pi / 180)) },
			"Cave 0" });
		attach(*adj_labels.back());
		adj_labels.back()->set_color(Color::black);
		adj_labels.back()->move(-int(adj_labels.back()->font_size() / 2 * adj_labels.back()->label().size() / 2), 0);
	}
}

My_window::~My_window()
{
	for (Text* adj_label : adj_labels)
		delete adj_label;
}

void My_window::print(const string& new_text)
{
	out_box_text += new_text;
	out_box.put(out_box_text);
	redraw();
}

void My_window::set_cave_labels(const vector<int>& cave_nums)
{
	const string label_start{ "Cave " };

	cave_label.set_label(label_start + to_string(cave_nums.front()));
	for (int i = 1; i < cave_nums.size(); ++i)
		adj_labels[i - 1]->set_label(label_start + to_string(cave_nums[i]));
}
}