#include "../../../../std_lib_facilities.h"

int main() {
	double temp = 0, sum = 0, median = 0;
	vector<double> temps;

	// collect temps from user
	while (cin >> temp)
		temps.push_back(temp);

	// increment sum by iterating through vector
	for (int i = 0; i < temps.size(); ++i)
		sum += temps[i];

	sort(temps.begin(), temps.end());

	// calculate true median
	median = (temps.size() % 2 == 1 ? temps[temps.size() / 2] :
		(temps[temps.size() / 2] + (temps[temps.size() / 2 + 1]) / 2));

	// output summary of data
	cout << "Average temperature: " << sum / temps.size() << endl;
	cout << "Median temperature: " << median << endl;
}