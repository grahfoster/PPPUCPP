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
	cave_map{ { width * 3 / 4, height / 3 }, width / 8 }
{
	attach(out_box);
	attach(in_box);
	attach(enter_button);
	attach(cave_map);
	cave_map.set_color(Color::black);

	for (int i = 0; i < Cave::num_adjs + 1; ++i) {
		if (i == 0)
			cave_labels.push_back(new Text{ cave_map.center(), "Cave 0" });
		else {
			cave_labels.push_back(
				new Text{ { cave_map.center().x + int(cave_map.radius() * 7 / 4 *
						cos((i * 360 / Cave::num_adjs + 90 / Cave::num_adjs) * pi / 180)),
					cave_map.center().y - int(cave_map.radius() * 5 / 4 *
						sin((i * 360 / Cave::num_adjs + 90 / Cave::num_adjs) * pi / 180)) },
			"Cave 0" });
		}
		attach(*cave_labels.back());
		cave_labels.back()->set_color(Color::black);
		cave_labels.back()->move(
			-int(cave_labels.back()->font_size() / 2 * cave_labels.back()->label().size() / 2), 0
		);
	}

	cave_menus.push_back(new Menu {
			{ cave_labels[1]->point(0).x, cave_labels[1]->point(0).y + cave_labels[1]->font_size() * 2 },
			width / 15, height / 20, Menu::vertical, "Cave State:" 
		});
	cave_menus.back()->attach(new Button{ { 0, 0 }, 0, 0, "Unknown",
		[](Address, Address addr) { 
			reference_to<My_window>(addr).set_map_cave_state(1, Cave::Cave_state::unknown);
		} });
	cave_menus.back()->attach(new Button{ { 0, 0 }, 0, 0, "Clear",
		[](Address, Address addr) {
			reference_to<My_window>(addr).set_map_cave_state(1, Cave::Cave_state::clear);
		} });
	cave_menus.back()->attach(new Button{ { 0, 0 }, 0, 0, "Possible Pit",
		[](Address, Address addr) {
			reference_to<My_window>(addr).set_map_cave_state(1, Cave::Cave_state::pit_warning);
		} });
	cave_menus.back()->attach(new Button{ { 0, 0 }, 0, 0, "Definite Pit",
		[](Address, Address addr) {
			reference_to<My_window>(addr).set_map_cave_state(1, Cave::Cave_state::pit_danger);
		} });
	cave_menus.back()->attach(new Button{ { 0, 0 }, 0, 0, "Possible Bat",
		[](Address, Address addr) {
			reference_to<My_window>(addr).set_map_cave_state(1, Cave::Cave_state::bat_warning);
		} });
	cave_menus.back()->attach(new Button{ { 0, 0 }, 0, 0, "Definite Bat",
		[](Address, Address addr) {
			reference_to<My_window>(addr).set_map_cave_state(1, Cave::Cave_state::bat_danger);
		} });
	attach(*cave_menus.back());

	cave_menus.push_back(new Menu{
			{ cave_labels[2]->point(0).x, cave_labels[2]->point(0).y + cave_labels[2]->font_size() * 2 },
			width / 15, height / 20, Menu::vertical, "Cave State:"
		});
	cave_menus.back()->attach(new Button{ { 0, 0 }, 0, 0, "Unknown",
		[](Address, Address addr) {
			reference_to<My_window>(addr).set_map_cave_state(2, Cave::Cave_state::unknown);
		} });
	cave_menus.back()->attach(new Button{ { 0, 0 }, 0, 0, "Clear",
		[](Address, Address addr) {
			reference_to<My_window>(addr).set_map_cave_state(2, Cave::Cave_state::clear);
		} });
	cave_menus.back()->attach(new Button{ { 0, 0 }, 0, 0, "Possible Pit",
		[](Address, Address addr) {
			reference_to<My_window>(addr).set_map_cave_state(2, Cave::Cave_state::pit_warning);
		} });
	cave_menus.back()->attach(new Button{ { 0, 0 }, 0, 0, "Definite Pit",
		[](Address, Address addr) {
			reference_to<My_window>(addr).set_map_cave_state(2, Cave::Cave_state::pit_danger);
		} });
	cave_menus.back()->attach(new Button{ { 0, 0 }, 0, 0, "Possible Bat",
		[](Address, Address addr) {
			reference_to<My_window>(addr).set_map_cave_state(2, Cave::Cave_state::bat_warning);
		} });
	cave_menus.back()->attach(new Button{ { 0, 0 }, 0, 0, "Definite Bat",
		[](Address, Address addr) {
			reference_to<My_window>(addr).set_map_cave_state(2, Cave::Cave_state::bat_danger);
		} });
	attach(*cave_menus.back());

	cave_menus.push_back(new Menu{
			{ cave_labels[3]->point(0).x, cave_labels[3]->point(0).y + cave_labels[3]->font_size() * 2 },
			width / 15, height / 20, Menu::vertical, "Cave State:"
		});
	cave_menus.back()->attach(new Button{ { 0, 0 }, 0, 0, "Unknown",
		[](Address, Address addr) {
			reference_to<My_window>(addr).set_map_cave_state(3, Cave::Cave_state::unknown);
		} });
	cave_menus.back()->attach(new Button{ { 0, 0 }, 0, 0, "Clear",
		[](Address, Address addr) {
			reference_to<My_window>(addr).set_map_cave_state(3, Cave::Cave_state::clear);
		} });
	cave_menus.back()->attach(new Button{ { 0, 0 }, 0, 0, "Possible Pit",
		[](Address, Address addr) {
			reference_to<My_window>(addr).set_map_cave_state(3, Cave::Cave_state::pit_warning);
		} });
	cave_menus.back()->attach(new Button{ { 0, 0 }, 0, 0, "Definite Pit",
		[](Address, Address addr) {
			reference_to<My_window>(addr).set_map_cave_state(3, Cave::Cave_state::pit_danger);
		} });
	cave_menus.back()->attach(new Button{ { 0, 0 }, 0, 0, "Possible Bat",
		[](Address, Address addr) {
			reference_to<My_window>(addr).set_map_cave_state(3, Cave::Cave_state::bat_warning);
		} });
	cave_menus.back()->attach(new Button{ { 0, 0 }, 0, 0, "Definite Bat",
		[](Address, Address addr) {
			reference_to<My_window>(addr).set_map_cave_state(3, Cave::Cave_state::bat_danger);
		} });
	attach(*cave_menus.back());
}

My_window::~My_window()
{
	for (Text* adj_label : cave_labels)
		delete adj_label;
}

void My_window::print(const string& new_text)
{
	out_box_text += new_text;
	out_box.put(out_box_text);
	redraw();
}

void My_window::set_cave_labels(const vector<Cave*>& mc)
{
	const string label_start{ "Cave " };

	map_caves = mc;
	map_caves.front()->set_cave_state(Cave::Cave_state::clear);

	for (int i = 0; i < map_caves.size(); ++i) {
		cave_labels[i]->set_label(label_start + to_string(map_caves[i]->get_num()));
		switch (map_caves[i]->get_cave_state()) {
		case Cave::Cave_state::clear:
			cave_labels[i]->set_color(Color::dark_green);
			break;
		case Cave::Cave_state::pit_warning:
			cave_labels[i]->set_color(Color::yellow);
			break;
		case Cave::Cave_state::pit_danger:
			cave_labels[i]->set_color(Color::red);
			break;
		case Cave::Cave_state::bat_warning:
			cave_labels[i]->set_color(Color::blue);
			break;
		case Cave::Cave_state::bat_danger:
			cave_labels[i]->set_color(Color::magenta);
			break;
		default:
			cave_labels[i]->set_color(Color::black);
		}
	}
}

void My_window::set_map_cave_state(int i, Cave::Cave_state cs)
{
	map_caves[i]->set_cave_state(cs);
	set_cave_labels(map_caves);
	redraw();
}
}