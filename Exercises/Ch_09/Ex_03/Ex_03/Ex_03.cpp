#include "Name_pairs.h"

int main() {
	Name_pairs first;
	Name_pairs second;

	try {
		first.read_names();
		first.read_ages();
		first.sort_pairs();
		cout << first;

		second.read_names();
		second.read_ages();
		second.sort_pairs();
		cout << second;

		if (first == second)
			cout << "These name pairs are the same!\n";
	}
	catch (...) {
		cerr << "Unexpected error.\n";
	}
}