#include "../../../../std_lib_facilities.h"

int maxv(vector<int>&);

int main() {
	vector<int> nums{ 1, 2, 3, 4, 5 };
	cout << maxv(nums) << '\n';
}

int maxv(vector<int>& nums) {
	sort(nums.begin(), nums.end());
	return nums.back();
}