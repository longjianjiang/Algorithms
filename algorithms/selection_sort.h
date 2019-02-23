//
//  selection_sort.h
//  Algorithms
//
//  Created by longjianjiang on 2019/2/23.
//  Copyright © 2019 longjianjiang. All rights reserved.
//

#ifndef selection_sort_h
#define selection_sort_h

#include <iostream>
#include <vector>

namespace jiang {

	template <typename T>
	void selection_sort(std::vector<T>& arr, bool sort_ascending = true) {
		int count = (int)arr.size();
		for (int i = 0; i < count; ++i) {
			int idx = i;
			for (int j = i+1; j < count; ++j) {
				if (sort_ascending) {
					if (arr[j] < arr[i]) {
						idx = j;
					}
				} else {
					if (arr[j] > arr[i]) {
						idx = j;
					}
				}
			}
			std::swap(arr[idx], arr[i]);
		}
	}
}

#endif /* selection_sort_h */
