#include "../../../../std_lib_facilities.h"

int main() {
	const int lower_bound = 2, upper_bound = 100;

	bool is_prime = true;
	vector<int> prime_nums;

	// check each value between 1 and 100 to see if it is prime
	for (int i = lower_bound; i < upper_bound; ++i) {
		if (prime_nums.size() > 0) {
			for (int j = 0; j < prime_nums.size(); ++j) {
				// track if the number isn't prime
				if (i % prime_nums[j] == 0)
					is_prime = false;
			}
		}
		// if the number is prime, add it to the vector
		if (is_prime)
			prime_nums.push_back(i);

		is_prime = true;
	}

	// print all prime numbers found
	cout << "Prime numbers between 1 and " << upper_bound << ": ";
	for (int i = 0; i < prime_nums.size(); ++i)
		cout << prime_nums[i] << " ";
}