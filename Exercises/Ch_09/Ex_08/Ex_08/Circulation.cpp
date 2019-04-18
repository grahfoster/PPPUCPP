#include "Circulation.h"

namespace Circulation {

Book::Book(string isbn, string title, string author, Genre genre, int copyright_date, bool is_charged) :
	isbn(isbn), title(title), author(author), genre(genre), copyright_date(copyright_date),
	is_charged(is_charged) {
	if (!is_valid())
		throw exception("Book() - invalid constructor argument");
}

string Book::get_genre() const {
	switch (genre) {
	case Genre::fiction:
		return "Fiction";
	case Genre::nonfiction:
		return "Nonfiction";
	case Genre::periodical:
		return "Periodical";
	case Genre::biography:
		return "Biography";
	case Genre::children:
		return "Children's Literature";
	default:
		throw exception("get_genre() - invalid enum member");
	}
}

ostream& operator<<(ostream& os, const Book& book) {
	return os << "ISBN: " << book.get_isbn() <<
		"\nTitle: " << book.get_title() <<
		"\nAuthor: " << book.get_author() <<
		"\nGenre: " << book.get_genre() << '\n';
}

Patron::Patron(string user_name, int card_num, double fees_owed) :
	user_name(user_name), card_num(card_num), fees_owed(fees_owed) {
	if (!is_valid())
		throw exception("Patron() - invalid constructor argument");
}
}