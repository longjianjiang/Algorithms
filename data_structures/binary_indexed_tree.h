//
//  binary_indexed_tree.h
//  Algorithms
//
//  Created by longjianjiang on 2019/3/21.
//  Copyright © 2019 longjianjiang. All rights reserved.
//

#ifndef binary_indexed_tree_h
#define binary_indexed_tree_h

#include <iostream>

namespace jiang {
#define DEFAULT_BINARY_INDEXED_TREE_SIZE 1024

    template <typename T>
    class binary_indexed_tree {
    public:
        binary_indexed_tree(size_t nsize = DEFAULT_BINARY_INDEXED_TREE_SIZE);
        binary_indexed_tree(T *arr, size_t nsize);
        ~binary_indexed_tree();
        virtual void update(size_t leaf_index, const T& update_value);
        virtual T get_sum_until(size_t leaf_index);
        virtual T get_sum_range(size_t from, size_t end);
        void show();
    protected:
        T *arr;
        size_t capacity;

        T initial_value() { return 0; }
        T null_value() { return 0; }
    };

    template <typename T>
    binary_indexed_tree<T>::binary_indexed_tree(size_t nsize) {
        if (nsize) {
            arr = (T *)calloc(nsize+1, sizeof(T));
            capacity = nsize + 1;
        } else {
            arr = nullptr;
            capacity = 0;
        }
    }

    template <typename T>
    binary_indexed_tree<T>::binary_indexed_tree(T *arr, size_t nsize) {
        if (nsize) {
            this->arr = (T *)calloc(nsize+1, sizeof(T));
            capacity = nsize + 1;
            for (size_t i = 0; i < nsize; ++i) {
                update(i, arr[i]);
            }
        } else {
            this->arr = nullptr;
            capacity = 0;
        }
    }

    template <typename T>
    binary_indexed_tree<T>::~binary_indexed_tree() {
        if (arr) {
            free(arr);
            arr = nullptr;
            capacity = 0;
        }
    }

    template <typename T>
    void binary_indexed_tree<T>::update(size_t leaf_index, const T &update_value) {
        if (arr && leaf_index+1 < capacity) {
            size_t idx = leaf_index+1;
            while (idx < capacity) {
                arr[idx] += update_value;
                idx += idx & (-idx);
            }
        }
    }

    template <typename T>
    T binary_indexed_tree<T>::get_sum_until(size_t leaf_index) {
        if (leaf_index + 1 < capacity) {
            T res = initial_value();
            size_t idx = leaf_index + 1;
            while (idx) {
                res += arr[idx];
                idx -= idx & (-idx);
            }
            return res;
        } else {
            return null_value();
        }
    }

    template <typename T>
    T binary_indexed_tree<T>::get_sum_range(size_t from, size_t end) {
        return get_sum_until(end) - get_sum_until(from-1);
    }

    template <typename T>
    void binary_indexed_tree<T>::show() {
        for (int i = 1; i < capacity; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";
    }
}

#endif /* binary_indexed_tree_h */