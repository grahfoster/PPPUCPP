#include "Book.h"

int main()
try {
	Book book1{ "111a", "Grendel", "John Gardner", 1971, false };
	Book book2{ "111a", "Grendel", "John Gardner", 1971, true };
	cout << book1 << '\n' << book2;
	if (book1 == book2) 
		cout << "\nThat's the same book.\n";
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}