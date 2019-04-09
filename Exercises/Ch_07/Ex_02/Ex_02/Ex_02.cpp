/*
	Simple calculator
	This program implements a basic expression calculator.
	Input from cin; output to cout.
	The grammar for input is:
		Calculation:
			Statement
			Print
			Quit
			Calculation Statement
		Statement:
			Declaration
			Expression
		Print:
			';'
		Quit:
			"exit"
		Declaration:
			"#" Name '=' Expression
		Assignment:
			Name '-' Expression
		Expression:
			Term
			Expression '+' Term
			Expression '-' Term
		Name:
			alphanumeric string (may include '_')
		Term:
			Primary
			Term '*' Primary
			Term '/' Primary
			Term '%' Primary
		Primary:
			Number
			Name
			"sqrt" '(' Expression ')'
			"pow" '(' Expression ',' Expression ')'
			'(' Expression ')'
			'+' Primary
			'-' Primary
		Number:
			floating-point literal
	Input comes from cin through the Token_stream called ts.
*/

#include "../../../../std_lib_facilities.h"

//------------------------------------------------------------------------------

class Token {
public:
	char kind;	// what kind of token
	double value;	// for numbers
	string name;	// for variables
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, string s) :kind(ch), name(s) { }
};

//------------------------------------------------------------------------------

class Token_stream {
	bool full;	// is there a Token in the buffer?
	Token buffer;	// here is where we keep a Token put back using unget()
public:
	Token_stream() :full(0), buffer(0) { }

	Token get();
	void unget(Token t) { buffer = t; full = true; }	// put a token back into buffer

	void ignore(char);	// ignore the input stream until we reach a certain character
};

const char let = 'L';
const char quit = 'Q';
const char square = 'S';
const char power = 'P';
const char print = ';';
const char number = '8';
const char name = 'a';
const string declkey = "#";
const string quitkey = "exit";
const string sqrtkey = "sqrt";
const string powkey = "pow";

Token Token_stream::get()
{
	if (full) { full = false; return buffer; }	// do we have a Token ready?
	char ch;
	cin >> ch;
	switch (ch) {
	case '(':
	case ')':
	case ',':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case print:	// for "print"
	case '=':	// for initializing
		return Token(ch);
	case '.':	// floating-point literals may start with a decimal point
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
	{	cin.unget();
	double val;
	cin >> val;
	return Token(number, val);
	}
	default:
		if (string(1, ch) == declkey)
			return Token(let);
		if (isalpha(ch) || ch == '_') {
			string s;
			s += ch;	// add first character to alphanumeric string
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;	// finish forming string
			cin.unget();
			if (s == quitkey) return Token(quit);
			if (s == sqrtkey) return Token(square);
			if (s == powkey) return Token(power);
			return Token(name, s);
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {	// check if the token we want is already in the buffer
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)	// eat input until we reach the character we want
		if (ch == c) return;
}

//------------------------------------------------------------------------------

class Variable {
public:
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names;	// contains any program- or user-initialized variables

//------------------------------------------------------------------------------

double get_value(string s)	// get the value of a variable by name
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ", s);	// no such variable found
}

void set_value(string s, double d)	// set the value of an existing variable
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ", s);	// variable doesn't exist
}

bool is_declared(string s)	// check if a variable with a certain name has alrady been declared
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;	// variable has already been declared
	return false;
}

//------------------------------------------------------------------------------

Token_stream ts; // provides get() and unget()

//------------------------------------------------------------------------------

double expression();	// declaration so that primary() can call expression()

// deal with numbers, signs, and parentheses
double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case square:	// handle 'sqrt(' expression ')'
	{	t = ts.get();
	if (t.kind != '(') error("'(' expected");
	double d = expression();
	if (d < 0) error("sqrt() called on negative number");
	t = ts.get();
	if (t.kind != ')') error("')' expected");
	return sqrt(d);
	}
	case power:	// handle 'pow(' expression ',' expression ')'
	{	t = ts.get();
	if (t.kind != '(') error("'(' expected");
	double d = expression();
	t = ts.get();
	if (t.kind != ',') error("',' expected");
	int i = narrow_cast<int>(expression());
	t = ts.get();
	if (t.kind != ')') error("')' expected");
	return pow(d, i);
	}
	case '(':	// handle '(' expression ')'
	{	double d = expression();
	t = ts.get();
	if (t.kind != ')') error("')' expected");
	return d;
	}
	case '-':
		return -primary();	// return negative value of primary
	case'+':
		return primary();	// return positive value of primary
	case number:
		return t.value;	// return the number's value
	case name:
		return get_value(t.name);	// return the name's value
	default:
		error("primary expected");
	}
}

// deal with *, /, and %
double term()
{
	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{	double d = primary();
		if (d == 0) error("divide by zero");
		left /= d;
		break;
		}
		case '%':
		{	double d = primary();
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
double expression()
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

// deal with variable assignment
double assignment(Token t)
{
	double d = expression();
	set_value(t.name, d);	// update the variable's value
	return d;
}

// deal with variable initialization
double declaration()
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration"); 	// check if a name follows "let"
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice");	// check if the variable has already been declared
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);	// check for '=' after variable name
	double d = expression();	// evaluate the final expression
	names.push_back(Variable(name, d));	// add the new variable to the vector
	return d;
}

// differentiate between intializations and simple calculations
double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	case name:
		char ch;
		cin >> ch;
		if (ch == '=') return assignment(t);	// pass in the token so we can use its name
		cin.unget();	// put the non-'=' back; it must be an expression
	default:
		ts.unget(t);
		return expression();
	}
}

//------------------------------------------------------------------------------

// recover from errors without closing program
void clean_up_mess()
{
	ts.ignore(print);
}

//------------------------------------------------------------------------------

const string prompt = "> ";
const string result = "= ";

// evaluate user input
void calculate()
{
	while (cin) try {
		cout << prompt;	// indicate that program is ready for input
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;	// quit the program
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

//------------------------------------------------------------------------------

int main()

try {
	names.push_back(Variable("k", 1000));	// initialize a variable k

	calculate();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	char c;
	while (cin >> c && c != ';');
	return 1;
}
catch (...) {
	cerr << "exception\n";
	char c;
	while (cin >> c && c != ';');
	return 2;
}

//------------------------------------------------------------------------------