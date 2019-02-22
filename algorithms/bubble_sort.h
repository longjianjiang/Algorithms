//
//  bubble_sort.h
//  Algorithms
//
//  Created by longjianjiang on 2019/2/22.
//  Copyright © 2019 longjianjiang. All rights reserved.
//

#ifndef bubble_sort_h
#define bubble_sort_h

#include <iostream>
#include <vector>

namespace jiang {
	
   template <typename T>
    void bubble_sort(std::vector<T>& arr, bool sort_ascending = true) {
        int count = (int)arr.size();
        for (int i = 0; i < count-1; ++i) {
            bool swapped = false;
            for (int j = 0; j < count-1-i; ++j) {
                if (sort_ascending) {
                    if (arr[j+1] < arr[j]) {
                        std::swap(arr[j+1], arr[j]);
                        swapped = true;
                    }
                } else {
                    if (arr[j+1] > arr[j]) {
                        std::swap(arr[j+1], arr[j]);
                        swapped = true;
                    }
                }
            }
            if (swapped == false) { break; }
        }
    }
}
#endif /* bubble_sort_h */
