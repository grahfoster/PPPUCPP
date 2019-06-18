#include "../Graph.h"
#include "../GUI.h"
#include "../Window.h"
#include <chrono>
#include <thread>

const double pi = atan(1) * 4;

namespace Graph_lib {

class Clock : public Circle {
public:
	Clock(Point, int);
	~Clock();

	void draw_lines() const override;

	void move_hour_hand(int = 1);
	void move_minute_hand(int = 1);
	void move_second_hand(int = 1);
private:
	const int num_hours = 12;
	const double hour_hand_ratio = 4.0 / 8;
	const double hour_label_ratio = 7.0 / 8;
	const double offset_ratio = 1.0 / 4;

	int hour_hand_position;
	int minute_hand_position;
	int second_hand_position;
	Line* hour_hand;
	Line* minute_hand;
	Line* second_hand;
	vector<Text*> hour_labels;

	void format_hands();
};

Clock::Clock(Point center, int radius) :
	Circle{ center, radius }, hour_hand{ new Line{ center, center } },
	minute_hand{ new Line{ center, center } }, second_hand{ new Line{ center, center } }
{
	time_t raw_time;
	time(&raw_time);
	tm local_time;
	localtime_s(&local_time, &raw_time);

	hour_hand_position = local_time.tm_hour;
	minute_hand_position = local_time.tm_min;
	second_hand_position = local_time.tm_sec;

	move_hour_hand(0);
	move_minute_hand(0);
	move_second_hand(0);

	set_color(Color::black);
	format_hands();

	for (int i = 0; i < num_hours; ++i) {
		hour_labels.push_back(
			new Text{ { center.x + int(radius * hour_label_ratio *
					cos((i + num_hours * offset_ratio) * 360 / num_hours * pi / 180)),
				center.y - int(radius * hour_label_ratio *
					sin((i + num_hours * offset_ratio) * 360 / num_hours * pi / 180)) },
			to_string(num_hours - i) });
		hour_labels.back()->set_color(Color::black);
	}
}

Clock::~Clock()
{
	delete hour_hand;
	delete minute_hand;
	delete second_hand;
	for (Text* hour_label : hour_labels)
		delete hour_label;
}

void Clock::draw_lines() const
{
	Circle::draw_lines();

	hour_hand->draw();
	minute_hand->draw();
	second_hand->draw();
	for (Text* hour_label : hour_labels)
		hour_label->draw();
}

void Clock::move_hour_hand(int i)
{
	hour_hand_position = (hour_hand_position + i) % num_hours;
	const int x = center().x + int(radius() * hour_hand_ratio *
		cos((num_hours * offset_ratio - hour_hand_position) * 360 / num_hours * pi / 180));
	const int y = center().y - int(radius() * hour_hand_ratio *
		sin((num_hours * offset_ratio - hour_hand_position) * 360 / num_hours * pi / 180));
	delete hour_hand;
	hour_hand = new Line{ center(), { x, y } };
	format_hands();
}

void Clock::move_minute_hand(int i)
{
	static const int num_minutes = 60;
	static const double minute_hand_ratio = 5.0 / 8;

	if (minute_hand_position == num_minutes - 1)
		move_hour_hand();

	minute_hand_position = (minute_hand_position + i) % num_minutes;
	const int x = center().x + int(radius() * minute_hand_ratio *
		cos((num_minutes * offset_ratio - minute_hand_position) * 360 / num_minutes * pi / 180));
	const int y = center().y - int(radius() * minute_hand_ratio *
		sin((num_minutes * offset_ratio - minute_hand_position) * 360 / num_minutes * pi / 180));
	delete minute_hand;
	minute_hand = new Line{ center(), { x, y } };
	format_hands();
}

void Clock::move_second_hand(int i)
{
	static const int num_seconds = 60;
	static const double second_hand_ratio = 6.0 / 8;

	if (second_hand_position == num_seconds - 1)
		move_minute_hand();

	second_hand_position = (second_hand_position + i) % num_seconds;
	const int x = center().x + int(radius() * second_hand_ratio *
		cos((num_seconds * offset_ratio - second_hand_position) * 360 / num_seconds * pi / 180));
	const int y = center().y - int(radius() * second_hand_ratio *
		sin((num_seconds * offset_ratio - second_hand_position) * 360 / num_seconds * pi / 180));
	delete second_hand;
	second_hand = new Line{ center(), { x, y } };
	format_hands();
}

void Clock::format_hands()
{
	hour_hand->set_color(Color::black);
	hour_hand->set_style(Line_style{ Line_style::solid, 6 });
	minute_hand->set_color(Color::black);
	minute_hand->set_style(Line_style{ Line_style::solid, 4 });
	second_hand->set_color(Color::black);
	second_hand->set_style(Line_style{ Line_style::solid, 2 });
}

class Clock_window : Window {
public:
	Clock_window(Point, int, int, const string&);

	void wait_for_button();
	void tick();
private:
	bool next_button_pushed;
	Button next_button;
	Button quit_button;
	Clock clock;

	void next() { next_button_pushed = true; }
	void quit() { hide(); }
};

Clock_window::Clock_window(Point tl, int width, int height, const string& label) :
	Window{ tl, width, height, label }, next_button_pushed{ false },
	next_button{ { x_max() * 18 / 20, 0 }, x_max() / 20, y_max() / 20, "Next",
		[](Address, Address addr) { reference_to<Clock_window>(addr).next(); } },
	quit_button{ { x_max() * 19 / 20, 0 }, x_max() / 20, y_max() / 20, "Quit",
		[](Address, Address addr) { reference_to<Clock_window>(addr).quit(); } },
	clock{ { width / 2, height / 2 }, height / 2 }
{
	attach(next_button);
	attach(quit_button);
	attach(clock);
}

void Clock_window::wait_for_button()
{
	while (!next_button_pushed)
		tick();
	next_button_pushed = false;
	Fl::redraw();
}

void Clock_window::tick()
{
	Fl::wait();
	clock.move_second_hand();
	redraw();
	this_thread::sleep_for(chrono::seconds(1));
}
}

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 8, y_max() / 8 };
	const int win_width = x_max() * 3 / 4;
	const int win_height = y_max() * 3 / 4;
	const string win_name{ "My window" };

	Clock_window c_win{ win_tl, win_width, win_height, win_name };

	c_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}