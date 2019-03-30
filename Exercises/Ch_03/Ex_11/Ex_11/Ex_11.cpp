#include "../../../../std_lib_facilities.h"

int main() {
	const int nickel_val = 5, dime_val = 10, quarter_val = 25, half_dollar_val = 50, dollar_coin_val = 100;
	int num_pennies = 0, num_nickels = 0, num_dimes = 0, num_quarters = 0, num_half_dollars = 0, num_dollar_coins = 0;
	double total_money = 0;

	// collect number of coins from user
	cout << "Enter the number of pennies you have: ";
	cin >> num_pennies;
	cout << "Enter the number of nickels you have: ";
	cin >> num_nickels;
	cout << "Enter the number of dimes you have: ";
	cin >> num_dimes;
	cout << "Enter the number of quarters you have: ";
	cin >> num_quarters;
	cout << "Enter the number of half dollars you have: ";
	cin >> num_half_dollars;
	cout << "Enter the number of dollar coins you have: ";
	cin >> num_dollar_coins;

	// add up total amount of money, in dollars
	total_money = (num_pennies + num_nickels * nickel_val + num_dimes * dime_val + num_quarters * quarter_val +
		num_half_dollars * half_dollar_val + num_dollar_coins * dollar_coin_val) / 100.0;

	// output summary of data, adjusting for singularity/plurality
	cout << "You have " << num_pennies << (num_pennies == 1 ? " penny.\n" : " pennies.\n")
		<< "You have " << num_nickels << (num_nickels == 1 ? " nickel.\n" : " nickels.\n")
		<< "You have " << num_dimes << (num_dimes == 1 ? " dime.\n" : " dimes.\n")
		<< "You have " << num_quarters << (num_quarters == 1 ? " quarter.\n" : " quarters.\n")
		<< "You have " << num_half_dollars << (num_half_dollars == 1 ? " half dollar.\n" : " half dollars.\n")
		<< "You have " << num_dollar_coins << (num_dollar_coins == 1 ? " dollar coin.\n" : " dollar coins.\n")
		<< "The total value of all your coins is $" << total_money << ".\n";
}