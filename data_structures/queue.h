//
//  queue.h
//  Algorithms
//
//  Created by longjianjiang on 2019/2/26.
//  Copyright © 2019 longjianjiang. All rights reserved.
//

#ifndef queue_h
#define queue_h

#include <iostream>
#include <exception>

namespace jiang {
#define DEFAULT_Q_SIZE 100

	template <typename T>
	class queue {
	public:
		queue(int nsize = DEFAULT_Q_SIZE);
		~queue();

		void push(const T& data);
		T pop();
		T back();
		T front();
		bool empty();
		bool full();
		T& operator[](int index);

	private:
		T *arr;
		int capacity;
		int contents;
	};

	// Public Methods
	template <typename T>
	queue<T>::queue(int nsize) {
		try {
            capacity = nsize;
			contents = 0;
			arr = (T*)calloc(capacity, sizeof(T));
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }		
	}

	template <typename T>
	queue<T>::~queue() {
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
	void queue<T>::push(const T& data) {
		if (contents < capacity) {
			arr[contents] = data;
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
    T queue<T>::back() {
    	if (contents > 0) {
    		return arr[contents-1];
    	} else {
    		throw peeking_empty_queue();
    	}
    }

    template <typename T>
    T queue<T>::front() {
    	if (contents > 0) {
    		return arr[0];
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
    T queue<T>::pop() {
    	if (contents > 0) {
    		T tmp = arr[0];
    		int idx = 1;
    		while (idx < contents) {
    			arr[idx-1] = arr[idx];
    			++idx;
    		}
    		--contents;
    		return tmp;
    	} else {
    		throw dequeueing_empty_queue();
    	}
    }

    template <typename T>
    bool queue<T>::empty() {
    	return contents == 0;
    }

    template <typename T>
    bool queue<T>::full() {
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
    T& queue<T>::operator[](int index) {
    	if (contents > 0) {
    		if (index >= 0 && index < contents) {
    			return arr[index];
    		} else if (index < 0 && index + contents >= 0) {
    			return arr[contents+index];
    		} else {
    			throw accessing_out_of_bounds_queue_index();
    		}
    	} else {
    		throw peeking_empty_queue();
    	}
    }

}

#endif /* queue_h */