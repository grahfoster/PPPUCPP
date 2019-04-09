/*
	Simple calculator
	This program implements a basic expression calculator. It supports basic arithmetic operations,
	including +, -, *, /, %, and !, as well as more advanced functions like sqrt(x) and pow(x, i). Users
	may declare their own constants and variables, as well as assign new values to variables.
	Future improvements: add a quadratic function; solve eaten input after failed expressions beginning with a name.
	Input from cin; output to cout.
	The grammar for input is:
		Calculation:
			Statement
			Print
			Help
			Quit
			Calculation Calculation
		Statement:
			Declaration
			Expression
		Print:
			';'
			'\n'
		Quit:
			"exit"
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
	Input comes from cin through the Token_stream called ts.
*/

#include "../../../../std_lib_facilities.h"

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
public:
	Token_stream() :full(0), buffer(0) { }

	Token get();
	void unget(Token t) { buffer = t; full = true; }	// put a token back into buffer

	void ignore(char);	// ignore the input stream until we reach a certain character
};

const char help = 'h';
const char newline = '\n';
const char let = 'L';
const char quit = 'Q';
const char square = 'S';
const char power = 'P';
const char print = ';';
const char number = '8';
const char constant = 'C';
const char name = 'a';
const string helpkey = "help";
const string declkey = "#";
const string quitkey = "quit";
const string sqrtkey = "sqrt";
const string powkey = "pow";
const string constkey = "const";

Token Token_stream::get()
{
	if (full) { full = false; return buffer; }	// do we have a Token ready?
	char ch;
	cin.get(ch);
	while (isspace(ch)) {
		if (ch == newline) return Token(print);	// treat newline as we would a print character
		cin.get(ch);	//	ignore whitespace and continue reading input
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
	case print:	// for "print"
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
	{	cin.unget();
	int val;
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
			if (s == helpkey) return Token(help);
			if (s == quitkey) return Token(quit);
			if (s == sqrtkey) return Token(square);
			if (s == powkey) return Token(power);
			if (s == constkey) return Token(constant);
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

int expression();	// declaration so that primary() can call expression()

// deal with numbers, signs, and parentheses
int primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case square:	// handle 'sqrt(' expression ')'
	{	t = ts.get();
	if (t.kind != '(') error("'(' expected");
	int d = expression();
	if (d < 0) error("sqrt() called on negative number");
	t = ts.get();
	if (t.kind != ')') error("')' expected");
	double temp = sqrt(d);
	return narrow_cast<int>(temp);
	}
	case power:	// handle 'pow(' expression ',' expression ')'
	{	t = ts.get();
	if (t.kind != '(') error("'(' expected");
	int d = expression();
	t = ts.get();
	if (t.kind != ',') error("',' expected");
	int i = expression();
	t = ts.get();
	if (t.kind != ')') error("')' expected");
	double temp = pow(d, i);
	return narrow_cast<int>(temp);
	}
	case '(':	// handle '(' expression ')'
	{	int d = expression();
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
		return st.get(t.name);	// return the name's value
	default:
		error("primary expected");
	}
}

// deal with !
int fact()
{
	int left = primary();
	Token t = ts.get();

	while (true) {
		if (t.kind == '!') {
			if (left == 0)	left = 1;	// "0!" is equal to 1
			else {
				double temp = left;
				for (int i = 1; i < left; ++i)	// calculate factorial
					temp *= i;
				left = narrow_cast<int>(temp);
			}
			t = ts.get();
		}
		else {
			ts.unget(t);
			return left;
		}
	}
}

// deal with *, /, and %
int term()
{
	int left = fact();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
		{
			double temp = left;
			temp *= fact();
			left = narrow_cast<int>(temp);
			break;
		}
		case '/':
		{	int d = fact();
		if (d == 0) error("divide by zero");
		left /= d;
		break;
		}
		case '%':
		{	int d = fact();
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
int expression()
{
	int left = term();
	double temp = left;
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			temp += term();
			left = narrow_cast<int>(temp);
			break;
		case '-':
			temp -= term();
			left = narrow_cast<int>(temp);
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

// deal with variable assignment
int assignment(Token t)
{
	int d = expression();
	st.set(t.name, d);	// update the variable's value
	return d;
}

// deal with variable initialization
int declaration()
{
	Token t = ts.get();
	if (t.kind != name && t.kind != constant) error("name expected in declaration"); 	// check if a name follows "let"
	bool is_constant = t.kind == constant;
	if (is_constant) t = ts.get();
	string name = t.name;
	if (st.is_declared(name)) error(name, " declared twice");	// check if the variable has already been declared
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);	// check for '=' after variable name
	int d = expression();	// evaluate the final expression
	st.declare(Variable(is_constant, name, d));	// add the new variable to the vector
	return d;
}

// differentiate between intializations and simple calculations
int statement()
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

// print out helpful instructions to the user
void print_help()
{
	cout << "Welcome to our simple calculator.\n"
		<< "Please enter expressions using integers.\n"
		<< "Available operators: +, -, *, /, %, !.\n"
		<< "Available functions: sqrt(x), pow(x, i).\n"
		<< "Parentheses may be used to enclose sub-expressions but not to indicate multiplication.\n"
		<< "This calculator supports variable declaration and assignment.\n"
		<< "To declare a variable, type '" << declkey << "' before your equation.\n"
		<< "To declare a constant, type \"" << constkey << "\" after '" << declkey << "'.\n"
		<< "Enter a newline or type \'" << print << "\' to calculate your expression.\n"
		<< "Type \"" << quitkey << "\" to quit the program.\n";
	return;
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
		if (t.kind == help) {
			print_help();
			continue;
		}
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
	st.declare(Variable(true, "k", 1000));	// initialize a variable k

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