#include "../../../../std_lib_facilities.h"

void print_until_ss(const vector<string>&, string);

int main() {
	const string quit = "quit";

	string word;
	vector<string> words;

	cout << "Enter a sequence of strings:\n";
	while (cin >> word) {
		words.push_back(word);
	}

	print_until_ss(words, quit);
}

void print_until_ss(const vector<string>& v, string quit) {
	int quits = 0;
	for (string s : v) {
		if (s == quit && quits == 1)
			return;
		if (s == quit && quits == 0)
			++quits;
		cout << s << '\n';
	}
}