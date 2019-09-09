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

	void quick_sort(vector<int>& nums, int left, int right) {
		if (left >= right) { return; }

		int pivot = partition_hoare_swap(nums, left, right);
		quick_sort(nums, left, p);
		quick_sort(nums, p+1, right);
	}
}

#endif /* quick_sort_h */
