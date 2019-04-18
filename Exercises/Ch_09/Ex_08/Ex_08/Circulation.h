#include <string>
#include <iostream>
#include <iomanip>

using std::string;
using std::exception;
using std::ostream;
using std::cout;
using std::cerr;

namespace Circulation {

enum class Genre {
	fiction, nonfiction, periodical, biography, children
};

class Book {
public:
	Book(string, string, string, Genre, int, bool);
	string get_isbn() const { return isbn; }
	string get_title() const { return title; }
	string get_author() const { return author; }
	string get_genre() const;
	int get_copyright_date() { return copyright_date; }
	bool get_circ_status() { return is_charged; }
	void charge() { is_charged = true; }
	void discharge() { is_charged = false; }
private:
	string isbn;
	string title;
	string author;
	Genre genre;
	int copyright_date;
	bool is_charged;
	bool is_valid() {
		return copyright_date >= 0 && copyright_date <= 2019 && isbn.length() == 4 &&
			isdigit(isbn[0]) && isdigit(isbn[1]) && isdigit(isbn[2]) && isalnum(isbn[3]);
	}
};

inline bool operator==(const Book& book1, const Book& book2) { return book1.get_isbn() == book2.get_isbn(); }
inline bool operator!=(const Book& book1, const Book& book2) { return !(book1 == book2); }
ostream& operator<<(ostream&, const Book&);

class Patron {
public:
	Patron(string, int, double);
	string get_user_name() { return user_name; }
	int get_card_num() { return card_num; }
	double get_fees_owed() const { return fees_owed; }
	void set_fees_owed(double fees) { fees_owed = fees; }
private:
	string user_name;
	int card_num;
	double fees_owed;
	bool is_valid() { return card_num > 0 && fees_owed >= 0; }
};

inline bool owes_fees(const Patron & patron) { return patron.get_fees_owed() > 0; }
}
