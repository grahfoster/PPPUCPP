#include "../../../../std_lib_facilities.h"

int convert(string operand);

const int input_invalid = 10;

int main() {
	char operator1 = 0;
	int val1 = 0, val2 = 0;
	string operand1, operand2;

	// collect operands and operator and output answer
	cout << "Enter two single-digit operands (numeric or spelled out) and an operator: ";
	while (cin >> operand1 >> operand2 >> operator1) {
		val1 = convert(operand1);
		val2 = convert(operand2);

		if (val1 != input_invalid && val2 != input_invalid) {
			switch (operator1) {
			case '+':
				cout << "The sum of " << operand1 << " and " << operand2 << " is " << val1 + val2 << ".\n";
				break;
			case '-':
				cout << "The difference of " << operand1 << " and " << operand2 << " is " << abs(val1 - val2) << ".\n";
				break;
			case '*':
				cout << "The product of " << operand1 << " and " << operand2 << " is " << val1 * val2 << ".\n";
				break;
			case '/':
				cout << "The quotient of " << operand1 << " and " << operand2 << " is " << val1 / val2 << ".\n";
				break;
			default:
				cout << "Please enter a valid operator.\n";
			}
		}
		else
			cout << "Please ensure your operands are single-digit (numeric or spelled out).\n";
	}
}

int convert(string operand) {
	vector<string> spelled_numbers = {
		"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

	// check if string is integer
	if (operand.length() == 1) {
		for (int i = 0; i < 10; ++i) {
			if (to_string(i) == operand)
				return i;
		}
	}
	// check if string is a spelled-out number
	else {
		for (int i = 0; i < spelled_numbers.size(); ++i) {
			if (spelled_numbers[i] == operand)
				return i;
		}
	}

	// indicate that input was invalid
	return input_invalid;
}