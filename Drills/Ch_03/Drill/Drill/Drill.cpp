#include "../../../../std_lib_facilities.h"

int main() {
	char friend_sex = 0;
	int age = 0;
	string first_name, friend_name;

	// collect user input and begin writing letter
	cout << "Enter the name of the person you want to write to: ";
	cin >> first_name;
	cout << "Dear" << first_name << ",\n"
		<< "\tHow are you? I'm fine. The days are finally getting longer.\n";

	// collect more input and continue writing letter
	cout << "Enter the name of your mutual friend: ";
	cin >> friend_name;
	cout << "Have you seen " << friend_name << " lately?\n";

	// collect more input and vary output according to entered sex
	cout << "Enter the sex of your mutual friend (m/f): ";
	cin >> friend_sex;
	if (friend_sex == 'm')
		cout << "If you see " << friend_name << " please ask him to call me.\n";
	else if (friend_sex == 'f')
		cout << "If you see " << friend_name << " please ask her to call me.\n";

	// collect and validate more input
	cout << "Enter the age of the recipient: ";
	cin >> age;
	if (age <= 0 || age >= 110)
		error("You're kidding!");

	// vary output according to entered age
	if (age < 12)
		cout << "Next year you'll be " << age + 1 << ".\n";
	else if (age == 17)
		cout << "Next year you'll be able to vote.\n";
	else if (age > 70)
		cout << "I hope you're enjoying retirement.\n";

	// finish writing letter
	cout << "Yours sincerely,\n\n"
		<< "Greg\n";
}