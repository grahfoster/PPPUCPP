#include "../../../../std_lib_facilities.h"

void print(const int);

int main() {
	int i = 0;
	print(i);
}

void print(const int i) {
	//cout << ++i;	// illegal
	cout << i;
}