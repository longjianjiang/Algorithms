//
//  Created by longjianjiang on 2019/08/16.
//  Copyright © 2019 longjianjiang. All rights reserved.
//

#ifndef shell_sort_h
#define shell_sort_h

#include <iostream>
#include <vector>

namespace jiang {

	// shell sort => group insertion sort
	void shell_sort(vector<int>& arr) {
		int nsize = (int)arr.size();

		for (int gap = nsize/2; gap > 0; gap /= 2) {
			for (int i = 0; i < gap; ++i) {
				for (int j = i+gap; j < nsize; j += gap) {
					int tmp = arr[j];
					int k = j - gap;

					while (k >= 0 && tmp < arr[k]) {
						arr[k+gap] = arr[k];
						k -= gap;
					}

					arr[k+gap] = tmp;
				}
			}
		}
	}
}

#endif /* shell_sort_h */
