#include"../../../../std_lib_facilities.h"

int main() {
	double operand1 = 0, operand2 = 0;
	string operator1;

	// collect entered operator and operands and calculate an answer
	cout << "Enter an operator followed by two operands: ";
	while (cin >> operator1 >> operand1 >> operand2) {
		if (operator1 == "+" || operator1 == "plus")
			cout << operand1 + operand2 << endl;
		else if (operator1 == "-" || operator1 == "minus")
			cout << operand1 - operand2 << endl;
		else if (operator1 == "*" || operator1 == "mul")
			cout << operand1 * operand2 << endl;
		else if (operator1 == "/" || operator1 == "div")
			cout << operand1 / operand2 << endl;
		else
			cout << "I don't know that operand.\n";
	}
}