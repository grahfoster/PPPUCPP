#include "Book.h"

int main()
try {
	Book book{ "111a", "Grendel", "John Gardner", 1971, false };
	book.charge();

	cout << "ISBN: " << book.get_isbn() << '\n';
	cout << "Title: " << book.get_title() << '\n';
	cout << "Author: " << book.get_author() << '\n';
	cout << "Copyright Date: " << book.get_copyright_date() << '\n';
	cout << "Circulation Status: " << (book.get_circ_status() ? "Charged" : "Available") << '\n';
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}