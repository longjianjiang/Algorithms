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

    public:
        static const int INORDER = 0;
        static const int PREORDER = 1;
        static const int POSTORDER = 2;
        static const int LEVELORDER = 3;

        binary_search_tree(T *arr, size_t size);
        binary_search_tree():root(nullptr), size(0) {}
        ~binary_search_tree();

        virtual bst_node<T> *insert(const T& data);
        virtual bst_node<T> *find(const T& data) const;
        virtual bool remove(const T& data);
        void clear();
//        virtual void print_traversal_results(int traversal_type = binary_search_tree<T>::INORDER, bst_node<T> *node = nullptr);

    };

    // Public Method
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
}

#endif /* binary_search_tree_h */
