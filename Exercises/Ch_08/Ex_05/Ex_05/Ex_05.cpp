#include "../../../../std_lib_facilities.h"

void reverse_v(vector<int>);
void reverse_r(vector<int>&);

int main() {
	vector<int> numbers = { 1, 2, 3, 4, 5 };
	reverse_v(numbers);
	reverse_r(numbers);
}

void reverse_v(vector<int> numbers) {
	vector<int> temp = numbers;
	for (int i = 0; i < numbers.size(); ++i) {
		numbers[i] = temp[temp.size() - 1 - i];
		numbers[numbers.size() - 1 - i] = temp[i];
	}
	for (int i : numbers)
		cout << i << " ";
	cout << '\n';
}

void reverse_r(vector<int>& numbers) {
	for (int i = 0; i < numbers.size() / 2; ++i)
		swap(numbers[i], numbers[numbers.size() - 1 - i]);
	for (int i : numbers)
		cout << i << " ";
	cout << '\n';
}