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
#include "../data_structures/heap.h"

namespace jiang {

	template <typename T>
	void heap_sort(std::vector<T>& arr, bool sort_ascending = true) {
		heap<T> h(arr, !sort_ascending);
		for(size_t i = 0; i < arr.size(); ++i){
            arr[i] = h.pop();
        }
	}
}

#endif /* heap_sort_h */