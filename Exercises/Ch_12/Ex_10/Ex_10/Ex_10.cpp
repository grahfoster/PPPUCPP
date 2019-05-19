#include "../Graph.h"
#include "../Simple_window.h"

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 16, y_max() / 16 };
	const int win_width = x_max() * 3 / 4;
	const int win_height = y_max() * 7 / 8;
	const string win_name{ "My window" };
	Simple_window s_win{ win_tl, win_width, win_height, win_name };

	const int box_width_s = s_win.x_max() / 8;
	const int box_width_m = s_win.x_max() / 6;
	const int box_width_l = box_width_s * 5 / 3;
	const int box_height_s = s_win.y_max() / 24;
	const int box_height_m = box_height_s * 2;
	const int box_height_l = box_height_s * 5 / 2;
	const int box_padding = 5;
	const int label_size = 14;
	const int arrowhead_size = 6;

	Graph_lib::Rectangle fltk_h_box1{ Point{ s_win.x_max() * 15 / 32,
		s_win.y_max() / 32 }, Point{ s_win.x_max() * 15 / 32 + box_width_m,
		s_win.y_max() / 32 + box_height_m } };
	fltk_h_box1.set_color(Color::black);
	fltk_h_box1.set_fill_color(Color::yellow);

	Graph_lib::Rectangle fltk_h_box2{
		Point{ fltk_h_box1.point(0).x + box_padding,
		fltk_h_box1.point(0).y + box_padding },
		Point{ fltk_h_box1.point(0).x + box_padding + box_width_m,
		fltk_h_box1.point(0).y + box_padding + box_height_m } };
	fltk_h_box2.set_color(Color::black);
	fltk_h_box2.set_fill_color(Color::yellow);

	Graph_lib::Rectangle fltk_h_box3{
		Point{ fltk_h_box2.point(0).x + box_padding,
		fltk_h_box2.point(0).y + box_padding },
		Point{ fltk_h_box2.point(0).x + box_padding + box_width_m,
		fltk_h_box2.point(0).y + box_padding + box_height_m } };
	fltk_h_box3.set_color(Color::black);
	fltk_h_box3.set_fill_color(Color::yellow);

	Text fltk_h_label{ Point { fltk_h_box3.point(0).x + box_padding,
		fltk_h_box3.point(0).y + box_padding * 4}, "FLTK headers" };
	fltk_h_label.set_color(Color::black);
	fltk_h_label.set_font_size(label_size);

	Graph_lib::Rectangle fltk_c_box1{ Point{ s_win.x_max() * 25 / 32,
		s_win.y_max() / 8 }, Point{ s_win.x_max() * 25 / 32 + box_width_m,
		s_win.y_max() / 8 + box_height_m } };
	fltk_c_box1.set_color(Color::black);
	fltk_c_box1.set_fill_color(Color::yellow);

	Graph_lib::Rectangle fltk_c_box2{
		Point{ fltk_c_box1.point(0).x + box_padding,
		fltk_c_box1.point(0).y + box_padding },
		Point{ fltk_c_box1.point(0).x + box_padding + box_width_m,
		fltk_c_box1.point(0).y + box_padding + box_height_m } };
	fltk_c_box2.set_color(Color::black);
	fltk_c_box2.set_fill_color(Color::yellow);

	Graph_lib::Rectangle fltk_c_box3{
		Point{ fltk_c_box2.point(0).x + box_padding,
		fltk_c_box2.point(0).y + box_padding },
		Point{ fltk_c_box2.point(0).x + box_padding + box_width_m,
		fltk_c_box2.point(0).y + box_padding + box_height_m } };
	fltk_c_box3.set_color(Color::black);
	fltk_c_box3.set_fill_color(Color::yellow);

	Text fltk_c_label{ Point { fltk_c_box3.point(0).x + box_padding,
		fltk_c_box3.point(0).y + box_padding * 4}, "FLTK code" };
	fltk_c_label.set_color(Color::black);
	fltk_c_label.set_font_size(label_size);

	Graph_lib::Rectangle point_h_box{ Point{ s_win.x_max() / 8,
		s_win.y_max() / 8 }, Point { s_win.x_max() / 8 + box_width_m,
		s_win.y_max() / 8 + box_height_s } };
	point_h_box.set_color(Color::black);
	point_h_box.set_fill_color(Color::yellow);

	Text point_h_label1{ Point{ point_h_box.point(0).x,
		point_h_box.point(0).y - box_padding }, "Point.h" };
	point_h_label1.set_color(Color::dark_blue);
	point_h_label1.set_font_size(label_size);
	point_h_label1.set_font(Font::helvetica_bold);

	Text point_h_label2{ Point{ point_h_box.point(0).x + box_padding,
		point_h_box.point(0).y + box_padding * 4 }, "struct Point { ... };" };
	point_h_label2.set_color(Color::black);
	point_h_label2.set_font_size(label_size);
	point_h_label2.set_font(Font::helvetica_bold);

	Graph_lib::Rectangle win_h_box{ Point{ s_win.x_max() * 7 / 16,
		s_win.y_max() * 5 / 16 }, Point{ s_win.x_max() * 7 / 16 + box_width_l,
		s_win.y_max() * 5 / 16 + box_height_l } };
	win_h_box.set_color(Color::black);
	win_h_box.set_fill_color(Color::yellow);

	Text win_h_label1{ Point{ win_h_box.point(0).x,
		win_h_box.point(0).y - box_padding }, "Window.h" };
	win_h_label1.set_color(Color::dark_blue);
	win_h_label1.set_font_size(label_size);
	win_h_label1.set_font(Font::helvetica_bold);

	Text win_h_label2{ Point{ win_h_box.point(0).x + box_padding * 2,
		win_h_box.point(0).y + box_padding * 4 }, "// window interface:" };
	win_h_label2.set_color(Color::black);
	win_h_label2.set_font_size(label_size);

	Text win_h_label3{ Point{ win_h_box.point(0).x + box_padding * 2,
		win_h_label2.point(0).y + box_padding * 4 },
		"class Window { ... };" };
	win_h_label3.set_color(Color::black);
	win_h_label3.set_font_size(label_size);
	win_h_label3.set_font(Font::helvetica_bold);

	Text win_h_label4{ Point{ win_h_box.point(0).x + box_padding * 2,
		win_h_label3.point(0).y + box_padding * 4 }, "..." };
	win_h_label4.set_color(Color::black);
	win_h_label4.set_font_size(label_size);

	Graph_lib::Rectangle graph_h_box{ Point{ point_h_box.point(0).x,
		s_win.y_max() * 7 / 16 }, Point{ point_h_box.point(0).x + box_width_l,
		s_win.y_max() * 7 / 16 + box_height_l } };
	graph_h_box.set_color(Color::black);
	graph_h_box.set_fill_color(Color::yellow);

	Text graph_h_label1{ Point{ graph_h_box.point(0).x,
		graph_h_box.point(0).y - box_padding }, "Graph.h" };
	graph_h_label1.set_color(Color::dark_blue);
	graph_h_label1.set_font_size(label_size);
	graph_h_label1.set_font(Font::helvetica_bold);

	Text graph_h_label2{ Point{ graph_h_box.point(0).x + box_padding * 2,
		graph_h_box.point(0).y + box_padding * 4 }, "// graphing interface:" };
	graph_h_label2.set_color(Color::black);
	graph_h_label2.set_font_size(label_size);

	Text graph_h_label3{ Point{ graph_h_box.point(0).x + box_padding * 2,
		graph_h_label2.point(0).y + box_padding * 4 },
		"struct Shape { ... };" };
	graph_h_label3.set_color(Color::black);
	graph_h_label3.set_font_size(label_size);
	graph_h_label3.set_font(Font::helvetica_bold);

	Text graph_h_label4{ Point{ graph_h_box.point(0).x + box_padding * 2,
		graph_h_label3.point(0).y + box_padding * 4 }, "..." };
	graph_h_label4.set_color(Color::black);
	graph_h_label4.set_font_size(label_size);

	Graph_lib::Rectangle gui_h_box{ Point{ s_win.x_max() * 5 / 8,
		s_win.y_max() / 2 }, Point{ s_win.x_max() * 5 / 8 + box_width_l,
		s_win.y_max() / 2 + box_height_l } };
	gui_h_box.set_color(Color::black);
	gui_h_box.set_fill_color(Color::yellow);

	Text gui_h_label1{ Point{ gui_h_box.point(0).x,
		gui_h_box.point(0).y - box_padding }, "GUI.h" };
	gui_h_label1.set_color(Color::dark_blue);
	gui_h_label1.set_font_size(label_size);
	gui_h_label1.set_font(Font::helvetica_bold);

	Text gui_h_label2{ Point{ gui_h_box.point(0).x + box_padding * 2,
		gui_h_box.point(0).y + box_padding * 4 }, "// GUI interface:" };
	gui_h_label2.set_color(Color::black);
	gui_h_label2.set_font_size(label_size);

	Text gui_h_label3{ Point{ gui_h_box.point(0).x + box_padding * 2,
		gui_h_label2.point(0).y + box_padding * 4 }, "struct In_box { ... };" };
	gui_h_label3.set_color(Color::black);
	gui_h_label3.set_font_size(label_size);
	gui_h_label3.set_font(Font::helvetica_bold);

	Text gui_h_label4{ Point{ gui_h_box.point(0).x + box_padding * 2,
		gui_h_label3.point(0).y + box_padding * 4 }, "..." };
	gui_h_label4.set_color(Color::black);
	gui_h_label4.set_font_size(label_size);

	Graph_lib::Rectangle window_c_box{ Point{ s_win.x_max() * 5 / 16,
		s_win.y_max() * 19 / 32 }, Point{ s_win.x_max() * 5 / 16 + box_width_m,
		s_win.y_max() * 19 / 32 + box_height_s } };
	window_c_box.set_color(Color::black);
	window_c_box.set_fill_color(Color::yellow);

	Text window_c_label1{ Point{ window_c_box.point(0).x,
		window_c_box.point(0).y - box_padding }, "Window.cpp" };
	window_c_label1.set_color(Color::dark_blue);
	window_c_label1.set_font_size(label_size);
	window_c_label1.set_font(Font::helvetica_bold);

	Text window_c_label2{ Point{ window_c_box.point(0).x + box_padding * 2,
		window_c_box.point(0).y + box_padding * 4 }, "Window code" };
	window_c_label2.set_color(Color::black);
	window_c_label2.set_font_size(label_size);
	window_c_label2.set_font(Font::helvetica_bold);

	Graph_lib::Rectangle graph_c_box{ Point{ s_win.x_max() / 16,
		s_win.y_max() * 11 / 16 }, Point{ s_win.x_max() / 16 + box_width_s,
		s_win.y_max() * 11 / 16 + box_height_s } };
	graph_c_box.set_color(Color::black);
	graph_c_box.set_fill_color(Color::yellow);

	Text graph_c_label1{ Point{ graph_c_box.point(0).x,
		graph_c_box.point(0).y - box_padding }, "Graph.cpp" };
	graph_c_label1.set_color(Color::dark_blue);
	graph_c_label1.set_font_size(label_size);
	graph_c_label1.set_font(Font::helvetica_bold);

	Text graph_c_label2{ Point{ graph_c_box.point(0).x + box_padding * 2,
		graph_c_box.point(0).y + box_padding * 4 }, "Graph code" };
	graph_c_label2.set_color(Color::black);
	graph_c_label2.set_font_size(label_size);
	graph_c_label2.set_font(Font::helvetica_bold);

	Graph_lib::Rectangle gui_c_box{ Point{ s_win.x_max() * 3 / 4,
		graph_c_box.point(0).y }, Point{ s_win.x_max() * 3 / 4 + box_width_s,
		graph_c_box.point(0).y + box_height_s } };
	gui_c_box.set_color(Color::black);
	gui_c_box.set_fill_color(Color::yellow);

	Text gui_c_label1{ Point{ gui_c_box.point(0).x,
		gui_c_box.point(0).y - box_padding }, "GUI.cpp" };
	gui_c_label1.set_color(Color::dark_blue);
	gui_c_label1.set_font_size(label_size);
	gui_c_label1.set_font(Font::helvetica_bold);

	Text gui_c_label2{ Point{ gui_c_box.point(0).x + box_padding * 2,
		gui_c_box.point(0).y + box_padding * 4 }, "GUI code" };
	gui_c_label2.set_color(Color::black);
	gui_c_label2.set_font_size(label_size);
	gui_c_label2.set_font(Font::helvetica_bold);

	Graph_lib::Rectangle s_win_h_box{ Point{ s_win.x_max() * 2 / 5,
		s_win.y_max() * 23 / 32 }, Point{ s_win.x_max() * 2 / 5 + box_width_l,
		s_win.y_max() * 23 / 32 + box_height_l } };
	s_win_h_box.set_color(Color::black);
	s_win_h_box.set_fill_color(Color::yellow);

	Text s_win_h_label1{ Point{ s_win_h_box.point(0).x,
		s_win_h_box.point(0).y - box_padding }, "Simple_window.h" };
	s_win_h_label1.set_color(Color::dark_blue);
	s_win_h_label1.set_font_size(label_size);
	s_win_h_label1.set_font(Font::helvetica_bold);

	Text s_win_h_label2{ Point{ s_win_h_box.point(0).x + box_padding * 2,
		s_win_h_box.point(0).y + box_padding * 4 }, "// window interface:" };
	s_win_h_label2.set_color(Color::black);
	s_win_h_label2.set_font_size(label_size);

	Text s_win_h_label3{ Point{ s_win_h_box.point(0).x + box_padding * 2,
		s_win_h_label2.point(0).y + box_padding * 4 },
		"class Simple_window { ... };" };
	s_win_h_label3.set_color(Color::black);
	s_win_h_label3.set_font_size(label_size);
	s_win_h_label3.set_font(Font::helvetica_bold);

	Text s_win_h_label4{ Point{ s_win_h_box.point(0).x + box_padding * 2,
		s_win_h_label3.point(0).y + box_padding * 4 }, "..." };
	s_win_h_label4.set_color(Color::black);
	s_win_h_label4.set_font_size(label_size);

	Graph_lib::Rectangle ch_12_c_box{ Point{ s_win.x_max() * 3 / 16,
		s_win.y_max() * 7 / 8 }, Point{ s_win.x_max() * 3 / 16 + box_width_l,
		s_win.y_max() * 7 / 8 + box_height_l } };
	ch_12_c_box.set_color(Color::black);
	ch_12_c_box.set_fill_color(Color::yellow);

	Text ch_12_c_label1{ Point{ ch_12_c_box.point(0).x,
		ch_12_c_box.point(0).y - box_padding }, "Chapter12.cpp" };
	ch_12_c_label1.set_color(Color::dark_blue);
	ch_12_c_label1.set_font_size(label_size);
	ch_12_c_label1.set_font(Font::helvetica_bold);

	Text ch_12_c_label2{ Point{ ch_12_c_box.point(0).x + box_padding * 2,
		ch_12_c_box.point(0).y + box_padding * 4 }, "#include \"Graph.h\"" };
	ch_12_c_label2.set_color(Color::black);
	ch_12_c_label2.set_font_size(label_size);
	s_win_h_label3.set_font(Font::helvetica_bold);

	Text ch_12_c_label3{ Point{ ch_12_c_box.point(0).x + box_padding * 2,
		ch_12_c_label2.point(0).y + box_padding * 4 },
		"#include \"Simple_window.h\"" };
	ch_12_c_label3.set_color(Color::black);
	ch_12_c_label3.set_font_size(label_size);
	ch_12_c_label3.set_font(Font::helvetica_bold);

	Text ch_12_c_label4{ Point{ ch_12_c_box.point(0).x + box_padding * 2,
		ch_12_c_label3.point(0).y + box_padding * 4 }, "int main() { ... }" };
	ch_12_c_label4.set_color(Color::black);
	ch_12_c_label4.set_font_size(label_size);
	s_win_h_label3.set_font(Font::helvetica_bold);

	Line arrow1{ Point{ fltk_c_box1.point(0).x,
		fltk_c_box1.point(0).y + box_height_m / 2 },
		Point{ fltk_h_box3.point(0).x + box_width_m,
		fltk_h_box3.point(0).y + box_height_m / 2 } };
	arrow1.set_color(Color::black);

	Graph_lib::Polygon arrowhead1;
	arrowhead1.add(Point{ arrow1.point(1) });
	arrowhead1.add(Point{ arrow1.point(1).x + arrowhead_size,
		arrow1.point(1).y + arrowhead_size / 2 });
	arrowhead1.add(Point{ arrow1.point(1).x + arrowhead_size,
		arrow1.point(1).y - arrowhead_size / 2 });
	arrowhead1.set_color(Color::black);
	arrowhead1.set_fill_color(Color::black);

	Line arrow2{ Point{ graph_h_box.point(0).x + box_width_l / 2,
		graph_h_box.point(0).y }, Point{ fltk_h_box3.point(0).x,
		fltk_h_box3.point(0).y + box_height_m } };
	arrow2.set_color(Color::black);

	Graph_lib::Polygon arrowhead2;
	arrowhead2.add(Point{ arrow2.point(1) });
	arrowhead2.add(Point{ arrow2.point(1).x + arrowhead_size,
		arrow2.point(1).y + arrowhead_size / 2 });
	arrowhead2.add(Point{ arrow2.point(1).x + arrowhead_size,
		arrow2.point(1).y - arrowhead_size / 2 });
	arrowhead2.set_color(Color::black);
	arrowhead2.set_fill_color(Color::black);

	Line arrow3{ Point{ win_h_box.point(0).x + box_width_l / 2,
		win_h_box.point(0).y },
		Point{ fltk_h_box3.point(0).x + box_width_m / 2,
		fltk_h_box3.point(0).y + box_height_m } };
	arrow3.set_color(Color::black);

	Graph_lib::Polygon arrowhead3;
	arrowhead3.add(Point{ arrow3.point(1) });
	arrowhead3.add(Point{ arrow3.point(1).x + arrowhead_size / 2,
		arrow3.point(1).y + arrowhead_size });
	arrowhead3.add(Point{ arrow3.point(1).x - arrowhead_size / 2,
		arrow3.point(1).y + arrowhead_size });
	arrowhead3.set_color(Color::black);
	arrowhead3.set_fill_color(Color::black);

	Line arrow4{ Point{ gui_h_box.point(0).x + box_width_l * 2 / 3,
		gui_h_box.point(0).y },
		Point{ fltk_h_box3.point(0).x + box_width_m * 3 / 4,
		fltk_h_box3.point(0).y + box_height_m } };
	arrow4.set_color(Color::black);

	Graph_lib::Polygon arrowhead4;
	arrowhead4.add(Point{ arrow4.point(1) });
	arrowhead4.add(Point{ arrow4.point(1).x + arrowhead_size / 2,
		arrow4.point(1).y + arrowhead_size });
	arrowhead4.add(Point{ arrow4.point(1).x - arrowhead_size / 2,
		arrow4.point(1).y + arrowhead_size });
	arrowhead4.set_color(Color::black);
	arrowhead4.set_fill_color(Color::black);

	Line arrow5{ Point{ graph_h_box.point(0).x + box_width_l / 2,
		graph_h_box.point(0).y },
		Point{ point_h_box.point(0).x + box_width_m / 2,
		point_h_box.point(0).y + box_height_s } };
	arrow5.set_color(Color::black);

	Graph_lib::Polygon arrowhead5;
	arrowhead5.add(Point{ arrow5.point(1) });
	arrowhead5.add(Point{ arrow5.point(1).x - arrowhead_size / 2,
		arrow5.point(1).y + arrowhead_size });
	arrowhead5.add(Point{ arrow5.point(1).x + arrowhead_size / 2,
		arrow5.point(1).y + arrowhead_size });
	arrowhead5.set_color(Color::black);
	arrowhead5.set_fill_color(Color::black);

	Line arrow6{ win_h_box.point(0),
		Point{ point_h_box.point(0).x + box_width_m,
		point_h_box.point(0).y + box_height_s } };
	arrow6.set_color(Color::black);

	Graph_lib::Polygon arrowhead6;
	arrowhead6.add(Point{ arrow6.point(1) });
	arrowhead6.add(Point{ arrow6.point(1).x + arrowhead_size,
		arrow6.point(1).y - arrowhead_size / 2 });
	arrowhead6.add(Point{ arrow6.point(1).x + arrowhead_size,
		arrow6.point(1).y + arrowhead_size / 2 });
	arrowhead6.set_color(Color::black);
	arrowhead6.set_fill_color(Color::black);

	Line arrow7{ Point{ window_c_box.point(0).x + box_width_m * 3 / 4,
		window_c_box.point(0).y },
		Point{ win_h_box.point(0).x + box_width_l * 1 / 4,
		win_h_box.point(0).y + box_height_l } };
	arrow7.set_color(Color::black);

	Graph_lib::Polygon arrowhead7;
	arrowhead7.add(Point{ arrow7.point(1) });
	arrowhead7.add(Point{ arrow7.point(1).x - arrowhead_size / 2,
		arrow7.point(1).y + arrowhead_size });
	arrowhead7.add(Point{ arrow7.point(1).x + arrowhead_size / 2,
		arrow7.point(1).y + arrowhead_size });
	arrowhead7.set_color(Color::black);
	arrowhead7.set_fill_color(Color::black);

	Line arrow8{ Point{ s_win_h_box.point(0).x + box_width_l * 2 / 3,
		s_win_h_box.point(0).y },
		Point{ win_h_box.point(0).x + box_width_l / 2,
		win_h_box.point(0).y + box_height_l } };
	arrow8.set_color(Color::black);

	Graph_lib::Polygon arrowhead8;
	arrowhead8.add(Point{ arrow8.point(1) });
	arrowhead8.add(Point{ arrow8.point(1).x - arrowhead_size / 2,
		arrow8.point(1).y + arrowhead_size });
	arrowhead8.add(Point{ arrow8.point(1).x + arrowhead_size / 2,
		arrow8.point(1).y + arrowhead_size });
	arrowhead8.set_color(Color::black);
	arrowhead8.set_fill_color(Color::black);

	Line arrow9{ Point{ gui_h_box.point(0).x + box_width_l * 2 / 3,
		gui_h_box.point(0).y }, Point{ win_h_box.point(0).x + box_width_l,
		win_h_box.point(0).y + box_height_l } };
	arrow9.set_color(Color::black);

	Graph_lib::Polygon arrowhead9;
	arrowhead9.add(Point{ arrow9.point(1) });
	arrowhead9.add(Point{ arrow9.point(1).x + arrowhead_size,
		arrow9.point(1).y - arrowhead_size / 2 });
	arrowhead9.add(Point{ arrow9.point(1).x + arrowhead_size,
		arrow9.point(1).y + arrowhead_size / 2 });
	arrowhead9.set_color(Color::black);
	arrowhead9.set_fill_color(Color::black);

	Line arrow10{ Point{ graph_c_box.point(0).x + box_width_s * 3 / 4,
		graph_c_box.point(0).y },
		Point{ graph_h_box.point(0).x + box_width_l / 2,
		graph_h_box.point(0).y + box_height_l } };
	arrow10.set_color(Color::black);

	Graph_lib::Polygon arrowhead10;
	arrowhead10.add(Point{ arrow10.point(1) });
	arrowhead10.add(Point{ arrow10.point(1).x - arrowhead_size / 2,
		arrow10.point(1).y + arrowhead_size });
	arrowhead10.add(Point{ arrow10.point(1).x + arrowhead_size / 2,
		arrow10.point(1).y + arrowhead_size });
	arrowhead10.set_color(Color::black);
	arrowhead10.set_fill_color(Color::black);

	Line arrow11{ Point{ ch_12_c_box.point(0).x + box_width_l * 2 / 3,
		ch_12_c_box.point(0).y },
		Point{ graph_h_box.point(0).x + box_width_l * 9 / 16,
		graph_h_box.point(0).y + box_height_l } };
	arrow11.set_color(Color::black);

	Graph_lib::Polygon arrowhead11;
	arrowhead11.add(Point{ arrow11.point(1) });
	arrowhead11.add(Point{ arrow11.point(1).x - arrowhead_size / 2,
		arrow11.point(1).y + arrowhead_size });
	arrowhead11.add(Point{ arrow11.point(1).x + arrowhead_size / 2,
		arrow11.point(1).y + arrowhead_size });
	arrowhead11.set_color(Color::black);
	arrowhead11.set_fill_color(Color::black);

	Line arrow12{ Point{ s_win_h_box.point(0).x + box_width_l * 2 / 3,
		s_win_h_box.point(0).y }, Point{gui_h_box.point(0).x,
		gui_h_box.point(0).y + box_height_l } };
	arrow12.set_color(Color::black);

	Graph_lib::Polygon arrowhead12;
	arrowhead12.add(Point{ arrow12.point(1) });
	arrowhead12.add(Point{ arrow12.point(1).x - arrowhead_size,
		arrow12.point(1).y - arrowhead_size / 2 });
	arrowhead12.add(Point{ arrow12.point(1).x - arrowhead_size,
		arrow12.point(1).y + arrowhead_size / 2 });
	arrowhead12.set_color(Color::black);
	arrowhead12.set_fill_color(Color::black);

	Line arrow13{ Point{ gui_c_box.point(0).x + box_width_s * 3 / 4,
		gui_c_box.point(0).y }, Point{gui_h_box.point(0).x + box_width_l / 2,
		gui_h_box.point(0).y + box_height_l } };
	arrow13.set_color(Color::black);

	Graph_lib::Polygon arrowhead13;
	arrowhead13.add(Point{ arrow13.point(1) });
	arrowhead13.add(Point{ arrow13.point(1).x + arrowhead_size,
		arrow13.point(1).y - arrowhead_size / 2 });
	arrowhead13.add(Point{ arrow13.point(1).x + arrowhead_size,
		arrow13.point(1).y + arrowhead_size / 2 });
	arrowhead13.set_color(Color::black);
	arrowhead13.set_fill_color(Color::black);

	Line arrow14{ Point{ ch_12_c_box.point(0).x + box_width_l * 2 / 3,
		ch_12_c_box.point(0).y }, Point{s_win_h_box.point(0).x,
		s_win_h_box.point(0).y + box_height_l } };
	arrow14.set_color(Color::black);

	Graph_lib::Polygon arrowhead14;
	arrowhead14.add(Point{ arrow14.point(1) });
	arrowhead14.add(Point{ arrow14.point(1).x - arrowhead_size,
		arrow14.point(1).y - arrowhead_size / 2 });
	arrowhead14.add(Point{ arrow14.point(1).x - arrowhead_size,
		arrow14.point(1).y + arrowhead_size / 2 });
	arrowhead14.set_color(Color::black);
	arrowhead14.set_fill_color(Color::black);

	s_win.attach(fltk_h_box1);
	s_win.attach(fltk_h_box2);
	s_win.attach(fltk_h_box3);
	s_win.attach(fltk_h_label);
	s_win.attach(fltk_c_box1);
	s_win.attach(fltk_c_box2);
	s_win.attach(fltk_c_box3);
	s_win.attach(fltk_c_label);
	s_win.attach(point_h_box);
	s_win.attach(point_h_label1);
	s_win.attach(point_h_label2);
	s_win.attach(win_h_box);
	s_win.attach(win_h_label1);
	s_win.attach(win_h_label2);
	s_win.attach(win_h_label3);
	s_win.attach(win_h_label4);
	s_win.attach(graph_h_box);
	s_win.attach(graph_h_label1);
	s_win.attach(graph_h_label2);
	s_win.attach(graph_h_label3);
	s_win.attach(graph_h_label4);
	s_win.attach(gui_h_box);
	s_win.attach(gui_h_label1);
	s_win.attach(gui_h_label2);
	s_win.attach(gui_h_label3);
	s_win.attach(gui_h_label4);
	s_win.attach(window_c_box);
	s_win.attach(window_c_label1);
	s_win.attach(window_c_label2);
	s_win.attach(graph_c_box);
	s_win.attach(graph_c_label1);
	s_win.attach(graph_c_label2);
	s_win.attach(gui_c_box);
	s_win.attach(gui_c_label1);
	s_win.attach(gui_c_label2);
	s_win.attach(s_win_h_box);
	s_win.attach(s_win_h_label1);
	s_win.attach(s_win_h_label2);
	s_win.attach(s_win_h_label3);
	s_win.attach(s_win_h_label4);
	s_win.attach(ch_12_c_box);
	s_win.attach(ch_12_c_label1);
	s_win.attach(ch_12_c_label2);
	s_win.attach(ch_12_c_label3);
	s_win.attach(ch_12_c_label4);
	s_win.attach(arrow1);
	s_win.attach(arrowhead1);
	s_win.attach(arrow2);
	s_win.attach(arrowhead2);
	s_win.attach(arrow3);
	s_win.attach(arrowhead3);
	s_win.attach(arrow4);
	s_win.attach(arrowhead4);
	s_win.attach(arrow5);
	s_win.attach(arrowhead5);
	s_win.attach(arrow6);
	s_win.attach(arrowhead6);
	s_win.attach(arrow7);
	s_win.attach(arrowhead7);
	s_win.attach(arrow8);
	s_win.attach(arrowhead8);
	s_win.attach(arrow9);
	s_win.attach(arrowhead9);
	s_win.attach(arrow10);
	s_win.attach(arrowhead10);
	s_win.attach(arrow11);
	s_win.attach(arrowhead11);
	s_win.attach(arrow12);
	s_win.attach(arrowhead12);
	s_win.attach(arrow13);
	s_win.attach(arrowhead13);
	s_win.attach(arrow14);
	s_win.attach(arrowhead14);

	s_win.wait_for_button();
}
catch (exception & e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}