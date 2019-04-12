#include "../../../../std_lib_facilities.h"

int main() {
	double sum = 0;
	vector<double> prices{ 1, 2, 3, 4, 5 };
	vector<double> weights{ 6, 7, 8, 9, 10 };

	try {
		if (prices.size() != weights.size())
			error("unequal vector sizes");
		for (int i = 0; i < prices.size(); ++i)
				sum += prices[i] * weights[i];
	}
	catch (exception& e) {
		cerr << "Error: " << e.what() << ".\n";
	}

	cout << "Sum: " << sum << '\n';
}