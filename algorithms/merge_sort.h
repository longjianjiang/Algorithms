//
//  merge_sort.h
//  Algorithms
//
//  Created by longjianjiang on 2019/4/11.
//  Copyright © 2019 longjianjiang. All rights reserved.
//

#ifndef merge_sort_h
#define merge_sort_h

#include <iostream>
#include <vector>

namespace jiang {
    template <typename T>
    void merge_sort(std::vector<T>& arr, bool sort_ascending = true) {
        if (arr.size() <= 1) { return; }

        auto half = arr.size() / 2;
        std::vector<T> left = std::vector<T>(arr.begin(), arr.begin()+half);
        std::vector<T> right = std::vector<T>(arr.begin()+half, arr.end());

        merge_sort(left, sort_ascending);
        merge_sort(right, sort_ascending);

        auto leftIdx = 0, rightIdx = 0, idx = 0;
        while (leftIdx < left.size() && rightIdx < right.size()) {
            if (sort_ascending) {
                if (left[leftIdx] < right[rightIdx]) {
                    arr[idx++] = left[leftIdx++];
                } else {
                    arr[idx++] = right[rightIdx++];
                }
            } else {
                if (left[leftIdx] > right[rightIdx]) {
                    arr[idx++] = left[leftIdx++];
                } else {
                    arr[idx++] = right[rightIdx++];
                }
            }
        }

        while (leftIdx < left.size()) {
            arr[idx++] = left[leftIdx++];
        }
        while (rightIdx < right.size()) {
            arr[idx++] = right[rightIdx++];
        }
    }
}
#endif /* merge_sort_h */