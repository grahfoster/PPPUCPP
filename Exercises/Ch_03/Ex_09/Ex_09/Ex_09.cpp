#include "../../../../std_lib_facilities.h"

int main() {
	string spelled_num;

	// collect spelled-out number and convert to digit
	cout << "Enter a spelled-out number from 0 to 4: ";
	while (cin >> spelled_num) {
		if (spelled_num == "zero")
			cout << "0\n";
		else if (spelled_num == "one")
			cout << "1\n";
		else if (spelled_num == "two")
			cout << "2\n";
		else if (spelled_num == "three")
			cout << "3\n";
		else if (spelled_num == "four")
			cout << "4\n";
		else
			cout << "I don't know that number.\n";
	}
}