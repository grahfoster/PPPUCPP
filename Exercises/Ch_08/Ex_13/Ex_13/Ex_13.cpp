#include "../../../../std_lib_facilities.h"

struct Words {
	string shortest, longest, first, last;

	Words(string shortest, string longest, string first, string last) {
		this->shortest = shortest;
		this->longest = longest;
		this->first = first;
		this->last = last;
	}
};

void set_char_counts(vector<string>&, vector<int>&);
Words set_words(vector<string>&);

int main() {
	vector<string> nums{ "one", "two", "three", "four", "five" };
	vector<int> char_counts;

	set_char_counts(nums, char_counts);
	cout << "Strings: ";
	for (int i = 0; i < nums.size(); ++i) {
		cout << nums[i] << " (" << char_counts[i] << " chars)";
		if (i < nums.size() - 1)
			cout << ", ";
		else
			cout << '\n';
	}

	Words words = set_words(nums);
	cout << "Shortest string: " << words.shortest << ", "
		<< "Longest string: " << words.longest << ", "
		<< "First string: " << words.first << ", "
		<< "Last string: " << words.last << '\n';
}

void set_char_counts(vector<string>& nums, vector<int>& char_counts) {
	for (string num : nums)
		char_counts.push_back(num.length());
}

Words set_words(vector<string>& nums) {
	int shortest_count = nums[0].length();
	int longest_count = shortest_count;
	string shortest = nums[0];
	string longest = nums[0];
	string first = nums[0];
	string last = nums[0];

	for (string num : nums) {
		if (num.length() < shortest_count) {
			shortest_count = num.length();
			shortest = num;
		}
		if (num.length() > longest_count) {
			longest_count = num.length();
			longest = num;
		}
	}

	sort(nums.begin(), nums.end());
	first = nums.front();
	last = nums.back();

	return Words(shortest, longest, first, last);
}