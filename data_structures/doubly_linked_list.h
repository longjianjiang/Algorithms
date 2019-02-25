//
//  doubly_linked_list.h
//  Algorithms
//
//  Created by longjianjiang on 2019/2/24.
//  Copyright © 2019 longjianjiang. All rights reserved.
//

#ifndef doubly_linked_list_h
#define doubly_linked_list_h

#include <iostream>
#include <exception>

namespace jiang {

	template <typename T>
	struct doubly_linked_list_node {
		T data;
		doubly_linked_list_node<T> *prev;
		doubly_linked_list_node<T> *next;
	};

	template <typename T>
	class doubly_linked_list {
	public:
		doubly_linked_list();
		~doubly_linked_list();

		virtual doubly_linked_list_node<T>* get_head();
		virtual doubly_linked_list_node<T>* get_tail();
		virtual void set_head(doubly_linked_list_node<T> *node);
		virtual void set_tail(doubly_linked_list_node<T> *node);
		virtual doubly_linked_list_node<T>* insert(const T& data);
		virtual doubly_linked_list_node<T>* insert_front(const T& data);
		virtual bool remove(const T& data);
		virtual bool remove_node(doubly_linked_list_node<T> *node);
		virtual size_t get_num_nodes();

		virtual void show();
		virtual void bubble_sort_list();
	
	protected:
		size_t num_nodes;
		doubly_linked_list_node<T> *head;
		doubly_linked_list_node<T> *tail;

		virtual doubly_linked_list_node<T>* create_node(const T& data, doubly_linked_list_node<T> *parent = nullptr);
		virtual void free_list(doubly_linked_list_node<T> *node);
		virtual void delete_node(doubly_linked_list_node<T> *node);
	};

	// Debug Methods
	template <typename T>
	void doubly_linked_list<T>::show() {
		doubly_linked_list_node<T> *cur = get_head();
		while (cur != nullptr) {
			std::cout << cur->data << " ";
			cur = cur->next;
		}
		std::cout << "\n";
	}

	template <typename T>
	void doubly_linked_list<T>::bubble_sort_list() {
		if (get_head() == nullptr) { return; }
		doubly_linked_list_node<T> *left = nullptr, *right = nullptr;
		bool swapped = false;

		do
		{
			swapped = false;
			left = get_head();
			while (left->next != right) {
				if (left->data > left->next->data) {
					std::swap(left->data, left->next->data);
					swapped = true;
				}
				left = left->next;
			}

			right = left;
		} while (swapped);
	}

	// Public Methods
	template <typename T>
	doubly_linked_list<T>::doubly_linked_list() {
		num_nodes = 0;
		head = nullptr;
		tail = nullptr;
	}

	template <typename T>
	doubly_linked_list<T>::~doubly_linked_list() {
		if (get_head() != nullptr) {
			free_list(get_head());
			head = nullptr;
			tail = nullptr;
			num_nodes = 0;
		}
	}

	template <typename T>
	size_t doubly_linked_list<T>::get_num_nodes() { return num_nodes; }

	template <typename T>
	doubly_linked_list_node<T>* doubly_linked_list<T>::get_head() { return head; }
	
	template <typename T>
	doubly_linked_list_node<T>* doubly_linked_list<T>::get_tail() { return tail; }

	template <typename T>
	void doubly_linked_list<T>::set_head(doubly_linked_list_node<T>* node) { head = node; }

	template <typename T>
	void doubly_linked_list<T>::set_tail(doubly_linked_list_node<T> *node) { tail = node; }

	template <typename T>
	doubly_linked_list_node<T>* doubly_linked_list<T>::insert(const T& data) {
		doubly_linked_list_node<T> *tail = get_tail(), *new_node = nullptr;
		new_node = create_node(data, tail);

		if (new_node) {
			if (get_head() == nullptr) {
				set_head(new_node);
			}
			set_tail(new_node);
			++num_nodes;
		}

		return new_node;
	}

	template <typename T>
	doubly_linked_list_node<T>* doubly_linked_list<T>::insert_front(const T& data) {
		doubly_linked_list_node<T> *head_node = get_head();
		doubly_linked_list_node<T> *new_node = create_node(data, nullptr);

		if (new_node) {
			if (head_node) {
				head_node->prev = new_node;
				new_node->next = head_node;
			}
			set_head(new_node);

			if (get_tail() == nullptr) {
				set_tail(new_node);
			}

			++num_nodes;
		}

		return new_node;
	}

	template <typename T>
	bool doubly_linked_list<T>::remove(const T& data) {
		doubly_linked_list_node<T> *cur = get_head();

		while (cur != nullptr && cur->data != data) {
			cur = cur->next;
		}

		if (cur) {
			return remove_node(cur);
		}

		return false;
	}

	template <typename T>
	bool doubly_linked_list<T>::remove_node(doubly_linked_list_node<T>* node) {
		if (node) {
			// normal node
			if (node->prev && node->next) {
				node->prev->next = node->next;
				node->next->prev = node->prev;

                node->prev = nullptr;
                node->next = nullptr;
			} 
			// remove tail node
			else if (node->prev) {
				node->prev->next = nullptr;
				set_tail(node->prev);
				node->prev = nullptr;
			} 
			// remove head node
			else {
				if (node->next) {
					node->next->prev = nullptr;
					set_head(node->next);
					node->next = nullptr;
				} else {
					set_head(nullptr);
				}
			}

			--num_nodes;
			delete_node(node);
			return true;
		}

		return false;
	}

	// Protocted Methods
	template <typename T>
	doubly_linked_list_node<T>* doubly_linked_list<T>::create_node(const T& data, doubly_linked_list_node<T>* parent) {
		try {
			doubly_linked_list_node<T>* new_node = (doubly_linked_list_node<T> *)calloc(sizeof(doubly_linked_list_node<T>), 1);
			new_node->data = data;
			if (parent != nullptr) {
				parent->next = new_node;
				new_node->prev = parent;
			}

			return new_node;
		}
		catch (const std::exception &e ){
            std::cerr << e.what() << std::endl;
        }
		return nullptr;
	}

	template <typename T>
	void doubly_linked_list<T>::free_list(doubly_linked_list_node<T>* node) {
		doubly_linked_list_node<T> *cur = node, *next = nullptr;
		while (cur != nullptr) {
			next = cur->next;
			delete_node(cur);
			cur = next;
		}
	}

	template <typename T>
	void doubly_linked_list<T>::delete_node(doubly_linked_list_node<T>* node) {
		free(node);
		node = nullptr;
	}

}
#endif /* doubly_linked_list_h */
