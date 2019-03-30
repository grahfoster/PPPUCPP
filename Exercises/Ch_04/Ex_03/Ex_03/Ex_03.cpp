#include "../../../../std_lib_facilities.h"

int main() {
	double distance = 0, total_distance = 0;
	vector<double> distances;

	// collect distance values from user
	cout << "Enter a distance values: ";
	while (cin >> distance) {
		// add distance value to vector and increment sum of values
		distances.push_back(distance);
		total_distance += distance;
	}

	sort(distances.begin(), distances.end());

	// output summary of data
	cout << "Sum of distances: " << total_distance << endl
		<< "Shortest distance: " << distances.front() << endl
		<< "Longest distance: " << distances.back() << endl
		<< "Average distance: " << total_distance / distances.size() << endl;
}