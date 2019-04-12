#include "../../../../std_lib_facilities.h"

void reverse_v(vector<string>);
void reverse_r(vector<string>&);

int main() {
	vector<string> numbers = { "one", "two", "three", "four", "five" };
	reverse_v(numbers);
	reverse_r(numbers);
}

void reverse_v(vector<string> numbers) {
	vector<string> temp = numbers;
	for (int i = 0; i < numbers.size(); ++i) {
		numbers[i] = temp[temp.size() - 1 - i];
		numbers[numbers.size() - 1 - i] = temp[i];
	}
	for (string s : numbers)
		cout << s << " ";
	cout << '\n';
}

void reverse_r(vector<string>& numbers) {
	for (int i = 0; i < numbers.size() / 2; ++i)
		swap(numbers[i], numbers[numbers.size() - 1 - i]);
	for (string s : numbers)
		cout << s << " ";
	cout << '\n';
}