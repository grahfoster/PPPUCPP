#include <string>
#include <iostream>

using namespace std;

class Book {
public:
	Book(string, string, string, int, bool);
	string get_isbn() { return isbn; }
	string get_title() { return title; }
	string get_author() { return author; }
	int get_copyright_date() { return copyright_date; }
	bool get_circ_status() { return is_charged; }
	void charge() { is_charged = true; }
	void discharge() { is_charged = false; }
private:
	string isbn;
	string title;
	string author;
	int copyright_date;
	bool is_charged;
	bool is_valid();
};

bool operator==(Book&, Book&);
bool operator!=(Book&, Book&);
ostream& operator<<(ostream&, Book&);