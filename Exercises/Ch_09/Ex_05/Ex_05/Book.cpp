#include "Book.h"

Book::Book(string isbn, string title, string author, int copyright_date, bool is_charged) :
	isbn(isbn), title(title), author(author), copyright_date(copyright_date), is_charged(is_charged) {
	if (is_valid())
		throw exception("Book() - invalid argument");
}

bool Book::is_valid() {
	return (copyright_date < 0 || copyright_date > 2019 || isbn.length() != 4 ||
		!isdigit(isbn[0]) || !isdigit(isbn[1]) || !isdigit(isbn[2]) || !isalnum(isbn[3]));
}

