#include "../../../../std_lib_facilities.h"

void sentence();

int main() {
	try {
		sentence();
		cout << "OK.\n";
	}
	catch (exception& e) {
		cerr << "Not OK: " << e.what() << '\n';
	}
	catch (...) {
		cerr << "Unexpected error.\n";
	}
}

// handle the verbs "rules", "fly", and "swim"
void verb() {
	string word;
	cin >> word;
	if (word != "rules" && word != "fly" && word != "swim")
		error("Invalid or missing verb.\n");
}

// handle the article "the" and the nouns "birds", "fish", and "C++"
void noun() {
	string word;
	cin >> word;
	if (word == "the")
		cin >> word;
	if (word != "birds" && word != "fish" && word != "C++")
		error("Invalid or missing noun.\n");
}

// handle the conjunctions "and", "or", and "but"
void conj(string word) {
	if (word != "and" && word != "or" && word != "but")
		error("Invalid or missing conjunction.\n");
}

// try to form a sentence
void sentence() {
	while (true) {
		noun();
		verb();
		string word;
		cin >> word;
		if (word == ".")
			return;
		conj(word);
	}
}