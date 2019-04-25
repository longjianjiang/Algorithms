//
//  binary_search_tree.h
//  Algorithms
//
//  Created by longjianjiang on 2019/2/20.
//  Copyright © 2019 longjianjiang. All rights reserved.
//

#ifndef binary_search_tree_h
#define binary_search_tree_h

#include <iostream>
#include <exception>
#include "...algorithms/heap_sort.h"

namespace jiang {

    template<typename T>
    struct bst_node {
        T data;
        bst_node<T> *left;
        bst_node<T> *right;
        bst_node<T> *parent;
    };

    template<typename T>
    class binary_search_tree {
    protected:
        bst_node<T> *root;
        int size;

        virtual bst_node<T> *create_node(const T& data, bst_node<T> *parent = nullptr);
        virtual void destroy_node(bst_node<T> *node);

        virtual void remove(bst_node<T> *node);
        virtual bst_node<T> *make_balanced_tree(const std::vector<T>& arr);

        void print_preorder_results(bst_node<T> *node);
        void print_inorder_results(bst_node<T> *node);
        void print_postorder_results(bst_node<T> *node);
        void print_levelorder_results(bst_node<T> *node);

    public:
        static const int PREORDER = 0;
        static const int INORDER = 1;
        static const int POSTORDER = 2;
        static const int LEVELORDER = 3;

        binary_search_tree(const std::vector<T>& arr);
        binary_search_tree():root(nullptr), size(0) {}
        ~binary_search_tree();

        virtual bst_node<T> *insert(const T& data);
        virtual bst_node<T> *find(const T& data) const;
        virtual bool remove(const T& data);
        void clear();
        void print_traversal_results(int traversal_type = binary_search_tree<T>::PREORDER, bst_node<T> *node = nullptr);

    };

    template <typename T>
    binary_search_tree<T>::binary_search_tree(const std::vector<T>& arr) {
        heap_sort(arr);
        root = make_balanced_tree(arr);
    }

    template<typename T>
    binary_search_tree<T>::~binary_search_tree() {
        clear();
    }

    template<typename T>
    void binary_search_tree<T>::clear() {
        while (root != nullptr) {
            remove(root);
        }
    }

    template<typename T>
    bst_node<T> *
    binary_search_tree<T>::insert(const T &data) {
        bst_node<T> *curr = root, *added = nullptr;
        if (curr == nullptr) {
            size++;
            root = create_node(data);
            added = root;
        } else {
            bst_node<T> *prev = nullptr;
            while (curr != nullptr) {
                prev = curr;
                if (curr->data == data) {
                    std::cout << "disallow insert an equal data in binary search tree\n";
                    return nullptr;
                } else if (curr->data > data) {
                    curr = curr->left;
                } else {
                    curr = curr->right;
                }
            }
            size++;
            bst_node<T> *newNode = create_node(data, prev);
            added = newNode;
            if (data < prev->data) {
                prev->left = newNode;
            } else {
                prev->right = newNode;
            }
        }
        return added;
    }

    template<typename T>
    bst_node<T> *
    binary_search_tree<T>::find(const T &data) const{
        bst_node<T> *curr = root;
        while (curr != nullptr) {
            if (curr->data == data) {
                return curr;
            } else if (curr->data > data) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return nullptr;
    }

    template<typename T>
    bool binary_search_tree<T>::remove(const T &data) {
        bst_node<T> *node = find(data);
        if (node == nullptr) {
            return false;
        } else {
            remove(node);
            return true;
        }
    }

    // Private Method
    template<typename T>
    bst_node<T> *
    binary_search_tree<T>::create_node(const T &data, bst_node<T> *parent) {
        try {
            bst_node<T> *node = (bst_node<T> *)calloc(1, sizeof(bst_node<T>));
            node->data = data;
            node->parent = parent;
            return node;
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
        return nullptr;
    }

    template<typename T>
    void binary_search_tree<T>::destroy_node(bst_node<T> *node) {
        if (node != nullptr) {
            free(node);
            node = nullptr;
        }
    }


    template<typename T>
    void binary_search_tree<T>::remove(bst_node<T> *node) {
        if (node == nullptr) { return; }
        if (root == nullptr) { return; }

        bst_node<T> *parent = node->parent;

        // remove a leaf
        if (node->left == nullptr && node->right == nullptr) {
            if (parent == nullptr) {
                root = nullptr;
            } else if (parent->left == node) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
            destroy_node(node);
            size--;
        }
        // remove a node with only a left child
        else if (node->right == nullptr) {
            if (parent == nullptr) {
                root = node->left;
                root->parent = nullptr;
            } else if (parent->left == node) {
                parent->left = node->left;
                node->left->parent = parent;
            } else {
                parent->right = node->left;
                node->left->parent = parent;
            }
            destroy_node(node);
            size--;
        }
        // remove a node with only a right child
        else if (node->left == nullptr) {
            if (parent == nullptr) {
                root = node->right;
                root->parent = nullptr;
            } else if (parent->left == node) {
                parent->left = node->right;
                node->right->parent = parent;
            } else {
                parent->right = node->right;
                node->right->parent = parent;
            }
            destroy_node(node);
            size--;
        }
        // remove a node with two children
        // swap data with successor (right child's most left child)
        // then remove the successor node
        else {
            bst_node<T> *tmp = node->right;
            while (tmp->left != nullptr) {
                tmp = tmp->left;
            }
            node->data = tmp->data;
            remove(tmp);
        }
    }


    template <typename T>
    void binary_search_tree<T>::print_traversal_results(int traversal_type = binary_search_tree<T>::PREORDER, bst_node<T> *node) {
        if (node == nullptr) { node = root; }

        switch (traversal_type) {
            case binary_search_tree<T>::PREORDER:
                print_preorder_results(node);
                break;
            case binary_search_tree<T>::INORDER:
                print_inorder_results(node);
                break;
            case binary_search_tree<T>::POSTORDER:
                print_postorder_results(node);
                break;
            case binary_search_tree<T>::LEVELORDER:
                print_levelorder_results(node);
                break;
        }
    }

    template <typename T>
    void binary_search_tree<T>::print_preorder_results(bst_node<T> *node) {
        if (node == nullptr) { return; }
        std::stack<bst_node<T> *> s;
        s.push(node);
        while (!s.empty()) {
            bst_node<T> *top = s.top();
            std::cout << top->data << " ";
            s.pop();
            if (top->right) { s.push(top->right); }
            if (top->left) { s.push(top->left); }
        }
    }

    template <typename T>
    void binary_search_tree<T>::print_inorder_results(bst_node<T> *node) {
        if (node == nullptr) { return; }

        std::stack<bst_node<T> *> s;
        bst_node<T> *pointer = node;
        while (!s.empty() || pointer) {
            if (pointer) {
                s.push(pointer);
                pointer = pointer->left;
            } else {
                pointer = s.top();
                std::cout << pointer->data << " ";
                s.pop();
                pointer = pointer->right;
            }
        }
    }

    template <typename T>
    void binary_search_tree<T>::print_postorder_results(bst_node<T> *node) {
        if (node == nullptr) { return; }

        std::stack<bst_node<T> *> s;
        bst_node<T> *pointer = node;

        while (pointer) {
            s.push(pointer);
            pointer = pointer->left;
        }

        while (!s.empty()) {
            bool left_visited = false, right_visited = false;

            if (pointer && s.top()->left == pointer) {
                left_visited = true;
            } else if (pointer && s.top()->right == pointer) {
                left_visited = true;
                right_visited = true;
            }

            pointer = s.top();

            if (pointer->left && !left_visited) {
                s.push(pointer->left);
            } else if (pointer->right && !right_visited) {
                s.push(pointer->right);
            } else {
                s.pop();
                std::cout << pointer->data << " ";
            }
        }
    }

    template <typename T>
    void binary_search_tree<T>::print_levelorder_results(bst_node<T> *node) {
        if (node == nullptr) { return; }

        std::queue<bst_node<T> *> q;
        bst_node<T> *cur;
        q.push(node);

        while (!q.empty()) {
            cur = q.front();
            q.pop();
            std::cout << cur->data << " ";

            if (cur->left) { q.push(cur->left); }
            if (cur->right) { q.push(cur->right); }
        }
    }
}

#endif /* binary_search_tree_h */
