#include "../../../../std_lib_facilities.h"

int main() {
	int val = 0;

	// collect integer value from user and determine whether it is odd or even
	cout << "Enter an integer: ";
	while (cin >> val)
		cout << "The value " << val << " is " << (val % 2 == 0 ? "even" : "odd") << ".\n";
}