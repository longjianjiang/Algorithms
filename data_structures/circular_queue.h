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

	private:
		T* arr;
		int capacity;
		int contents;
		int start;
		int end;
	};
}
#endif /* circular_queue_h */