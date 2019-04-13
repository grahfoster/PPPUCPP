#include "../../../../std_lib_facilities.h"

struct Data {
	double min = 0, max = 0, mean = 0, median = 0;

	Data(double min, double max, double mean, double median) {
		this->min = min;
		this->max = max;
		this->mean = mean;
		this->median = median;
	}
};

Data create_data(vector<double>&);

int main() {
	vector<double> nums{ 1, 2, 3, 4, 5 };
	Data data = create_data(nums);
	cout << "Min: " << data.min << ", "
		<< "Max: " << data.max << ", "
		<< "Mean: " << data.mean << ", "
		<< "Median: " << data.median << '\n';
}

Data create_data(vector<double>& nums) {
	double min = 0, max = 0, mean = 0, median = 0, sum = 0;

	sort(nums.begin(), nums.end());
	min = nums.front();
	max = nums.back();
	for (int num : nums)
		sum += num;
	mean = sum / nums.size();
	median = nums.size() % 2 == 0 ? (nums[nums.size() / 2 - 1] + nums[nums.size() / 2]) / 2 : nums[nums.size() / 2];

	return Data(min, max, mean, median);
}