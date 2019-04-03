#include "../../../../std_lib_facilities.h"

bool add_val(string day, int val);
void print_vals();

const vector<string> accepted_sundays = { "sunday", "sun", "su" };
const vector<string> accepted_mondays = { "monday", "mon", "mo", "m" };
const vector<string> accepted_tuesdays = { "tuesday", "tues", "tu", "t" };
const vector<string> accepted_wednesdays = { "wednesday", "weds", "we", "w" };
const vector<string> accepted_thursdays = { "thursday", "thurs", "th" };
const vector<string> accepted_fridays = { "friday", "fri", "fr", "f" };
const vector<string> accepted_saturdays = { "saturday", "sat", "sa" };

vector<int> sunday_vals, monday_vals, tuesday_vals, wednesday_vals, thursday_vals, friday_vals, saturday_vals;

int main() {
	int num_rejected = 0;

	cout << "Enter pairs of weekday names followed by integer values (type \"|\" to finish):\n";
	while (true) {
		int val = 0;
		string day;

		cin >> day >> val;
		if (day == "|")	// terminate input when "|" is reached
			break;
		if (!cin && day.size() > 0) {	// reject non-integer input
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << "Value must be an integer.\n";
			continue;
		}

		if (!add_val(day, val)) {	// reject invalid weekday name
			cout << "Invalid weekday name.\n";
			++num_rejected;
		}

		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}

	print_vals();
	cout << "Values rejected: " << num_rejected << '\n';	// print number of rejected values
}

// add integer value to corresponding weekday vector
bool add_val(string day, int val) {
	bool val_added = false;
	string day_adjusted;

	for (char c : day)	// make string all lowercase
		day_adjusted += tolower(c);

	for (string accepted_sunday : accepted_sundays) {	// check if string is a variant of "sunday"
		if (day_adjusted == accepted_sunday) {
			sunday_vals.push_back(val);
			val_added = true;
		}
	}
	for (string accepted_monday : accepted_mondays) {	// check if string is a variant of "monday"
		if (day_adjusted == accepted_monday) {
			monday_vals.push_back(val);
			val_added = true;
		}
	}
	for (string accepted_tuesday : accepted_tuesdays) {	// check if string is a variant of "tuesday"
		if (day_adjusted == accepted_tuesday) {
			tuesday_vals.push_back(val);
			val_added = true;
		}
	}
	for (string accepted_wednesday : accepted_wednesdays) {	// check if string is a variant of "wednesday"
		if (day_adjusted == accepted_wednesday) {
			wednesday_vals.push_back(val);
			val_added = true;
		}
	}
	for (string accepted_thursday : accepted_thursdays) {	// check if string is a variant of "thursday"
		if (day_adjusted == accepted_thursday) {
			thursday_vals.push_back(val);
			val_added = true;
		}
	}
	for (string accepted_friday : accepted_fridays) {	// check if string is a variant of "friday"
		if (day_adjusted == accepted_friday) {
			friday_vals.push_back(val);
			val_added = true;
		}
	}
	for (string accepted_saturday : accepted_saturdays) {	// check if string is a variant of "saturday"
		if (day_adjusted == accepted_saturday) {
			saturday_vals.push_back(val);
			val_added = true;
		}
	}

	return val_added;
}

// print weekday vector values and value sums
void print_vals() {
	int sunday_vals_sum = 0, monday_vals_sum = 0, tuesday_vals_sum = 0, wednesday_vals_sum = 0, 
		thursday_vals_sum = 0, friday_vals_sum = 0, saturday_vals_sum = 0;

	cout << "Sunday values: ";
	for (int val : sunday_vals) {
		cout << val << " ";
		sunday_vals_sum += val;
	}
	cout << '\n' << '\t' << "Sum: " << sunday_vals_sum << '\n';

	cout << "Monday values: ";
	for (int val : monday_vals) {
		cout << val << " ";
		monday_vals_sum += val;
	}
	cout << '\n' << '\t' << "Sum: " << monday_vals_sum << '\n';

	cout << "Tuesday values: ";
	for (int val : tuesday_vals) {
		cout << val << " ";
		tuesday_vals_sum += val;
	}
	cout << '\n' << '\t' << "Sum: " << tuesday_vals_sum << '\n';

	cout << "Wednesday values: ";
	for (int val : wednesday_vals) {
		cout << val << " ";
		wednesday_vals_sum += val;
	}
	cout << '\n' << '\t' << "Sum: " << wednesday_vals_sum << '\n';

	cout << "Thursday values: ";
	for (int val : thursday_vals) {
		cout << val << " ";
		thursday_vals_sum += val;
	}
	cout << '\n' << '\t' << "Sum: " << thursday_vals_sum << '\n';

	cout << "Friday values: ";
	for (int val : friday_vals) {
		cout << val << " ";
		friday_vals_sum += val;
	}
	cout << '\n' << '\t' << "Sum: " << friday_vals_sum << '\n';

	cout << "Saturday values: ";
	for (int val : saturday_vals) {
		cout << val << " ";
		saturday_vals_sum += val;
	}
	cout << '\n' << '\t' << "Sum: " << saturday_vals_sum << '\n';
}