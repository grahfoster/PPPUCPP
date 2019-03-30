#include "../../../../std_lib_facilities.h"

int main() {
	char operator1 = 0;
	double operand1 = 0, operand2 = 0;

	// collect operands and operator and output answer
	cout << "Enter two operands and an operator: ";
	while (cin >> operand1 >> operand2 >> operator1) {
		switch (operator1) {
		case '+':
			cout << "The sum of " << operand1 << " and " << operand2 << " is " << operand1 + operand2 << ".\n";
			break;
		case '-':
			cout << "The difference of " << operand1 << " and " << operand2 << " is " << abs(operand1 - operand2) << ".\n";
			break;
		case '*':
			cout << "The product of " << operand1 << " and " << operand2 << " is " << operand1 * operand2 << ".\n";
			break;
		case '/':
			cout << "The quotient of " << operand1 << " and " << operand2 << " is " << operand1 / operand2 << ".\n";
			break;
		default:
			cout << "Please enter a valid operator.\n";
		}
	}
}