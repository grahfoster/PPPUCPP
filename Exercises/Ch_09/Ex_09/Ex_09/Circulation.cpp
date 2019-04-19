/*
	This file provides implementations for classes and helper functions used in creating,
	accessing, and manipulating records of library books, patrons, transactions, and
	collections.
*/

#include "Circulation.h"

namespace Circulation {

/*----------Book Class Constructors----------*/

// construct Book with custom values for ISBN, title, author, genre, copyright year, and charged status
Book::Book(string isbn, string title, string author, Genre genre, int copyright_year, bool is_charged) :
	isbn(isbn), title(title), author(author), genre(genre), copyright_year(copyright_year),
	is_charged(is_charged) {
	if (!is_valid())
		throw exception("Book() - invalid constructor argument");
}

/*----------Book Class Member Functions----------*/

// get string representation of Genre
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

/*----------Patron Class Constructors----------*/

// construct Patron with custom values for user name, card number, and fees owed
Patron::Patron(string user_name, int card_num, double fees_owed) :
	user_name(user_name), card_num(card_num), fees_owed(fees_owed) {
	if (!is_valid())	// validate arguments
		throw exception("Patron() - invalid constructor argument");
}

/*----------Library Class Member Functions----------*/

// charge Book to Patron and create Transaction
void Library::charge_book(Book& book, const Patron& patron, const Date& date) {
	bool is_available = false;
	bool is_registered = false;

	for (Book b : books)	// check if Book exists
		if (book == b)
			is_available = !(b.get_is_charged());	// check if Book is available
	if (!is_available)	// nonexistent/unavailable Books cannot be charged
		throw exception("charge_book() - book is unavailable or doesn't exist");

	for (Patron p : patrons)	// check if Patron is registered
		if (patron == p)
			is_registered = true;
	if (!is_registered)	// unregistered Patrons cannot charge Books
		throw exception("charge_book() - patron is not registered");

	if (owes_fees(patron))	// Patrons who owe fees cannot charge Books
		throw exception("char_book() - patron owes fees");

	add_transaction(Transaction{ book, patron, date });	// create record of Transaction
	book.charge();	// change charged status of book
}

/*----------Library Class Helper Functions----------*/

// get list of all Patrons who owe fees
vector<Patron> Library::get_owing_patrons() {
	vector<Patron> owing_patrons;

	for (Patron patron : patrons) {
		if (owes_fees(patron))
			owing_patrons.push_back(patron);
	}

	return owing_patrons;
}
}