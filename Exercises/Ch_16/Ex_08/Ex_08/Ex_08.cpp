#include "../Graph.h"
#include "../GUI.h"
#include "../Window.h"

namespace Graph_lib {

struct Currency {
	string name;
	double rate = 0;
};

istream& operator>>(istream& is, Currency& currency)
{
	char c1;
	char c2;
	string n;
	double r;

	is >> c1 >> n >> r >> c2;
	if (is.eof())
		return is;
	if (is.fail() || c1 != '(' || c2 != ')')
		throw exception("operator>>() - invalid Currency format");

	currency.name = n;
	currency.rate = r;

	return is;
}

class Currency_window : Window {
public:
	Currency_window(Point, int, int, const string&);

	void wait_for_button();
private:
	enum class Currency_code {
		USD, EUR, JPY, GBP, AUD, CAD
	};
	vector<Currency> currencies;
	Currency_code base_code = Currency_code::USD;
	Currency_code converted_code = Currency_code::USD;
	bool next_button_pushed = false;
	Button next_button;
	Button quit_button;
	In_box currency_in;
	Out_box currency_out;
	Button convert_button;
	Menu base_menu;
	Menu converted_menu;

	void next() { next_button_pushed = true; }
	void quit() { hide(); }
	void convert();
	void set_base_code(Currency_code cc) { base_code = cc; }
	void set_converted_code(Currency_code cc) { converted_code = cc; }
};

Currency_window::Currency_window(Point tl, int width, int height, const string& label) :
	Window{ tl, width, height, label },
	next_button{ { width * 18 / 20, 0 }, width / 20, height / 20, "Next",
		[](Address, Address addr) { reference_to<Currency_window>(addr).next(); } },
	quit_button{ { width * 19 / 20, 0 }, width / 20, height / 20, "Quit",
		[](Address, Address addr) { reference_to<Currency_window>(addr).quit(); } },
	currency_in{ { width / 8, height / 2 }, width / 4, height / 8, "Base Amount" },
	currency_out{ { width * 5 / 8, height / 2 }, width / 4, height / 8, "Converted Amount" },
	convert_button{ { width * 7 / 16, height * 3 / 4 }, width / 8, height / 16, "Convert",
		[](Address, Address addr) { reference_to<Currency_window>(addr).convert(); } },
	base_menu{ { width / 8, height * 3 / 8 }, width / 24, height / 8, Menu::horizontal, "Base Currency" },
	converted_menu{ { width * 5 / 8, height * 3 / 8 }, width / 24, height / 8, Menu::horizontal,
		"Converted Currency" }
{
	const string input_file{ "Ex_08_input.txt" };
	ifstream ifs{ input_file };
	if (!ifs)
		throw exception("Currency_window() - couldn't open file");
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);

	for (Currency currency; ifs >> currency;)
		currencies.push_back(currency);

	attach(next_button);
	attach(quit_button);
	attach(currency_in);
	attach(currency_out);
	attach(convert_button);
	base_menu.attach(new Button{ { 0, 0 }, 0, 0, currencies[int(Currency_code::USD)].name,
		[](Address, Address addr) { reference_to<Currency_window>(addr).set_base_code(Currency_code::USD); } });
	base_menu.attach(new Button{ { 0, 0 }, 0, 0, currencies[int(Currency_code::EUR)].name,
		[](Address, Address addr) { reference_to<Currency_window>(addr).set_base_code(Currency_code::EUR); } });
	base_menu.attach(new Button{ { 0, 0 }, 0, 0, currencies[int(Currency_code::JPY)].name,
		[](Address, Address addr) { reference_to<Currency_window>(addr).set_base_code(Currency_code::JPY); } });
	base_menu.attach(new Button{ { 0, 0 }, 0, 0, currencies[int(Currency_code::GBP)].name,
		[](Address, Address addr) { reference_to<Currency_window>(addr).set_base_code(Currency_code::GBP); } });
	base_menu.attach(new Button{ { 0, 0 }, 0, 0, currencies[int(Currency_code::AUD)].name,
		[](Address, Address addr) { reference_to<Currency_window>(addr).set_base_code(Currency_code::AUD); } });
	base_menu.attach(new Button{ { 0, 0 }, 0, 0, currencies[int(Currency_code::CAD)].name,
		[](Address, Address addr) { reference_to<Currency_window>(addr).set_base_code(Currency_code::CAD); } });
	attach(base_menu);
	converted_menu.attach(new Button{ { 0, 0 }, 0, 0, currencies[int(Currency_code::USD)].name,
		[](Address, Address addr) { 
			reference_to<Currency_window>(addr).set_converted_code(Currency_code::USD); 
		} });
	converted_menu.attach(new Button{ { 0, 0 }, 0, 0, currencies[int(Currency_code::EUR)].name,
		[](Address, Address addr) { 
			reference_to<Currency_window>(addr).set_converted_code(Currency_code::EUR); 
		} });
	converted_menu.attach(new Button{ { 0, 0 }, 0, 0, currencies[int(Currency_code::JPY)].name,
		[](Address, Address addr) { 
			reference_to<Currency_window>(addr).set_converted_code(Currency_code::JPY); 
		} });
	converted_menu.attach(new Button{ { 0, 0 }, 0, 0, currencies[int(Currency_code::GBP)].name,
		[](Address, Address addr) { 
			reference_to<Currency_window>(addr).set_converted_code(Currency_code::GBP); 
		} });
	converted_menu.attach(new Button{ { 0, 0 }, 0, 0, currencies[int(Currency_code::AUD)].name,
		[](Address, Address addr) { 
			reference_to<Currency_window>(addr).set_converted_code(Currency_code::AUD); 
		} });
	converted_menu.attach(new Button{ { 0, 0 }, 0, 0, currencies[int(Currency_code::CAD)].name,
		[](Address, Address addr) { 
			reference_to<Currency_window>(addr).set_converted_code(Currency_code::CAD); 
		} });
	attach(converted_menu);
}

void Currency_window::wait_for_button()
{
	while (!next_button_pushed)
		Fl::wait();
	next_button_pushed = false;
	Fl::redraw();
}

void Currency_window::convert()
{
	double base_amount = stod(currency_in.get_string());
	double usd_amount = base_amount / currencies[int(base_code)].rate;
	string converted_amount_str;
	ostringstream oss{ converted_amount_str };
	oss << setprecision(3) << usd_amount * currencies[int(converted_code)].rate;
	currency_out.put(oss.str());
}
}

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 8, y_max() / 8 };
	const int win_width = x_max() * 3 / 4;
	const int win_height = y_max() * 3 / 4;
	const string win_name{ "My window" };

	Currency_window c_win{ win_tl, win_width, win_height, win_name };

	c_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}