//
//  circular_queue.h
//  Algorithms
//
//  Created by longjianjiang on 2019/2/26.
//  Copyright © 2019 longjianjiang. All rights reserved.
//

#ifndef circular_queue_h
#define circular_queue_h

#include <iostream>
#include <exception>

namespace jiang {
#define DEFAULT_CQ_SIZE 100

	template <typename T>
	class circular_queue {
	public:
		circular_queue(int nsize = DEFAULT_CQ_SIZE);
		~circular_queue();

		void push(const T& data);
		T pop();
		T front();
		T back();
		bool empty();
		bool full();
		T& operator[](int index);

	private:
		T* arr;
		int capacity;
		int contents;
		int start;
		int end;
	};

	template <typename T>
	circular_queue<T>::circular_queue(int nsize) {
		try {
            capacity = nsize;
			contents = 0;
			start = 0;
			end = 0;
			arr = (T*)calloc(capacity, sizeof(T));
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }		
	}

	template <typename T>
	circular_queue<T>::~circular_queue() {
		if (arr != nullptr) {
			free(arr);
			arr = nullptr;
		}
		capacity = 0;
		contents = 0;
	}

#ifndef ENQUEUEING_FULL_QUEUE
#define ENQUEUEING_FULL_QUEUE

    struct enqueueing_full_queue : public std::exception {
        const char *what() const throw() {
            return "Unable to enqueue a value into a full queue.";
        }
    };

#endif

    template <typename T>
	void circular_queue<T>::push(const T& data) {
		if (contents < capacity) {
			arr[end] = data;
			end = (end + 1) % capacity;
			++contents;
		} else {
			throw enqueueing_full_queue();
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
    T circular_queue<T>::front() {
    	if (contents > 0) {
    		return arr[start];
    	} else {
    		throw peeking_empty_queue();
    	}
    }

    template <typename T>
    T circular_queue<T>::back() {
    	if (contents > 0) {
    		return arr[end-1];
    	} else {
    		throw peeking_empty_queue();
    	}
    }

#ifndef DEQUEUEING_EMPTY_QUEUE
#define DEQUEUEING_EMPTY_QUEUE

    struct dequeueing_empty_queue : public std::exception {
        const char *what() const throw() {
            return "Unable to dequeue a value from an empty queue.";
        }
    };

#endif

    template <typename T>
    T circular_queue<T>::pop() {
    	if (contents > 0) {
    		T tmp = arr[start];
    		start = (start+1) % capacity;
    		--contents;
    		return tmp;
    	} else {
    		throw dequeueing_empty_queue();
    	}
    }

    template <typename T>
    bool circular_queue<T>::empty() {
    	return contents == 0;
    }

    template <typename T>
    bool circular_queue<T>::full() {
    	return contents == capacity;
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
    T& circular_queue<T>::operator[](int index) {
    	if (contents > 0) {
    		if (index >= 0 && index < contents) {
    			return arr[(start+index) % capacity];
    		} else if (index < 0 && index + contents >= 0) {
    			return arr[(start+contents+index) % capacity];
    		} else {
    			throw accessing_out_of_bounds_queue_index();
    		}
    	} else {
    		throw peeking_empty_queue();
    	}
    }

}
#endif /* circular_queue_h */