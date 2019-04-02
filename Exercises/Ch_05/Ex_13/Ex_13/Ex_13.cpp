#include "../../../../std_lib_facilities.h"

int main() {
	int seed = 0;

	cout << "Welcome to Bulls and Cows!\n"
		<< "Enter an integer value to seed the round: ";
	cin >> seed;
	while (!cin) {	// reject non-integer input
		cout << "Value must be an integer.\n";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> seed;
	}
	srand(seed);	// randomize generation of correct numbers
	vector<int> correct_nums = { randint(10), randint(10), randint(10), randint(10) };	// generate correct numbers

	while (true) {
		int guess = 0, bulls = 0, cows = 0;
		vector<int> guesses;

		cout << "Enter four integer values between 0 and 9: ";
		while (guesses.size() < correct_nums.size()) {	// ask for input until four integer values have been entered
			cin >> guess;
			if (!cin) {	// reject non-integer input
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "Value must be an integer.\n";
			}
			else if (guess < 0 || guess > 9) {	// reject invalid input
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "Value must be between 0 and 9.\n";
			}
			else
				guesses.push_back(guess);	// add value to vector
		}

		for (int i = 0; i < correct_nums.size(); ++i) {
			if (guesses[i] == correct_nums[i])	// calculate the number of bulls
				++bulls;
			else {
				for (int j = 0; j < correct_nums.size(); ++j) {	// calculate the number of cows
					if (guesses[i] == correct_nums[j])
						++cows;
				}
			}
		}

		if (bulls == correct_nums.size()) {	// check if the player has won
			cout << "You win!\n";
			main();	// start a new game
		}

		cout << "Bulls: " << bulls << ", Cows: " << cows << '\n';	// print the number of bulls and cows
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}
}