//
//  Created by longjianjiang on 2019/09/07.
//  Copyright © 2019 longjianjiang. All rights reserved.
//

#ifndef quick_sort_h
#define quick_sort_h

#include <vector>

namespace jiang {

	int partition_hoare_swap(vector<int>& nums, int left, int right) {
		int pivot = nums[left];
		int i = left, j = right;

		while (1) {
			while (nums[i] < pivot) { ++i; }
			while (nums[j] > pivot) { --j; }

			if (i == j) {
				return i;
			} else if (i > j) {
				return i-1;
			}

			swap(nums[i], nums[j]);
			++i;
			--j;
		}
	}

	void quick_sort_hoare_swap(vector<int>& nums, int left, int right) {
		if (left >= right) { return; }

		int pivot = partition_hoare_swap(nums, left, right);
		quick_sort(nums, left, p);
		quick_sort(nums, p+1, right);
	}

	/**********************************************************************************************/

	int partition_lomuto(vector<int>& nums, int left, int right) {
		int pivot = nums[right];
		int i = left;
		// pos i point to num greater than pivot
		for (int j = left; j < right; ++j) {
			if (nums[j] < pivot) {
				if (i != j) { swap(nums[i], nums[j]); }
				++i;
			}
		}

		if (i == right) {
			return i-1;
		} else {
			swap(nums[i], nums[right]);
			return i;
		}
	}

	void quick_sort_lomuto(vector<int>& nums, int left, int right) {
		if (left >= right) { return; }

		int pivot = partition_lomuto(nums, left, right);
		quick_sort(nums, left, p);
		quick_sort(nums, p+1, right);
	}

}

#endif /* quick_sort_h */
