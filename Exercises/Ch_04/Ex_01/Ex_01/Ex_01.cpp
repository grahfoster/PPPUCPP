#include "../../../../std_lib_facilities.h"

// int square(int x);

int main() {
	//const double jpy_per_usd = 110.9;	// number of yen in a dollar
	//const double eur_per_usd = 0.89;	// number of euros in a dollar
	//const double gbp_per_usd = 0.77;	// number of pounds in a dollar
	//double money = 1;	// money in yen, euros, or pounds
	//char unit = ' ';	// a space is not a unit
	//cout << "Please enter an amount of money followed by a currency (y/e/p):\n";
	//cin >> money >> unit;
	//if (unit == 'y')
	//	cout << money << " yen == " << money / jpy_per_usd << " dollars\n";
	//else if (unit == 'e')
	//	cout << money << " euros == " << money / eur_per_usd << " dollars\n";
	//else if (unit == 'p')
	//	cout << money << " pounds == " << money / gbp_per_usd << " dollars\n";
	//else
	//	cout << "Sorry, I don't know a currency called '" << unit << "'\n";

	///

	//const double jpy_per_usd = 110.9;	// number of yen in a dollar
	//const double eur_per_usd = 0.89;	// number of euros in a dollar
	//const double gbp_per_usd = 0.77;	// number of pounds in a dollar
	//const double cny_per_usd = 6.71;	// number of yuan in a dollar
	//const double nok_per_usd = 8.63;	// number of kroner in a dollar
	//double money = 1;	// money in yen, euros, or pounds
	//char unit = ' ';	// a space is not a unit
	//cout << "Please enter an amount of money followed by a currency (y/e/p/u/k):\n";
	//cin >> money >> unit;
	//switch (unit) {
	//case 'y':
	//	cout << money << " yen == " << money / jpy_per_usd << " dollars\n";
	//	break;
	//case 'e':
	//	cout << money << " euros == " << money / eur_per_usd << " dollars\n";
	//	break;
	//case 'p':
	//	cout << money << " pounds == " << money / gbp_per_usd << " dollars\n";
	//	break;
	//case 'u':
	//	cout << money << " yuan == " << money / cny_per_usd << " dollars\n";
	//	break;
	//case 'k':
	//	cout << money << " kroner == " << money / nok_per_usd << " dollars\n";
	//	break;
	//default:
	//	cout << "Sorry, I don't know a currency called '" << unit << "'\n";
	//}

	///

	//int i = 'a';
	//while (i <= 'z') {
	//	cout << char(i) << "\t" << i << endl;
	//	++i;
	//}

	///

	//for (int i = 'a'; i <= 'z'; ++i)
	//	cout << char(i) << "\t" << i << endl;
	//for (int i = 'A'; i <= 'Z'; ++i)
	//	cout << char(i) << "\t" << i << endl;
	//for (int i = '0'; i <= '1'; ++i)
	//	cout << char(i) << "\t" << i << endl;

	///

	//for (int i = 0; i < 100; ++i)
	//	cout << i << "\t" << square(i) << "\n";

	///

	string word;
	vector<string> censored_words = { "broccoli", "cabbage", "peas", "carrots" };
	while (cin >> word) {
		for (int i = 0; i < censored_words.size(); ++i) {
			if (word == censored_words[i])
				word = "BLEEP";
		}
		cout << word << "\n";
	}
}

//int square(int x) {
//	int sum = 0;
//	for (int i = 0; i < x; ++i)
//		sum += x;
//	return sum;
//}