//
//  insertion_sort.h
//  Algorithms
//
//  Created by longjianjiang on 2019/2/24.
//  Copyright © 2019 longjianjiang. All rights reserved.
//

#ifndef insertion_sort_h
#define insertion_sort_h

#include <iostream>
#include <vector>

namespace jiang {

	template <typename T>
	void insertion_sort(std::vector<T>& arr, bool sort_ascending = true) {
		for (int i = 1; i < arr.size(); ++i) {
			int num = arr[i];
			int j = i-1;
			
			if (sort_ascending) {
				while (j >= 0 && num < arr[j]) {
					arr[j+1] = arr[j];
					j -= 1;
				}
			} else {
				while (j >= 0 && num > arr[j]) {
					arr[j+1] = arr[j];
					j -= 1;
				}
			}

			arr[j+1] = num;
		}
	}
}

#endif /* insertion_sort_h */
