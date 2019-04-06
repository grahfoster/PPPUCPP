#include "../../../../std_lib_facilities.h"

// contains a name and value pair
class Name_value {
public:
	Name_value(int i, string s) :
		score(i), name(s) {};
	int get_score() { return score; }
	string get_name() { return name; }

private:
	int score = 0;
	string name;
};

int main() {
	int score = 0;
	string name;
	vector<Name_value> pairs;

	cout << "Enter pairs of names and scores: ";
	try {
		while (true) {
			cin >> name >> score;
			if (!cin) {	// reject non-integer score input
				cout << "Score must be an integer.\n";
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				continue;
			}
			if (name == "NoName" && score == 0)	// exit loop upon receiving specific input
				break;
			
			for (int i = 0; i < pairs.size(); ++i) {	// throw an error if the name has already been entered
				if (name == pairs[i].get_name())
					error("Name has already been entered.\n");
			}

			pairs.push_back(Name_value(score, name));	// create a Name_value with the entered pair
		}
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
	}
}