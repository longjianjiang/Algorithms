//
//  heap_sort.h
//  Algorithms
//
//  Created by longjianjiang on 2019/2/23.
//  Copyright © 2019 longjianjiang. All rights reserved.
//

#ifndef heap_sort_h
#define heap_sort_h

#include <vector>

namespace jiang {

	void shift_down(std::vector<int>& arr, int pos, int nsize, bool is_max_heap) {
		int tmp = arr[pos];

		while ((pos*2 + 1) < nsize) {
			int left = pos*2 + 1, right = pos*2 + 2;
			int j = left;
			if (right < nsize) {
				if (is_max_heap) {
					if (arr[right] > arr[left]) { j = right; }	
				} else {
					if (arr[right] < arr[left]) { j = right; }	
				}
			}

			if (is_max_heap) {
				if (tmp >= arr[j]) { break; }
			} else {
				if (tmp <= arr[j]) { break; }
			}

			arr[pos] = arr[j];
			pos = j;
		}

		arr[pos] = tmp;
	}

	void heap_sort(std::vector<int>& arr, bool sort_ascending = true) {
		int nsize = (int)arr.size();

		for (int i = nsize/2 - 1; i >= 0; --i) {
			shift_down(arr, i, nsize, sort_ascending);
		}

		int k = nsize-1;
		while (k > 0) {
			swap(arr[0], arr[k--]);
			shift_down(arr, 0, k+1, sort_ascending);
		}
	}
}

#endif /* heap_sort_h */
