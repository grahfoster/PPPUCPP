#include "../Graph.h"
#include "../Simple_window.h"

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 4, 0 };
	const int win_width = 800;
	const int win_height = 1000;
	const string win_name{ "My window" };
	Simple_window s_win{ win_tl, win_width, win_height, win_name };

	const int num_rows = 8;
	const int num_columns = 8;
	const int square_side = 100;
	Vector_ref<Graph_lib::Rectangle> rects;
	for (int i = 0; i < num_rows; ++i)
		for (int j = 0; j < num_columns; ++j) {
			rects.push_back(new Graph_lib::Rectangle{{ j * square_side, i * square_side },
				square_side, square_side });
			rects[rects.size() - 1].set_color(Color::black);
			if (i == j)
				rects[rects.size() - 1].set_fill_color(Color::red);
			s_win.attach(rects[rects.size() - 1]);
		}

	const int num_imgs = 3;
	int img_width = 200;
	const string img_src = "Cyan_Hammer.jpg";
	Vector_ref<Image> imgs;
	for (int i = 0; i < num_imgs; ++i) {
		imgs.push_back(new Image{ { (i + 1) * img_width, i * img_width }, img_src });
		s_win.attach(imgs[imgs.size() - 1]);
	}

	img_width = 100;
	Image img_s{ { 0, 0}, "Cinna_Bit.jpg" };
	s_win.attach(img_s);
	
	for (int i = 0; i < num_rows; ++i) {
		s_win.wait_for_button();
		img_s.move(img_width, img_width);
	}
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}