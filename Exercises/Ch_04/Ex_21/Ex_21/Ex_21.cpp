#include "../../../../std_lib_facilities.h"

int main() {
	int score = 0;
	string name;
	vector<int> scores;
	vector<string>names;

	// prompt user for input
	cout << "Enter pairs of names and scores: ";
	while (cin >> name >> score) {
		// exit loop upon receiving specific input
		if (name == "NoName" && score == 0)
			break;

		// throw an error if the name has already been entered
		for (int i = 0; i < names.size(); ++i) {
			if (name == names[i])
				error("Repeat name");
		}

		// add the name and score to the respective vectors
		names.push_back(name);
		scores.push_back(score);
	}

	// prompt user for input
	cout << "Enter a score to find a corresponding name: ";
	while (cin >> score) {
		bool was_found = false;
		// output the name associated with a particular score
		for (int i = 0; i < scores.size(); ++i) {
			if (score == scores[i]) {
				was_found = true;
				cout << "Name: " << names[i] << "\n";
			}
		}

		// indicate if score was not found
		if (!was_found)
			cout << "Score not found.\n";
	}
}