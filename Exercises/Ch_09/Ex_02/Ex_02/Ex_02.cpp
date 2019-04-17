#include "Name_pairs.h"

int main() {
	Name_pairs name_pairs;

	try {
		name_pairs.read_names();
		name_pairs.read_ages();
		name_pairs.sort_pairs();
		name_pairs.print_pairs();
	}
	catch (...) {
		cerr << "Unexpected error.\n";
	}
}