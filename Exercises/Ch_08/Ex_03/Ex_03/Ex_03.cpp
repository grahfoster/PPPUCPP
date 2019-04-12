#include "../../../../std_lib_facilities.h"

vector<int> fibonacci(int, int, vector<int>, int);
void print(string, vector<int>);

int main() {
	const int num1 = 1, num2 = 2, num_count = 10;
	const string label = "Fibonacci sequence";

	try {
		print(label, fibonacci(num1, num2, vector<int>(), num_count));
	}
	catch (exception& e) {
		cerr << "Error: " << e.what() << ".\n";
	}
}

vector<int> fibonacci(int num1, int num2, vector<int> nums, int num_count) {
	nums.push_back(num1);
	nums.push_back(num2);
	for (int i = 0; i < num_count; ++i) {
		if (nums[nums.size() - 2] > numeric_limits<int>::max() - nums[nums.size() - 1])
			error("fibonacci() - int overflow");
		nums.push_back(nums[nums.size() - 2] + nums[nums.size() - 1]);
	}
	return nums;
}

void print(string label, vector<int> numbers) {
	cout << label << ": ";
	for (int i : numbers)
		cout << i << " ";
	cout << '\n';
}