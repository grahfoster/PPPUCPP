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

bool operator==(Book & book1, Book & book2) { 
	return book1.get_isbn() == book2.get_isbn();
}

bool operator!=(Book & book1, Book & book2) { 
	return !(book1 == book2); 
}

ostream& operator<<(ostream & os, Book & book) {
	return os << "ISBN: " << book.get_isbn()
		<< "\nTitle: " << book.get_title()
		<< "\nAuthor: " << book.get_author() << '\n';
}