#include "Circulation.h"

using namespace Circulation;

int main()
try {
	Book book{ "111a", "Grendel", "John Gardner", Genre::fiction, 1971, false };
	Patron patron{ "grahfoster", 12345, 123.40 };
	if (owes_fees(patron))
		cout << "Patron owes $" << std::fixed << std::setprecision(2) << patron.get_fees_owed() << ".\n";
	else
		cout << "Patron owes no fees.\n";
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}