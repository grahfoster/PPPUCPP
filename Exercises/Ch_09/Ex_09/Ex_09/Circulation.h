/*
	This file provides interfaces for class and helper functions used in creating,
	accessing, and manipulating records of library books, patrons, transactions, and
	collections.
*/

#include "Chrono.h"

#include <string>
#include <vector>
#include <iomanip>

using namespace Chrono;
using std::string;
using std::vector;

namespace Circulation {

/*----------Enum Classes----------*/

enum class Genre {	// contains literary genres
	fiction, nonfiction, periodical, biography, children
};

/*----------Book Class----------*/

class Book {	// represents library book
public:
	Book(string, string, string, Genre, int, bool);

	string get_isbn() const {
		return isbn;
	}
	string get_title() const {
		return title;
	}
	string get_author() const {
		return author;
	}
	string get_genre() const;

	int get_copyright_year() {
		return copyright_year;
	}
	bool get_is_charged() {
		return is_charged;
	}
	void charge() {	// charge Book
		is_charged = true;
	}
	void discharge() { // discharge Book
		is_charged = false;
	}
private:
	string isbn;
	string title;
	string author;
	Genre genre;
	int copyright_year;
	bool is_charged;

	bool is_valid() {	// check if Book is valid
		return copyright_year >= 0 && copyright_year <= 2019 && isbn.length() == 4 &&
			isdigit(isbn[0]) && isdigit(isbn[1]) && isdigit(isbn[2]) && isalnum(isbn[3]);
	}
};

/*----------Book Class Helper Functions----------*/

inline bool operator==(const Book& book1, const Book& book2) {	// allow comparison of Books
	return book1.get_isbn() == book2.get_isbn();
}
inline bool operator!=(const Book& book1, const Book& book2) {	// allow differentiation of Books
	return !(book1 == book2);
}
inline ostream& operator<<(ostream & os, const Book & book) {	// allow output of Books
	return os << "ISBN: " << book.get_isbn() << "\nTitle: " << book.get_title() << "\nAuthor: " <<
		book.get_author() << "\nGenre: " << book.get_genre() << '\n';
}

/*----------Patron Class----------*/

class Patron {	// represents library patron
public:
	Patron(string, int, double);

	string get_user_name() const {
		return user_name;
	}
	int get_card_num() const {
		return card_num;
	}
	double get_fees_owed() const {
		return fees_owed;
	}

	void set_fees_owed(double fees) {
		fees_owed = fees;
	}
private:
	string user_name;
	int card_num;
	double fees_owed;

	bool is_valid() {	// check if Patron is valid
		return card_num > 0 && fees_owed >= 0;
	}
};

/*----------Patron Class Helper Functions----------*/

inline bool owes_fees(const Patron & patron) {	// check if Patron owes fees
	return patron.get_fees_owed() > 0;
}
inline bool operator==(const Patron & patron1, const Patron & patron2) {	// allow comparison of Patrons
	return patron1.get_card_num() == patron2.get_card_num();
}
inline bool operator!=(const Patron & patron1, const Patron & patron2) {	// allow differentiation of Patrons
	return !(patron1 == patron2);
}
inline ostream& operator<<(ostream & os, const Patron & patron) {	// allow output of Patrons
	return os << "User name: " << patron.get_user_name() << "\nCard number: " << patron.get_card_num() <<
		"\nAmount owed: $" << std::fixed << std::setprecision(2) << patron.get_fees_owed();
}

/*----------Library Class----------*/

class Library {	// represents library collection
public:
	struct Transaction {	// represents library transaction
		Transaction(const Book& book, const Patron& patron, const Date& date) :
			// construct Transaction with custom values for book, patron, and date
			book(book), patron(patron), date(date) {}

		Book book;
		Patron patron;
		Date date;
	};

	void add_book(const Book& book) {	// add Book to Library
		books.push_back(book);
	}
	void add_patron(const Patron& patron) {	// add Patron to Library
		patrons.push_back(patron);
	}
	void add_transaction(Transaction transaction) {	// add Transaction to Library
		transactions.push_back(transaction);
	}
	void charge_book(Book&, const Patron&, const Date&);

	vector<Patron> get_owing_patrons();
private:
	vector<Book> books;
	vector<Patron> patrons;
	vector<Transaction> transactions;
};
}