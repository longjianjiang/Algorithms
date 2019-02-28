//
//  double_ended_queue.h
//  Algorithms
//
//  Created by longjianjiang on 2019/2/27.
//  Copyright © 2019 longjianjiang. All rights reserved.
//

#ifndef double_ended_queue_h
#define double_ended_queue_h

#include "doubly_linked_list.h"

namespace jiang {

	template <typename T>
	class double_ended_queue : protected doubly_linked_list<T> {
	public:
		double_ended_queue();
		~double_ended_queue();

		void push_front(const T& data);
		void push_back(const T& data);
		void pop_front();
		void pop_back();
		T back();
		T front();
		bool empty();
		T& operator[](int index);
	};

	template <typename T>
	double_ended_queue<T>::double_ended_queue() {}

	template <typename T>
	double_ended_queue<T>::~double_ended_queue() {}

	template <typename T>
	void double_ended_queue<T>::push_front(const T& data) {
		this->insert_front(data);
	}

	template <typename T>
	void double_ended_queue<T>::push_back(const T& data) {
		this->insert(data);
	}

	template <typename T>
	void double_ended_queue<T>::pop_front() {
		doubly_linked_list_node<T> *head = this->get_head();
		if (head) {
			this->remove_node(head);
		}
	}

	template <typename T>
	void double_ended_queue<T>::pop_back() {
		doubly_linked_list_node<T> *tail = this->get_tail();
		if (tail) {
			this->remove_node(tail);
		}
	}

#ifndef PEEKING_EMPTY_QUEUE
#define PEEKING_EMPTY_QUEUE

    struct peeking_empty_queue : public std::exception {
        const char *what() const throw() {
            return "Unable to peek into an empty queue.";
        }
    };

#endif

	template <typename T>
	T double_ended_queue<T>::back() {
		doubly_linked_list_node<T> *tail = this->get_tail();
		if (tail) {
			return tail->data;
		}
		throw peeking_empty_queue();
	}

	template <typename T>
	T double_ended_queue<T>::front() {
		doubly_linked_list_node<T> *head = this->get_head();
		if (head) {
			return head->data;
		}
		throw peeking_empty_queue();
	}

	template <typename T>
	bool double_ended_queue<T>::empty() {
		return this->num_nodes == 0;
	}

#ifndef ACCESSING_OUT_OF_BOUNDS_QUEUE_INDEX
#define ACCESSING_OUT_OF_BOUNDS_QUEUE_INDEX

    struct accessing_out_of_bounds_queue_index : public std::exception {
        const char *what() const throw() {
            return "Error trying to access out of bounds queue index.";
        }
    };

#endif

    template <typename T>
    T& double_ended_queue<T>::operator[](int index) {
    	if (index >= 0 && index < this->num_nodes) {
    		doubly_linked_list_node<T> *cur = this->get_head();
    		while (cur && index) {
    			cur = cur->next;
    			--index;
    		}
    		return cur->data;
    	} else if (index < 0 && index + this->num_nodes >= 0) {
    		doubly_linked_list_node<T> *cur = this->get_tail();
    		++index;
    		while (cur && index) {
    			cur = cur->next;
    			++index;
    		}
    		return cur->data;
    	} else {
    		throw accessing_out_of_bounds_queue_index();
    	}
    }

}
#endif /* double_ended_queue_h */