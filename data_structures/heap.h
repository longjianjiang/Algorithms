//
//  heap.h
//  Algorithms
//
//  Created by longjianjiang on 2019/2/24.
//  Copyright © 2019 longjianjiang. All rights reserved.
//

#ifndef heap_h
#define heap_h

#include <iostream>
#include <exception>

namespace jiang {
#define DEFAULT_HEAP_SIZE 100

	template <typename T>
	class heap {
	public:
		heap(int nsize = DEFAULT_HEAP_SIZE, bool is_max_heap = true);
		heap(const std::vector<T>& arr, bool is_max_heap = true);
		~heap();

		void push(const T& data);
		T pop();
		T top();
		bool empty();
		bool full();

	private:
		bool is_max_heap;
		int capacity;
		int contents;
		std::vector<T> arr;

		int left_child_index(int pos);
		int right_child_index(int pos);
		int parent_index(int pos);

		void build_heap();
		void shift_up(int pos);
		void shift_down(int pos);
	};

	// Public Methods
	template <typename T>
	heap<T>::heap(int nsize, bool is_max_heap) {
		this->capacity = nsize;
		this->contents = 0;
		this->arr = {};
		this->is_max_heap = is_max_heap;
	}

	template <typename T>
	heap<T>::heap(std::vector<T>& arr, bool is_max_heap) {
		this->capacity = (int)arr.size();
		this->contents = (int)arr.size();
		this->arr = arr;
		this->is_max_heap = is_max_heap;
		build_heap();
	}
	
	template <typename T>
	heap<T>::~heap() {
		this->capacity = 0;
		this->contents = 0;
	}

#ifndef PUSHING_FULL_HEAP
#define PUSHING_FULL_HEAP 

	struct pushing_full_heap : public std::exception {
		const char* what() const throw() {
			return "Unable to push a data into full heap.";
		}
	};

#endif /* PUSHING_FULL_HEAP */ 

	template <typename T>
	void heap<T>::push(const T& data) {
		if (contents < capacity) {
			arr[contents] = data;
			++contents;
			shift_up(contents-1);
		} else {
			throw pushing_full_heap();
		}
	}

#ifndef POPPING_EMPTY_HEAP
#define POPPING_EMPTY_HEAP 

	struct popping_empty_heap : public std::exception {
		const char* what() const throw() {
			return "Unable to pop a data from an empty heap.";
		}
	};

#endif /* POPPING_EMPTY_HEAP */ 

	template <typename T>
	T heap<T>::pop() {
		if (contents > 0) {
			T tmp = arr[0];
			arr[0] = arr[contents-1];
			arr.pop_back();
			--contents;
			shift_down(0);
			return tmp;
		} else {
			throw popping_empty_heap();
		}
	}

#ifndef PEEKING_EMPTY_HEAP
#define PEEKING_EMPTY_HEAP 

	struct peeking_empty_heap : public std::exception {
		const char* what() const throw() {
			return "Unbale to peek into an empty heap.";
		}
	};

#endif /* PEEKING_EMPTY_HEAP */ 

	template <typename T>
	T heap<T>::top() {
		if (contents > 0) {
			return arr[0];
		} else {
			throw peeking_empty_heap();
		}
	}

	template <typename T>
	bool heap<T>::empty() {
		return contents <= 0;
	}
	
	template <typename T>
	bool heap<T>::full() {
		return contents == capacity;
	}

	// Private Methods
	template <typename T>
	int heap<T>::left_child_index(int pos) {
		int idx = pos*2 + 1;
		return idx >= contents ? -1 : idx;
	}

	template <typename T>
	int heap<T>::right_child_index(int pos) {
		int idx = pos*2 + 2;
		return idx >= contents ? -1 : idx;
	}

	template <typename T>
	int heap<T>::parent_index(int pos) {
		return (pos-1) / 2;
	}

	template <typename T>
	void heap<T>::build_heap() {
		if (contents && capacity) {
			for (int i = contents/2 -1; i >= 0; --i) {
				shift_down(i);
			}
		}
	}

	template <typename T>
	void heap<T>::shift_up(int pos) {
		if (pos == 0) { return; }
		int p = parent_index(pos);

		if (is_max_heap) {
			if (arr[pos] > arr[p]) {
				std::swap(arr[pos], arr[p]);
				shift_up(p);
			}
		} else {
			if (arr[pos] < arr[p]) {
				std::swap(arr[pos], arr[p]);
				shift_up(p);
			}
		}
	}

	template <typename T>
	void heap<T>::shift_down(int pos) {
		int l = left_child_index(pos);
		int r = right_child_index(pos);

		if (is_max_heap) {
			if (l == -1 && r == -1) {
				return;
			} else if (l == -1) {
				return;
			} else if (r == -1) {
				if (arr[pos] < arr[l]) {
					std::swap(arr[pos], arr[l]);
					shift_down(l);
				}
			} else {
				int biggest = arr[l] > arr[r] ? l : r;
				if (arr[pos] < arr[biggest]) {
					std::swap(arr[pos], arr[biggest]);
					shift_down(biggest);
				}
			}
		} else {
			if (l == -1 && r == -1) {
				return;
			} else if (l == -1) {
				return;
			} else if (r == -1) {
				if (arr[pos] > arr[l]) {
					std::swap(arr[pos], arr[l]);
					shift_down(l);
				}
			} else {
				int smallest = arr[l] < arr[r] ? l : r;
				if (arr[pos] > arr[smallest]) {
					std::swap(arr[pos], arr[smallest]);
					shift_down(smallest);
				}
			}
		}
	}

}
#endif /* heap_h */ 
