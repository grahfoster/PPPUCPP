#include "../../../../std_lib_facilities.h"

int main() {
	int val1 = 0, val2 = 0, val3 = 0;

	// collect three integer values from user and order them smallest to largest
	cout << "Enter three integer values: ";
	while (cin >> val1 >> val2 >> val3) {
		cout << (val1 <= val2 && val1 <= val3 ? val1 : (val2 <= val1 && val2 <= val3 ? val2 : val3)) << " "
			<< ((val1 >= val2 && val1 <= val3) || (val1 >= val3 && val1 <= val2) ? val1 :
			((val2 >= val1 && val2 <= val3) || (val2 >= val3 && val2 <= val1) ? val2 : val3)) << " "
			<< (val1 >= val2 && val1 >= val3 ? val1 : (val2 >= val1 && val2 >= val3 ? val2 : val3)) << endl;
	}
}