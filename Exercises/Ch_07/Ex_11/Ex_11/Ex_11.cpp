///*
//	A simple number-guessing game. The user is prompted to think of a number in a certain range.
//	The computer then attempts to guess that number by asking if it is less than a particular value,
//	recursively narrowing the range until only one possibile number remains.
//*/
//
//#include "../../../../std_lib_facilities.h"
//
//void introduce_game();
//void make_guess();
//void narrow_range();
//void finish_game();
//
//const char confirm = 'y';	// valid positive user response
//const char deny = 'n';	// valid negative user response
//const int init_low_bound = 1;	// lower bound of range of numbers from which user can pick
//const int init_high_bound = 100;	// upper bound of range of numbers from which user can pick
//
//char response = 0;	// user's response to computer's question
//int guess = init_high_bound / 2;	// current computer guess
//int low_bound = init_low_bound;	// lower bound of range of numbers from which computer can guess
//int high_bound = init_high_bound;	// upper bound of range of numbers from which computer can guess
//
//int main() {
//	introduce_game();
//
//	while (low_bound != high_bound) {	// if range is 1, stop trying to narrow it
//		try {
//			make_guess();
//			narrow_range();
//		}
//		catch (exception& e) {
//			cerr << "Error: " << e.what() << ".\n";
//		}
//	}
//
//	finish_game();
//}
//
//// print rules of game
//void introduce_game() {
//	cout << "Think of a number between " << init_low_bound << " and " << init_high_bound << ".\n"
//		<< "Enter '" << confirm << "' or '" << deny << "' to confirm or deny computer guesses.\n\n";
//}
//
//// ask user to confirm or deny guess
//void make_guess() {
//	// prepare input stream for new characters
//	cin.clear();
//	cin.ignore(cin.rdbuf()->in_avail());
//
//	cout << "Is your number less than " << guess << "?\n";
//	cin >> response;
//	if (response != confirm && response != deny)	// validate input
//		error("invalid response");
//}
//
//// narrow range of possible numbers
//void narrow_range() {
//	if (response == confirm) {
//		high_bound = guess - 1;	// number is at least 1 less than guess
//		if (high_bound - low_bound == 1)	// if range is 2, number must be lesser value
//			guess -= 1;
//		else
//			guess -= (high_bound - low_bound) / 2;	// update guess to middle of range
//	}
//	else {
//		low_bound = guess;	// number is larger than or equal to guess
//		if (high_bound - low_bound == 1)	// if range is 2, number must be greater value
//			guess += 1;
//		else
//			guess += (high_bound - low_bound) / 2;	// update guess to middle of range
//	}
//}
//
//// print final (correct) guess
//void finish_game() {
//	cout << "I've got it! Your number is " << low_bound << '\n';
//}

///

/*
	A simple quadratic calculator program. The user is prompted to input values for the coeffecients
	a, b, and c of a quadratic equation. The computer then either returns a pair of real roots or
	indicates that the roots are imaginary or infinite.
*/

#include "../../../../std_lib_facilities.h"

// contains pair of real quadratic roots
class Root_pair {
private:
	double x1 = 0;	// first root
	double x2 = 0;	// second root
public:
	Root_pair(double d1, double d2);
	double get_x1();
	double get_x2();
};

void get_input();
Root_pair calculate_roots(double a, double b, double c);

double a = 0, b = 0, c = 0;	// quadratic coefficient

int main() {
	cout << "Enter three coefficients for a quadratic equation (a, b, c):\n";

	while (true) {
		try {
			get_input();
			Root_pair root_pair = calculate_roots(a, b, c);
			cout << "x1 = " << root_pair.get_x1() << ", x2 = " << root_pair.get_x2() << '\n';
		}
		catch (exception& e) {
			cerr << "Error: " << e.what() << ".\n";
		}
	}
}

// construct root pair with two real roots
Root_pair::Root_pair(double d1, double d2) {
	x1 = d1;
	x2 = d2;
}

// get first root
double Root_pair::get_x1() {
	return x1;
}

// get second root
double Root_pair::get_x2() {
	return x2;
}

// prompt user to input coefficients
void get_input() {
	// prepare input stream for new characters
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	
	cin >> a >> b >> c;
	if (!cin)	// validate input
		error("invalid input");
}

// calculate roots of quadratic equation
Root_pair calculate_roots(double a, double b, double c) {
	// validate input
	if (b * b < 4 * a * c)	// avoid taking square root of a negative number
		error("imaginary roots");
	if (a == 0)	// avoid dividing by zero
		error("infinite roots");

	// calculate roots
	double x1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
	double x2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);

	return Root_pair(x1, x2);
}