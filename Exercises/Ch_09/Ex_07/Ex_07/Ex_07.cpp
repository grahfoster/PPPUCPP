#include "Book.h"

int main()
try {
	Book book{ "111a", "Grendel", "John Gardner", Genre::fiction, 1971, false };
	cout << book;
}
catch (exception & e) {
	cerr << "Error: " << e.what() << ".\n";
}