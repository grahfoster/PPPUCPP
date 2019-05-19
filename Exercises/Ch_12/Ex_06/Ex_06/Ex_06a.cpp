//#include "../Graph.h"
//#include "../Simple_window.h"
//
//int main()
//try {
//	using namespace Graph_lib;
//
//	const Point win_tl{ x_max() / 4, y_max() / 4 };
//	const int win_width = x_max() / 2;
//	const int win_height = y_max() / 2;
//	const string win_name{ "My window" };
//	Simple_window s_win{ win_tl, win_width, win_height, win_name };
//
//	Graph_lib::Rectangle rect{ Point{ 0, 0 }, win_width + 100,
//		win_height + 100 };
//
//	s_win.attach(rect);
//
//	s_win.wait_for_button();
//}
//catch (exception& e) {
//	cerr << "Error: " << e.what() << ".\n";
//}
//catch (...) {
//	cerr << "Unexpected error.\n";
//}