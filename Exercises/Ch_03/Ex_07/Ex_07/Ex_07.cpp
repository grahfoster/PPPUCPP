#include "../../../../std_lib_facilities.h"

int main() {
	string val1, val2, val3;

	// collect three string values from user and order them smallest to largest
	cout << "Enter three string values: ";
	while (cin >> val1 >> val2 >> val3) {
		cout << (val1 <= val2 && val1 <= val3 ? val1 : (val2 <= val1 && val2 <= val3 ? val2 : val3)) << " "
			<< ((val1 >= val2 && val1 <= val3) || (val1 >= val3 && val1 <= val2) ? val1 :
			((val2 >= val1 && val2 <= val3) || (val2 >= val3 && val2 <= val1) ? val2 : val3)) << " "
			<< (val1 >= val2 && val1 >= val3 ? val1 : (val2 >= val1 && val2 >= val3 ? val2 : val3)) << endl;
	}
}