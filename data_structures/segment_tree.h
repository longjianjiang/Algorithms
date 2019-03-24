//
//  segment_tree.h
//  Algorithms
//
//  Created by longjianjiang on 2019/3/24.
//  Copyright © 2019 longjianjiang. All rights reserved.
//

#ifndef segment_tree_h
#define segment_tree_h

#include <iostream>

namespace jiang {
#define DEFAULT_SEGMENT_TREE_SIZE 1024
    
    template <typename T>
    struct segment_tree_node {
        segment_tree_node<T> *left, *right, *parent;
        T value;
        size_t lo, hi;
        
        void push_up();
    };
    
    template <typename T>
    void segment_tree_node<T>::push_up() {
        if (left) { value += left->value; }
        if (right) { value += right->value; }
    }
    
    template <typename T>
    class segment_tree {
    public:
        segment_tree(size_t nsize = DEFAULT_SEGMENT_TREE_SIZE);
        segment_tree(T *arr, size_t nsize);
        ~segment_tree();
        
        void update(size_t leaf_index, const T& update_value);
        void update(size_t lo, size_t hi, const T& update_value);
        T get_sum_range(size_t from, size_t end);
        
    private:
        size_t capacity;
        segment_tree_node<T> *root;
        segment_tree_node<T> **leaf_nodes;
        segment_tree_node<T> *make_tree(T *arr, size_t lo, size_t hi, segment_tree_node<T> *parent = nullptr);
        T get_range_func_helper(size_t lo, size_t hi, segment_tree_node<T> *node);
        void free_node(segment_tree_node<T> *node);
    };
    
    template <typename T>
    segment_tree<T>::segment_tree(size_t nsize) {
        if (nsize) {
            leaf_nodes = (segment_tree_node<T> **)calloc(nsize, sizeof(segment_tree_node<T> *));
            capacity = nsize;
            T *temp = (T *)calloc(nsize, sizeof(T));
            root = make_tree(temp, 0, nsize-1, nullptr);
        } else {
            leaf_nodes = nullptr;
            capacity = 0;
            root = nullptr;
        }
    }
    
    template <typename T>
    segment_tree<T>::segment_tree(T *arr, size_t nsize) {
        if (nsize) {
            leaf_nodes = (segment_tree_node<T> **)calloc(nsize, sizeof(segment_tree_node<T> *));
            capacity = nsize;
            root = make_tree(arr, 0, nsize-1, nullptr);
        } else {
            leaf_nodes = nullptr;
            capacity = 0;
            root = nullptr;
        }
    }
    
    template <typename T>
    void segment_tree<T>::free_node(segment_tree_node<T> *node) {
        if (node) {
            if (node->left) { free_node(node->left); }
            if (node->right) { free_node(node->right); }
            free(node);
        }
    }
    
    template <typename T>
    segment_tree<T>::~segment_tree() {
        if (root) {
            free_node(root);
            root = nullptr;
        }
        if (leaf_nodes) {
            free(leaf_nodes);
            leaf_nodes = nullptr;
            capacity = 0;
        }
    }
    
    template <typename T>
    segment_tree_node<T> *segment_tree<T>::make_tree(T *arr, size_t lo, size_t hi, segment_tree_node<T> *parent) {
        try {
            segment_tree_node<T> *node = (segment_tree_node<T> *) calloc(1, sizeof(segment_tree_node<T>));
            node->lo = lo;
            node->hi = hi;
            node->parent = parent;
            if (lo == hi) {
                node->value = arr[lo];
                leaf_nodes[lo] = node;
            } else {
                size_t mid = lo + (hi - lo) / 2;
                node->left = make_tree(arr, lo, mid, node);
                node->right = make_tree(arr, mid+1, hi, node);
                node->push_up();
            }
            return node;
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
        
        return nullptr;
    }
    
    template<typename T>
    T segment_tree<T>::get_range_func_helper(size_t lo, size_t hi, segment_tree_node<T> *node) {
        if (lo <= node->lo && hi >= node->hi) {
            return node->value;
        } else if (lo > node->hi || hi < node->lo) {
            return 0;
        } else {
            return get_range_func_helper(lo, hi, node->left) +
                   get_range_func_helper(lo, hi, node->right);
        }
    }
    
    template <typename T>
    T segment_tree<T>::get_sum_range(size_t from, size_t end) {
        if (capacity && root) {
            return get_range_func_helper(from, end, root);
        }
        return 0;
    }
    
    template <typename T>
    void segment_tree<T>::update(size_t leaf_index, const T &update_value) {
        if (leaf_index < capacity) {
            segment_tree_node<T> *curr = leaf_nodes[leaf_index];
            while (curr) {
                curr->value += update_value;
                curr = curr->parent;
            }
        }
    }
}

#endif /* segment_tree_h */