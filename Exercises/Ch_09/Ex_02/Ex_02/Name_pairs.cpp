#include "Name_pairs.h"

void Name_pairs::read_names() {
	const string finish = "|";

	cout << "Enter a sequence of names (type \"" << finish << "\" to finish):\n";
	while (true) {
		try {
			string name;
			cin >> name;
			if (name == finish) {
				if (names.size() == 0) {
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					throw exception("read_names() - no names entered");
				}
				break;
			}
			names.push_back(name);
		}
		catch (exception & e) {
			cout << "Error: " << e.what() << ".\n";
		}
	}
}

void Name_pairs::read_ages() {
	cout << "Enter the ages for each name:\n";
	while (ages.size() < names.size()) {
		try {
			int age = 0;
			cin >> age;
			if (!cin) {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				throw exception("read_ages() - invalid input");
			}
			ages.push_back(age);
		}
		catch (exception & e) {
			cerr << "Error: " << e.what() << ".\n";
		}
	}
}

void Name_pairs::sort_pairs() {
	vector<string> names_temp = names;
	vector<double> ages_temp;

	sort(names.begin(), names.end());
	for (int i = 0; i < names.size(); ++i)
		for (int j = 0; j < names_temp.size(); ++j)
			if (names[i] == names_temp[j])
				ages_temp.push_back(ages[j]);
	ages = ages_temp;
}

void Name_pairs::print_pairs() {
	for (int i = 0; i < names.size(); ++i)
		cout << names[i] << " (" << ages[i] << ")\n";
}