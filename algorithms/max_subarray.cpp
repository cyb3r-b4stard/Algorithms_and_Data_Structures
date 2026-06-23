#include <iostream>
#include <vector>
#include <cstdint>

struct Triple
{
	int64_t i;
	int64_t j;
	int64_t sum;
};

Triple max_crossing_subarray(const std::vector<int64_t> &vec, int64_t left, int64_t right)
{
	int64_t left_sum{INT64_MIN}, right_sum{INT64_MIN}, sum{0};
	int64_t max_left, max_right, mid{left + ((right - left) >> 1)};

	for (int64_t i{mid}; i >= left; --i)
	{
		sum += vec[i];
		if (sum > left_sum)
		{
			left_sum = sum;
			max_left = i;
		}
	}

	sum = 0;

	for (int64_t i{mid + 1}; i <= right; ++i)
	{
		sum += vec[i];
		if (sum > right_sum)
		{
			right_sum = sum;
			max_right = i;
		}
	}
	return {max_left, max_right, left_sum + right_sum};
}

Triple max_subarray(std::vector<int64_t> &vec, int64_t left, int64_t right)
{
	if (left == right)
	{
		return {left, right, vec[left]};
	}

	int64_t mid{left + ((right - left) >> 1)};

	Triple left_arr{max_subarray(vec, left, mid)};
	Triple cross_arr{max_crossing_subarray(vec, left, right)};
	Triple right_arr{max_subarray(vec, mid + 1, right)};

	if (left_arr.sum >= right_arr.sum && left_arr.sum >= cross_arr.sum)
	{
		return left_arr;
	}
	else if (right_arr.sum >= left_arr.sum && right_arr.sum >= cross_arr.sum)
	{
		return right_arr;
	}

	return cross_arr;
}

Triple max_subarray_linear(std::vector<int64_t> &vec, int64_t left_index, int64_t right_index)
{
	int64_t sum{0}, max_subarray_sum{vec[left_index]};
	int64_t left{left_index}, right{left_index}, left_minus{-1};

	for (int64_t i{left_index}; i <= right_index; ++i)
	{
		sum += vec[i];

		if (sum > max_subarray_sum)
		{
			max_subarray_sum = sum;
			left = left_minus + 1;
			right = i;
		}

		if (sum < 0)
		{
			sum = 0;
			left_minus = i;
		}
	}

	return {left, right, max_subarray_sum};
}

int main()
{
	std::vector<int64_t> vec{-13, -5, -4, -7};
	Triple answer = max_subarray(vec, 0, vec.size() - 1);

	std::cout << answer.i << "\n"
			  << answer.j << "\n"
			  << answer.sum << "\n";

	answer = max_subarray_linear(vec, 0, vec.size() - 1);

	std::cout << answer.i << "\n"
			  << answer.j << "\n"
			  << answer.sum << "\n";
	return 0;
}
