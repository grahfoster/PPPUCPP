/*
	Simple calculator
	This program implements a basic expression calculator. It supports basic arithmetic operations,
	including +, -, *, /, %, and !, as well as more advanced functions like sqrt(x) and pow(x, i). Users
	may declare their own constants and variables, as well as assign new values to variables.
	Future improvement: add a quadratic function.
	Input from is; output to os.
	The grammar for input is:
		Calculation:
			Statement
			Print
			Help
			Calculation Calculation
		Statement:
			Declaration
			Assignment
			Expression
		Print:
			'\n'
		Declaration:
			"#" Name '=' Expression
			"#" "const" Name '=' Expression
		Assignment:
			Name '-' Expression
		Expression:
			Term
			Expression '+' Term
			Expression '-' Term
		Name:
			alphanumeric string (may include '_')
		Term:
			Fact
			Term '*' Fact
			Term '/' Fact
			Term '%' Fact
		Fact:
			Primary '!'
			Primary
		Primary:
			Number
			Name
			"sqrt" '(' Expression ')'
			"pow" '(' Expression ',' Expression ')'
			'(' Expression ')'
			'+' Primary
			'-' Primary
		Number:
			integer
		Name:
			alphanumeric string (underscores allowed)
		Stream:
			string
	Input comes from stream through the Token_stream called ts.
*/

#include "../Graph.h"
#include "../GUI.h"
#include "../Window.h"

//------------------------------------------------------------------------------

class Token {
public:
	char kind;	// what kind of token
	int value;	// for numbers
	string name;	// for variables
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, int val) :kind(ch), value(val) { }
	Token(char ch, string s) :kind(ch), name(s) { }
};

//------------------------------------------------------------------------------

class Token_stream {
	bool full;	// is there a Token in the buffer?
	Token buffer;	// here is where we keep a Token put back using unget()
	ifstream stream;
	ofstream os;
public:
	Token_stream() : full(0), buffer(0) {};

	void open_ifstream(string file) { stream.open(file); }
	void open_ofstream(string file) { os.open(file); }
	ifstream& get_ifstream() { return stream; }
	ofstream& get_ofstream() { return os; }
	Token get(istream&);
	void unget(Token t) { buffer = t; full = true; }	// put a token back into buffer

	void ignore(istream&, char c1, char c2);	// ignore the input stream until we reach a certain character
};

const char help = 'h';
const char newline = '\n';
const char let = 'L';
const char square = 'S';
const char power = 'P';
const char print = '\n';
const char number = '8';
const char constant = 'C';
const char name = 'a';
const string helpkey = "help";
const string declkey = "#";
const string sqrtkey = "sqrt";
const string powkey = "pow";
const string constkey = "const";

Token Token_stream::get(istream& is)
{
	if (full) { full = false; return buffer; }	// do we have a Token ready?
	char ch;
	is.get(ch);
	if (is.eof())
		return Token(print);
	while (isspace(ch)) {
		if (ch == newline) return Token(print);	// treat newline as we would a print character
		is.get(ch);	//	ignore whitespace and continue reading input
	}
	switch (ch) {
	case '(':
	case ')':
	case ',':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '!':
	case '=':	// for initializing
		return Token(ch);
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	is.unget();
	int val;
	is >> val;
	return Token(number, val);
	}
	default:
		if (string(1, ch) == declkey)
			return Token(let);
		if (isalpha(ch) || ch == '_') {
			string s;
			s += ch;	// add first character to alphanumeric string
			while (is.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;	// finish forming string
			is.unget();
			if (s == helpkey) return Token(help);
			if (s == sqrtkey) return Token(square);
			if (s == powkey) return Token(power);
			if (s == constkey) return Token(constant);
			return Token(name, s);	// must be a variable or constant name
		}
		error("Bad token");
	}
}

void Token_stream::ignore(istream& is, char c1, char c2)
{
	if (full && (c1 == buffer.kind || c2 == buffer.kind)) {	// check if the token we want is already in the buffer
		full = false;
		return;
	}
	full = false;

	char ch;
	while (is.get(ch))	// eat input until we reach the character we want
		if (ch == c1 || ch == c2) return;
}

//------------------------------------------------------------------------------

class Variable {
public:
	bool constant;
	string name;
	int value;
	Variable(string n, int v) :constant(0), name(n), value(v) { }
	Variable(bool b, string n, int v) :constant(b), name(n), value(v) { }
};

vector<Variable> names;	// contains any program- or user-initialized variables

//------------------------------------------------------------------------------

class Symbol_table {
public:
	vector<Variable> names;	// contains any program- or user-initialized variables
	int get(string s);
	void set(string s, int d);
	bool is_declared(string s);
	void declare(Variable v);
};

int Symbol_table::get(string s)	// get the value of a variable by name
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ", s);	// no such variable found
}

void Symbol_table::set(string s, int d)	// set the value of an existing variable
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) {
			if (names[i].constant) error("set: cannot change constant value");
			names[i].value = d;
			return;
		}
	error("set: undefined name ", s);	// variable doesn't exist
}

bool Symbol_table::is_declared(string s)	// check if a variable with a certain name has alrady been declared
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;	// variable has already been declared
	return false;
}

void Symbol_table::declare(Variable v) {	// add a new variable to the vector
	names.push_back(v);
}

Symbol_table st;	// provides get(), set(), is_declared(), and declare()

//------------------------------------------------------------------------------

Token_stream ts; // provides get() and unget()

//------------------------------------------------------------------------------

int expression(istream& is);	// declaration so that primary() can call expression()

// deal with numbers, signs, and parentheses
int primary(istream& stream)
{
	Token t = ts.get(stream);
	switch (t.kind) {
	case square:	// handle 'sqrt(' expression ')'
	{	t = ts.get(stream);
	if (t.kind != '(') error("'(' expected");
	int d = expression(stream);
	if (d < 0) error("sqrt() called on negative number");
	t = ts.get(stream);
	if (t.kind != ')') error("')' expected");
	double temp = sqrt(d);
	return narrow_cast<int>(temp);
	}
	case power:	// handle 'pow(' expression ',' expression ')'
	{	t = ts.get(stream);
	if (t.kind != '(') error("'(' expected");
	int d = expression(stream);
	t = ts.get(stream);
	if (t.kind != ',') error("',' expected");
	int i = expression(stream);
	t = ts.get(stream);
	if (t.kind != ')') error("')' expected");
	double temp = pow(d, i);
	return narrow_cast<int>(temp);
	}
	case '(':	// handle '(' expression ')'
	{	int d = expression(stream);
	t = ts.get(stream);
	if (t.kind != ')') error("')' expected");
	return d;
	}
	case '-':
		return -primary(stream);	// return negative value of primary
	case'+':
		return primary(stream);	// return positive value of primary
	case number:
		return t.value;	// return the number's value
	case name:
		return st.get(t.name);	// return the name's value
	default:
		error("primary expected");
	}
}

// deal with !
int fact(istream& is)
{
	int left = primary(is);
	Token t = ts.get(is);

	while (true) {
		if (t.kind == '!') {
			if (left == 0)	left = 1;	// "0!" is equal to 1
			else {
				double temp = left;
				for (int i = 1; i < left; ++i)	// calculate factorial
					temp *= i;
				left = narrow_cast<int>(temp);
			}
			t = ts.get(is);
		}
		else {
			ts.unget(t);
			return left;
		}
	}
}

// deal with *, /, and %
int term(istream& is)
{
	int left = fact(is);
	while (true) {
		Token t = ts.get(is);
		switch (t.kind) {
		case '*':
		{
			double temp = left;
			temp *= fact(is);
			left = narrow_cast<int>(temp);
			break;
		}
		case '/':
		{	int d = fact(is);
		if (d == 0) error("divide by zero");
		left /= d;
		break;
		}
		case '%':
		{	int d = fact(is);
		if (d == 0) error("%:divide by zero");
		left = fmod(left, d);
		break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

// deal with + and -
int expression(istream& is)
{
	int left = term(is);
	double temp = left;
	while (true) {
		Token t = ts.get(is);
		switch (t.kind) {
		case '+':
			temp += term(is);
			left = narrow_cast<int>(temp);
			break;
		case '-':
			temp -= term(is);
			left = narrow_cast<int>(temp);
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

// deal with variable assignment
int assignment(istream& is, Token t)
{
	int d = expression(is);
	st.set(t.name, d);	// update the variable's value
	return d;
}

// deal with variable initialization
int declaration(istream& is)
{
	Token t = ts.get(is);
	if (t.kind != name && t.kind != constant) error("name expected in declaration"); 	// check if a name follows "let"
	bool is_constant = t.kind == constant;
	if (is_constant) t = ts.get(is);
	string name = t.name;
	if (st.is_declared(name)) error(name, " declared twice");	// check if the variable has already been declared
	Token t2 = ts.get(is);
	if (t2.kind != '=') error("= missing in declaration of ", name);	// check for '=' after variable name
	int d = expression(is);	// evaluate the final expression
	st.declare(Variable(is_constant, name, d));	// add the new variable to the vector
	return d;
}

// differentiate between intializations and simple calculations
int statement(istream& is)
{
	Token t = ts.get(is);
	switch (t.kind) {
	case let:
		return declaration(is);
	case name:
		char ch;
		is.get(ch);
		if (ch == '=') return assignment(is, t);	// pass in the token so we can use its name
		is.unget();	// put the non-'=' back; it must be an expression
	default:
		ts.unget(t);
		return expression(is);
	}
}

//------------------------------------------------------------------------------

// recover from errors without closing program
void clean_up_mess(istream& is)
{
	ts.ignore(is, print, newline);
}

//------------------------------------------------------------------------------

// print out helpful instructions to the user
void print_help()
{
	cout << "Welcome to our simple calculator.\n"
		"Please enter expressions using integers.\n"
		"Available operators: +, -, *, /, %, !.\n"
		"Available functions: sqrt(x), pow(x, i).\n"
		"Parentheses may be used to enclose sub-expressions but not to indicate multiplication.\n"
		"This calculator supports variable declaration and assignment.\n"
		"To declare a variable, type '" << declkey << "' before your equation.\n"
		"To declare a constant, type \"" << constkey << "\" after '" << declkey << "'.\n";
	return;
}

//------------------------------------------------------------------------------

// evaluate user input
void calculate(istream& is, ostream& os)
try {
	Token t = ts.get(is);
	while (t.kind == print) {
		if (is.eof())
			error("no input");
		t = ts.get(is);
	}
	if (t.kind == help) {
		print_help();
		return;
	}
	ts.unget(t);
	os << statement(is) << endl;
}
catch (runtime_error& e) {
	os << e.what() << endl;
	is.unget();
	clean_up_mess(is);
}

//------------------------------------------------------------------------------

namespace Graph_lib {

class Calculator_window : Window {
public:
	Calculator_window(Point, int, int, const string&);

	void wait_for_button();
private:
	bool next_button_pushed = false;
	Button next_button;
	Button quit_button;
	In_box calculation_in;
	Out_box calculation_out;
	Button calculate_button;

	void next() { next_button_pushed = true; }
	void quit() { hide(); }
	void do_calculation();
};

Calculator_window::Calculator_window(Point tl, int width, int height, const string& label) :
	Window{ tl, width, height, label },
	next_button{ { x_max() * 18 / 20, 0 }, x_max() / 20, y_max() / 20, "Next",
		[](Address, Address addr) { reference_to<Calculator_window>(addr).next(); } },
	quit_button{ { x_max() * 19 / 20, 0 }, x_max() / 20, y_max() / 20, "Quit",
		[](Address, Address addr) { reference_to<Calculator_window>(addr).quit(); } },
	calculation_in{ { width / 8, height / 2 }, width / 4, height / 8, "Calculation" },
	calculation_out{ { width * 5 / 8, height / 2 }, width / 4, height / 8, "Answer" },
	calculate_button{ { width * 7 / 16, height * 3 / 4 }, width / 8, height / 16, "Calculate",
		[](Address, Address addr) { reference_to<Calculator_window>(addr).do_calculation(); } }
{
	attach(next_button);
	attach(quit_button);
	attach(calculation_in);
	attach(calculation_out);
	attach(calculate_button);
}

void Calculator_window::wait_for_button()
{
	while (!next_button_pushed)
		Fl::wait();
	next_button_pushed = false;
	Fl::redraw();
}

void Calculator_window::do_calculation()
{
	string calculation = calculation_in.get_string();
	istringstream iss{ calculation };
	string answer;
	ostringstream oss{ answer };
	calculate(iss, oss);
	string clean_answer = oss.str().substr(0, oss.str().size() - 1);
	calculation_out.put(clean_answer);

}
}

int main()
try {
	using namespace Graph_lib;

	const Point win_tl{ x_max() / 8, y_max() / 8 };
	const int win_width = x_max() * 3 / 4;
	const int win_height = y_max() * 3 / 4;
	const string win_name{ "My window" };

	Calculator_window c_win{ win_tl, win_width, win_height, win_name };

	c_win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}

