#include "../../../../std_lib_facilities.h"

void print(string, vector<int>);

int main() {
	print("Numbers", vector<int> {1, 2, 3, 4, 5});	// sample call
}

void print(string label, vector<int> numbers) {
	cout << label << ": ";
	for (int i : numbers)
		cout << i << " ";
	cout << '\n';
}