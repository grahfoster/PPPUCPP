#include "Circulation.h"

using namespace Circulation;
using std::cout;
using std::cerr;

int main()
try {
	Library library;
	Book book{ "111a", "Grendel", "John Gardner", Genre::fiction, 1971, false };
	Patron patron{ "grahfoster", 12345, 0 };
	Date date{ 2019, Month::apr, 18 };

	library.add_book(book);
	library.add_patron(patron);

	vector<Patron> owing_patrons = library.get_owing_patrons();
	for (Patron owing_patron : owing_patrons)	// output information of all owing Patrons
		cout << owing_patron << '\n';

	library.charge_book(book, patron, date);
}
catch (exception & e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}