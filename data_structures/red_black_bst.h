//
//  red_black_bst.h
//  Algorithms-CPP
//
//  Created by zl on 2019/2/20.
//  Copyright © 2019 longjianjiang. All rights reserved.
//

#ifndef red_black_bst_h
#define red_black_bst_h

#include <iostream>
#include "binary_search_tree.h"

namespace jiang {

    template<typename T>
    struct rb_bst_node : public bst_node<T> {
    public:
        bool is_black; // default is red
    };

    template<typename T>
    class red_black_tree : public binary_search_tree<T> {
    public:
        red_black_tree(T *arr, size_t size);
        red_black_tree();
        ~red_black_tree();

        bst_node<T> *insert(const T& data);
        
    protected:
        bst_node<T> *create_node(const T& data, bst_node<T> *parent = nullptr);
        virtual void destroy_node(bst_node<T> *node);

        rb_bst_node<T> *get_parent(rb_bst_node<T> *node);
        rb_bst_node<T> *get_sibling(rb_bst_node<T> *node);
        rb_bst_node<T> *get_uncle(rb_bst_node<T> *node);
        rb_bst_node<T> *get_grand_parent(rb_bst_node<T> *node);

        virtual void insert_repair(rb_bst_node<T> *node);
        void remove(bst_node<T> *node);

        void delete_repair(rb_bst_node<T> *node, rb_bst_node<T> *replacing_child);
        void delete_repair_helper1(rb_bst_node<T> *node);
        void delete_repair_helper2(rb_bst_node<T> *node);
        void delete_repair_helper3(rb_bst_node<T> *node);
        void delete_repair_helper4(rb_bst_node<T> *node);
        void delete_repair_helper5(rb_bst_node<T> *node);
        void delete_repair_helper6(rb_bst_node<T> *node);

        virtual bool rotate_left(rb_bst_node<T> *node);
        virtual bool rotate_right(rb_bst_node<T> *node);
    };

    // Public Method
    template<typename T>
    red_black_tree<T>::red_black_tree():binary_search_tree<T>() {
        this->root = nullptr;
        this->size = 0;
    }

    template<typename T>
    red_black_tree<T>::~red_black_tree() {
        binary_search_tree<T>::clear();
    }

    // Private Method
    template<typename T>
    bst_node<T> *
    red_black_tree<T>::create_node(const T &data, bst_node<T> *parent) {
        try {
            rb_bst_node<T> *node = (rb_bst_node<T> *)calloc(sizeof(rb_bst_node<T>), 1);
            node->data = data;
            node->parent = parent;
            return node;
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
        return nullptr;
    }

    template<typename T>
    void red_black_tree<T>::destroy_node(bst_node<T> *node) {
        if (node != nullptr) {
            free((rb_bst_node<T> *) node);
            node = nullptr;
        }
    }

    template<typename T>
    rb_bst_node<T> *
    red_black_tree<T>::get_parent(rb_bst_node<T> *node) {
        if (node != nullptr) {
            return (rb_bst_node<T> *)node->parent;
        }
        return nullptr;
    }

    template<typename T>
    rb_bst_node<T> *
    red_black_tree<T>::get_sibling(rb_bst_node<T> *node) {
        if (node != nullptr) {
            if (node->parent != nullptr) {
                if (node->parent->left == node) {
                    return (rb_bst_node<T> *)node->parent->right;
                } else {
                    return (rb_bst_node<T> *)node->parent->left;
                }
            }
        }
        return nullptr;
    }

    template<typename T>
    rb_bst_node<T> *
    red_black_tree<T>::get_uncle(rb_bst_node<T> *node) {
        if (node != nullptr) {
            if (node->parent != nullptr) {
                if (node->parent->parent != nullptr) {
                    if (node->parent->parent->left == node->parent) {
                        return (rb_bst_node<T> *)node->parent->parent->right;
                    } else {
                        return (rb_bst_node<T> *)node->parent->parent->left;
                    }
                }
            }
        }
        return nullptr;
    }

    template<typename T>
    rb_bst_node<T> *
    red_black_tree<T>::get_grand_parent(rb_bst_node<T> *node) {
        if (node != nullptr) {
            if (node->parent != nullptr) {
                if (node->parent->parent != nullptr) {
                    return (rb_bst_node<T> *)node->parent->parent;
                }
            }
        }
        return nullptr;
    }

    template<typename T>
    bst_node<T> *
    red_black_tree<T>::insert(const T &data) {
        rb_bst_node<T> *added;
        added = (rb_bst_node<T> *)binary_search_tree<T>::insert(data);
        if (added != nullptr) {
            insert_repair(added);
        }
        return added;
    }

    template<typename T>
    void red_black_tree<T>::insert_repair(rb_bst_node<T> *node) {
        rb_bst_node<T> *uncle = get_uncle(node);

        // root node, set black
        if (node->parent == nullptr) {
            node->is_black = true;
        }
        // parent node is black, insert node is red
        else if (get_parent(node)->is_black) {
            // do nothind
            return;
        }
        /***********************************************************************
         * below situation parent node is red, we need do repair job.
         * right now node's grand parent always exist.
         **********************************************************************/

        // uncle node is red
        else if (uncle != nullptr && !uncle->is_black) {
            get_parent(node)->is_black = true;
            uncle->is_black = true;
            rb_bst_node<T> *grand_parent = get_grand_parent(node);
            grand_parent->is_black = false;
            insert_repair(grand_parent);
        }
        // uncle node don't exsit or uncle ndoe is black
        else {
            rb_bst_node<T> *parent = get_parent(node);
            rb_bst_node<T> *grand_parent = get_grand_parent(node);

            // node is parent node's right child
            if (grand_parent->left != nullptr && node == grand_parent->left->right) {
                rotate_left(parent);
                node = (rb_bst_node<T> *)node->left;
            } else if (grand_parent->right != nullptr && node == grand_parent->right->left) {
                rotate_right(parent);
                node = (rb_bst_node<T> *)node->right;
            }

            parent = get_parent(node);
            grand_parent = get_grand_parent(node);

            // node is parent node's left child
            if (parent != nullptr && node == parent->left) {
                rotate_right(grand_parent);
            } else {
                rotate_left(grand_parent);
            }
            parent->is_black = true;
            grand_parent->is_black = false;
        }
    }

    template<typename T>
    void red_black_tree<T>::remove(bst_node<T> *node) {
        bst_node<T> *parent = node->parent;
        rb_bst_node<T> *replacement_node = nullptr;

        // remove a leaf
        if (node->left == nullptr && node->right == nullptr) {
            if (parent == nullptr) {
                this->root = nullptr;
            } else if (parent->left == node) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }

            delete_repair((rb_bst_node<T> *)node, replacement_node);
            destroy_node(node);
            this->size--;
        }
        // remove a node with only a left child
        else if (node->right == nullptr) {
            replacement_node = (rb_bst_node<T> *)node->left;

            if (parent == nullptr) {
                this->root = node->left;
                this->root->parent = nullptr;
            } else if (parent->left == node) {
                parent->left = node->left;
                node->left->parent = parent;
            } else {
                parent->right = node->left;
                node->left->parent = parent;
            }
            
            delete_repair((rb_bst_node<T> *)node, replacement_node);
            destroy_node(node);
            this->size--;
        }
        // remove a node with only a right child
        else if (node->left == nullptr) {
            replacement_node = (rb_bst_node<T> *)node->right;

            if (parent == nullptr) {
                this->root = node->right;
                this->root->parent = nullptr;
            } else if (parent->left == node) {
                parent->left = node->right;
                node->right->parent = parent;
            } else {
                parent->right = node->right;
                node->right->parent = parent;
            }
            
            delete_repair((rb_bst_node<T> *)node, replacement_node);
            destroy_node(node);
            this->size--;
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

    template<typename T>
    void red_black_tree<T>::delete_repair(rb_bst_node<T> *node, rb_bst_node<T> *replacing_child) {
        bool is_node_black = (node != nullptr) ? node->is_black : true;
        bool is_replacement_black = (replacing_child != nullptr) ? replacing_child->is_black : true;

        if (is_node_black) {
            // node is black, replacement node is red
            if (!is_replacement_black && replacing_child) {
                replacing_child->is_black = true;
            }

            /***********************************************************************
             * below situation node is black, replacement node is black
             * one black node missing on the path, so we need do repair job.
             **********************************************************************/
            else {
                delete_repair_helper1(replacing_child);
            }
        }
    }

    template<typename T>
    void red_black_tree<T>::delete_repair_helper1(rb_bst_node<T> *node) {
        if (node != nullptr && node->parent != nullptr) {
            delete_repair_helper2(node);
        }
    }

    template<typename T>
    void red_black_tree<T>::delete_repair_helper2(rb_bst_node<T> *node) {
        rb_bst_node<T> *sibling = get_sibling(node);
        rb_bst_node<T> *parent = get_parent(node);

        // replacement node's sibling node is red
        if (sibling != nullptr && !sibling->is_black) {
            parent->is_black = false;
            sibling->is_black = true;
            if (node == parent->left) {
                rotate_left(parent);
            } else {
                rotate_right(parent);
            }
        }

        delete_repair_helper3(node);
    }

    template<typename T>
    void red_black_tree<T>::delete_repair_helper3(rb_bst_node<T> *node) {
        rb_bst_node<T> *sibling = get_sibling(node);
        rb_bst_node<T> *parent = get_parent(node);
        bool is_sibling_black = (sibling != nullptr) ? sibling->is_black : true;

        if (sibling != nullptr) {
            bool is_sibling_left_child_black = sibling->left ? ((rb_bst_node<T> *) sibling->left)->is_black : true;
            bool is_sibling_right_child_black = sibling->right ? ((rb_bst_node<T> *) sibling->right)->is_black : true;

            // parent node is black, replacement node's sibling is black and sibling's two child is black or null
            if (parent->is_black && is_sibling_black && is_sibling_left_child_black && is_sibling_right_child_black) {
                sibling->is_black = false;
                delete_repair_helper1(parent);
            } else {
                delete_repair_helper4(node);
            }
        }
    }

    template<typename T>
    void red_black_tree<T>::delete_repair_helper4(rb_bst_node<T> *node) {
        rb_bst_node<T> *sibling = get_sibling(node);
        rb_bst_node<T> *parent = get_parent(node);
        bool is_sibling_black = (sibling != nullptr) ? sibling->is_black : true;

        if (sibling != nullptr) {
            bool is_sibling_left_child_black = sibling->left ? ((rb_bst_node<T> *) sibling->left)->is_black : true;
            bool is_sibling_right_child_black = sibling->right ? ((rb_bst_node<T> *) sibling->right)->is_black : true;

            // parent node is red, replacement node's sibling is black and sibling's two child is black or null
            if (!parent->is_black && is_sibling_black && is_sibling_left_child_black && is_sibling_right_child_black) {
                sibling->is_black = false;
                parent->is_black = true;
            } else {
                delete_repair_helper5(node);
            }
        }
    }

    template<typename T>
    void red_black_tree<T>::delete_repair_helper5(rb_bst_node<T> *node) {
        rb_bst_node<T> *sibling = get_sibling(node);
        rb_bst_node<T> *parent = get_parent(node);
        bool is_sibling_black = (sibling != nullptr) ? sibling->is_black : true;

        if (sibling != nullptr && is_sibling_black) {
            bool is_sibling_left_child_black = sibling->left ? ((rb_bst_node<T> *) sibling->left)->is_black : true;
            bool is_sibling_right_child_black = sibling->right ? ((rb_bst_node<T> *) sibling->right)->is_black : true;

            // replacement node's sibling is black, sibling's left child is red, sibling's right child is black or null
            if (node == parent->left && is_sibling_right_child_black && !is_sibling_left_child_black) {
                sibling->is_black = false;
                ((rb_bst_node<T> *) sibling->left)->is_black = true;
                rotate_right(sibling);
            }
            else if (node == parent->right && is_sibling_left_child_black && !is_sibling_right_child_black) {
                sibling->is_black = false;
                ((rb_bst_node<T> *) sibling->right)->is_black = true;
                rotate_left(sibling);
            }
        }
        delete_repair_helper6(node);
    }

    template<typename T>
    void red_black_tree<T>::delete_repair_helper6(rb_bst_node<T> *node) {
        rb_bst_node<T> *sibling = get_sibling(node);
        rb_bst_node<T> *parent = get_parent(node);

        if (sibling != nullptr) {
            sibling->is_black = parent->is_black;
            parent->is_black = true;

            if (node == parent->left) {
                if (sibling->right) {
                    ((rb_bst_node<T> *) sibling->right)->is_black = true;
                }
                rotate_left(parent);
            } else {
                if (sibling->left) {
                    ((rb_bst_node<T> *) sibling->left)->is_black = true;
                }
                rotate_right(parent);
            }
        }
    }

    template<typename T>
    bool red_black_tree<T>::rotate_left(rb_bst_node<T> *parent) {
        if (parent != nullptr) {
            rb_bst_node<T> *node = (rb_bst_node<T> *) parent->right;
            if (node != nullptr) {
                rb_bst_node<T> *grand_parent = get_parent(parent);
                node->parent = grand_parent;
                rb_bst_node<T> *node_left = (rb_bst_node<T> *) node->left;
                if (node_left != nullptr) { node_left->parent = parent; }
                node->left = parent;
                parent->parent = node;
                parent->right = node_left;

                if (grand_parent == nullptr) {
                    this->root = node;
                } else if (grand_parent->left == parent) {
                    grand_parent->left = node;
                } else {
                    grand_parent->right = node;
                }
                return true;
            }
        }
        return false;
    }

    template<typename T>
    bool red_black_tree<T>::rotate_right(rb_bst_node<T> *parent) {
        if (parent != nullptr) {
            rb_bst_node<T> *node = (rb_bst_node<T> *) parent->left;
            if (node != nullptr) {
                rb_bst_node<T> *grand_parent = get_parent(parent);
                node->parent = grand_parent;
                rb_bst_node<T> *node_right = (rb_bst_node<T> *) node->right;
                if (node_right != nullptr) { node_right->parent = parent; }
                node->right = parent;
                parent->parent = node;
                parent->left = node_right;

                if (grand_parent == nullptr) {
                    this->root = node;
                } else if (grand_parent->left == parent) {
                    grand_parent->left = node;
                } else {
                    grand_parent->right = node;
                }
                return true;
            }
        }
        return false;
    }

}
#endif /* red_black_bst_h */
