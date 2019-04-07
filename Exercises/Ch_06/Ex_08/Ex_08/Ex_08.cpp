#include "../../../../std_lib_facilities.h"

int main() {
	char guess = 0;
	int bulls = 0, cows = 0;
	vector<char> guesses;
	vector<char> correct_letters = { 'a', 'b', 'c', 'd' };

	cout << "Enter four letters between 'a' and 'z': ";
	while (guesses.size() < correct_letters.size()) {	// ask for input until four letters have been entered
		cin >> guess;
		if (!cin || isalpha(guess) == 0) {	// reject non-alphabetic input
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << "Value must be a character between 'a' and 'z'.\n";
			continue;
		}
		tolower(guess);
		guesses.push_back(guess);	// add value to vector
	}

	for (int i = 0; i < correct_letters.size(); ++i) {
		if (guesses[i] == correct_letters[i])	// calculate the number of bulls
			++bulls;
		else {
			for (int j = 0; j < correct_letters.size(); ++j) {	// calculate the number of cows
				if (guesses[i] == correct_letters[j])
					++cows;
			}
		}
	}

	if (bulls == correct_letters.size())	// check if the player has won
		cout << "You win!\n";
	else {
		cout << "Bulls: " << bulls << ", Cows: " << cows << '\n';	// print the number of bulls and cows
		main();
	}
}