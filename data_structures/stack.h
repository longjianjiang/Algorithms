//
//  stack.h
//  Algorithms
//
//  Created by longjianjiang on 2019/3/1.
//  Copyright © 2019 longjianjiang. All rights reserved.
//

#ifndef stack_h
#define stack_h

#include <iostream>
#include <exception>

namespace jiang {
#define DEFAULT_STACK_SIZE 100

	template <typename T>
	class stack {
	public:
		stack(int nsize = DEFAULT_STACK_SIZE);
		~stack();

		void push(const T& data);
		T pop();
		bool empty();
		bool full();

	private:
		T *arr;
		int capacity;
		int contents;
	};

	template <typename T>
	stack<T>::stack(int nsize) {
		try {
            capacity = nsize;
			contents = 0;
			arr = (T*)calloc(capacity, sizeof(T));
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
	}

	template <typename T>
	stack<T>::~stack() {
		if (arr != nullptr) {
			free(arr);
			arr = nullptr;
		}
		capacity = contents = 0;
	}

#ifndef PUSHING_FULL_STACK
#define PUSHING_FULL_STACK

    struct pushing_full_stack : public std::exception {
        const char *what() const throw() {
            return "Unable to push a key into a full stack.";
        }
    };

#endif

    template <typename T>
    void stack<T>::push(const T& data) {
    	if (contents < capacity) {
    		arr[contents] = data;
    		++contents;
    	} else {
    		throw pushing_full_stack();
    	}
    }


#ifndef POPPING_EMPTY_STACK
#define POPPING_EMPTY_STACK

    struct popping_empty_stack : public std::exception {
        const char *what() const throw() {
            return "Unable to pop a key from an empty stack.";
        }
    };

#endif

    template <typename T>
    T stack<T>::pop() {
    	if (contents > 0) {
    		T tmp = arr[contents-1];
    		--contents;
    		return tmp;
    	} else {
    		throw popping_empty_stack();
    	}
    }

    template <typename T>
    bool stack<T>::empty() {
    	return contents == 0;
    }

    template <typename T>
    bool stack<T>::full() {
    	return contents == capacity;
    }

}
#endif /* stack_h */
