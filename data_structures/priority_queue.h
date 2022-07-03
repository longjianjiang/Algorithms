#ifndef priority_queue_h
#define priority_queue_h

#include <iostream>
#include <vector>
#include <exception>
#include <functional>

namespace jiang {
	template <class T, class Compare = less<T> >
	class priority_queue {
	public:
		priority_queue(const Compare& x) : comp(x) {}
		~priority_queue() = default;

		void push(const T& data);
		T top();
		void pop();
		bool empty();

	private:
   		Compare comp;
		std::vector<T> arr;
		int contents;
	};

	// Public Methods
	template <class T, class Compare>
    bool priority_queue<T, Compare>::empty() {
    	return contents == 0;
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
    T priority_queue<T>::top() {
    	if (contents > 0) {
    		return arr[0];
    	} else {
    		throw peeking_empty_queue();
    	}
    }

	template <typename T>
	void priority_queue<T>::push(const T& data) {
		auto nsize = arr.size();
		if (nsize == 0) {
			arr.push_back(data);
			return;
		}

		auto mid = 0;
		auto l = 0, r = nsize - 1;
		while (l <= r) {
			mid = l + (r - l) / 2;
			bool res = comp(data, arr[mid]);

		}
	}
}
#endif /* priority_queue_h */

/*
    NSUInteger mid = 0;
    NSUInteger min = 0;
    NSUInteger max = self.queue.count - 1;
    BOOL found = NO;
    
    while (min <= max) {
        
        mid = (min + max) / 2;
        
        NSComparisonResult result = self.comparator(object, self.queue[mid]);
        
        if (result == NSOrderedSame) {
            mid++;
            found = YES;
            break;
        } else if (result == NSOrderedAscending) {
            max = mid - 1;
            if (max == NSUIntegerMax) {
                found = YES;
                break;
            }
        } else if (result == NSOrderedDescending) {
            min = mid + 1;
        }
    }
    
    if (found) {
        // Index found at mid
        [self.queue insertObject:object atIndex:mid];
    } else {
        // Index not found, use min
        [self.queue insertObject:object atIndex:min];
    }

	*/