#include "../../../../std_lib_facilities.h"

int main() {
	const string finish = "|";

	vector<int> ages;
	vector<string> names;

	cout << "Please enter a sequence of names (type \"" << finish << "\" to finish):\n";
	while (true) {
		string name;
		cin >> name;
		if (name == finish)
			break;
		names.push_back(name);
	}

	cout << "Please enter the ages for each name:\n";
	while (ages.size() < names.size()) {
		try {
			int age = 0;
			cin >> age;
			if (!cin) {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				error("invalid input");
			}
			ages.push_back(age);
		}
		catch (exception& e) {
			cerr << "Error: " << e.what() << ".\n";
		}
	}

	for (int i = 0; i < names.size(); ++i)
		cout << names[i] << " (age " << ages[i] << ")   ";
	cout << '\n';

	vector<string> names_temp = names;
	vector<int> ages_temp;

	sort(names.begin(), names.end());
	for (int i = 0; i < names.size(); ++i) 
		for (int j = 0; j < names_temp.size(); ++j) 
			if (names[i] == names_temp[j])
				ages_temp.push_back(ages[j]);
	
	for (int i = 0; i < names.size(); ++i)
		cout << names[i] << " (age " << ages_temp[i] << ")   ";
}