#include <stdlib.h>
#include <stdio.h>

struct Data {
	int min;
	int max;
	int median;
	int mean;
};

int compare(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

struct Data compute(int nums[], int size)
{
	Data data;
	int sum = 0;
	int i;

	for (i = 0; i < size; ++i)
		sum += nums[i];
	qsort(nums, size, sizeof(int), compare);

	data.min = nums[0];
	data.max = nums[size - 1];
	data.median = size % 2 ? nums[size / 2] : (nums[size / 2] + nums[size / 2 - 1]) / 2;
	data.mean = sum / size;

	return data;
}

int main()
{
	const int size = 10;
	int nums[size] = { 1, 10, 2, 9, 3, 8, 4, 7, 5, 6 };
	Data data = compute(nums, size);
	printf("Results: min = %d, max = %d, median = %d, mean = %d\n", data.min, data.max, data.median, data.mean);
}